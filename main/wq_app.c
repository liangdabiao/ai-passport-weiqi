// main/wq_app.c —— 见 wq_app.h。
#include "wq_app.h"

#include <stddef.h>
#include <string.h>

#include "bsp_display.h"   // bsp_lvgl_lock / bsp_lvgl_unlock
#include "esp_log.h"
#include "esp_timer.h"

#include "wq_content.h"
#include "wq_sfx.h"
#include "wq_store.h"
#include "wq_volume.h"

static const char *TAG = "wq_app";

typedef enum {
    PAGE_NONE = 0,
    PAGE_TITLE,
    PAGE_WORLD,
    PAGE_LEVELS,
    PAGE_PLAY,
    PAGE_RESULT,
} page_id_t;

static wq_session_t s_session;
static wq_progress_t s_progress;
static uint8_t s_volume = WQ_VOLUME_DEFAULT;

static lv_obj_t *s_screen;
static page_id_t s_page = PAGE_NONE;

// 当前页面的离开钩子。跳页时先调它清掉旧页面的静态状态，再建新页面 ——
// 顺序反过来会让旧页面的 leave 去清已经属于新页面的状态。
static void (*s_leave)(void);

static void replace_page(page_id_t page, lv_obj_t *(*enter)(void), void (*leave)(void))
{
    if (s_leave) s_leave();
    lv_obj_t *next = enter();
    if (s_screen) lv_obj_delete(s_screen);
    s_screen = next;
    s_page = page;
    s_leave = leave;
    lv_scr_load(s_screen);
}

void wq_app_goto_title(void)
{
    replace_page(PAGE_TITLE, wq_page_title_enter, wq_page_title_leave);
}

void wq_app_goto_world(void)
{
    replace_page(PAGE_WORLD, wq_page_world_enter, wq_page_world_leave);
}

void wq_app_goto_levels(void)
{
    replace_page(PAGE_LEVELS, wq_page_levels_enter, wq_page_levels_leave);
}

void wq_app_goto_play(void)
{
    replace_page(PAGE_PLAY, wq_page_play_enter, wq_page_play_leave);
}

void wq_app_goto_result(void)
{
    replace_page(PAGE_RESULT, wq_page_result_enter, wq_page_result_leave);
}

wq_session_t *wq_app_session(void)
{
    return &s_session;
}

const wq_progress_t *wq_app_progress(void)
{
    return &s_progress;
}

uint8_t wq_app_volume(void)
{
    return s_volume;
}

uint16_t wq_app_volume_text(char *out, size_t capacity)
{
    return wq_volume_text(s_volume, out, capacity);
}

void wq_app_cycle_volume(void)
{
    s_volume = wq_volume_next(s_volume);
    wq_sfx_set_volume(s_volume);
    const esp_err_t err = wq_store_save_volume(s_volume);
    if (err != ESP_OK) {
        // 存不下来不影响本次使用，只影响下次开机 —— 记一笔就好，不打断用户。
        ESP_LOGW(TAG, "音量未能持久化：%s", esp_err_to_name(err));
    }
}

void wq_app_commit_result(void)
{
    // 只升不降：重打已通关的关，星级不会倒退。
    wq_progress_record_result(&s_progress, s_session.level, s_session.result_stars);
    s_progress.last_level = s_session.level;
    const esp_err_t err = wq_store_save(&s_progress);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "进度未能保存：%s", esp_err_to_name(err));
    }
}

void wq_app_reset_progress(void)
{
    wq_progress_reset(&s_progress);
    const esp_err_t err = wq_store_erase();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "清空记录未能落盘：%s", esp_err_to_name(err));
    }
}

void wq_app_key(wq_key_t key)
{
    // 拿不到锁就直接丢弃这次按键：宁可少响应一次，也不能在没锁的情况下碰 LVGL。
    if (!bsp_lvgl_lock(500)) {
        ESP_LOGW(TAG, "未能取得 LVGL 锁，本次按键被丢弃");
        return;
    }

    switch (s_page) {
        case PAGE_TITLE:  wq_page_title_key(key); break;
        case PAGE_WORLD:  wq_page_world_key(key); break;
        case PAGE_LEVELS: wq_page_levels_key(key); break;
        case PAGE_PLAY:   wq_page_play_key(key); break;
        case PAGE_RESULT: wq_page_result_key(key); break;
        default: break;
    }

    bsp_lvgl_unlock();
}

void wq_app_start(void)
{
    // 存档先读出来，标题页要用它显示「通关数 / 总星数」。读不到就是首次开机，
    // 存档层已经把这种情况当正常路径处理（复位成空档并返回 OK），所以这里
    // 只需要处理真正的失败。
    const esp_err_t err = wq_store_load(&s_progress);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "进度读取未成功（%s），按空档处理", esp_err_to_name(err));
    }

    // 音量档位。读不到（首次开机）时存档层已经把输出设成默认档位，所以这里
    // 不看返回值也能用；但真正的失败值得记一笔。
    uint8_t volume = WQ_VOLUME_DEFAULT;
    if (wq_store_load_volume(&volume) != ESP_OK) {
        ESP_LOGI(TAG, "无音量存档，用默认档位 %u%%", (unsigned)WQ_VOLUME_DEFAULT);
    }
    s_volume = volume;
    wq_sfx_set_volume(s_volume);

    wq_session_init(&s_session);
    s_page = PAGE_NONE;
    s_leave = NULL;
    s_screen = NULL;
    // 用 replace_page 而不是直接建页：这样「第一次进入」也走同一条路径，
    // 不会出现「首页特殊」这种只在一处存在的分支。
    wq_app_goto_title();
}
