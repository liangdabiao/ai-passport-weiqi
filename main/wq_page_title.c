// main/wq_page_title.c —— 标题页：一个大标题、三项菜单、一行成绩。
//
// 只有三项，第一项就是「继续闯关」—— 打开机器按两下就能下棋，不需要先翻目录。
// 三个键的菜单项数越多越容易迷失。
#include "wq_app.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "wq_content.h"
#include "wq_sfx.h"
#include "wq_store.h"
#include "wq_ui.h"

#define TITLE_ITEMS 3

static const char *const TITLE_LABEL[TITLE_ITEMS] = {
    "继续闯关",
    "音量",
    "重置记录",
};

// 三项菜单里右侧小字要放得下「已重置」这种四字提示。
#define TITLE_NOTE_W 72
// 版式（相对页面卡，正文区高 WQ_BODY_H = 248）：顶栏 0..36 / 大字 42..82 /
// 成绩 88..108 / 菜单 124..240 / 底栏 284..310
//
// 与侨批同一块屏：正文区外的元素会被 LVGL 裁掉、真机不可见（侨批标题页成绩行
// 曾在 250 被裁），所以这里的每一个 y 都用断言钉在编译期。
#define TITLE_HEADLINE_Y 42
#define TITLE_HEADLINE_H  40
#define TITLE_STATS_Y     88
#define TITLE_STATS_H     20   // 16px 字库的行高
#define TITLE_MENU_Y      124

#define TITLE_MENU_END \
    (TITLE_MENU_Y + (TITLE_ITEMS - 1) * (WQ_ROW_H + WQ_ROW_GAP) + WQ_ROW_H)
_Static_assert(TITLE_MENU_END <= WQ_BODY_H, "菜单最后一行超出正文区，会被裁掉");
_Static_assert(TITLE_STATS_Y + TITLE_STATS_H <= WQ_BODY_H, "成绩行超出正文区，会被裁掉");
_Static_assert(TITLE_STATS_Y + TITLE_STATS_H <= TITLE_MENU_Y, "成绩行会与菜单重叠");

static wq_row_t s_rows[TITLE_ITEMS];
static lv_obj_t *s_hint;
static lv_obj_t *s_stats;
static int s_sel;
// 重置记录要按两次：第一次「上膛」，第二次才真的清。在只有三个键的机器上，
// 一步就把记录抹掉太容易误触。
static bool s_confirm_reset;

static void title_refresh(void)
{
    const wq_progress_t *progress = wq_app_progress();

    char notes[TITLE_ITEMS][16];
    notes[0][0] = '\0';
    // 音量档位：0 档的文本就是「关」。
    (void)wq_app_volume_text(notes[1], sizeof(notes[1]));
    snprintf(notes[2], sizeof(notes[2]), "%s", s_confirm_reset ? "再按一次" : "");

    for (int index = 0; index < TITLE_ITEMS; index++) {
        wq_row_update(&s_rows[index], NULL, TITLE_LABEL[index], notes[index],
                      index == s_sel ? WQ_STATE_SELECTED : WQ_STATE_NORMAL);
    }

    if (s_stats && progress) {
        char stats[64];
        // 「通关」+「星」+ 两个分隔符 = 7 个字 21 字节，三个数字至多 33 字节，
        // 64 字节有充足余量。
        snprintf(stats, sizeof(stats),
                 "通关 %u/%u · ★%lu",
                 (unsigned)wq_progress_cleared_count(progress),
                 (unsigned)WQ_LEVEL_COUNT,
                 (unsigned long)wq_progress_total_stars(progress));
        lv_label_set_text(s_stats, stats);
    }

    if (s_hint) {
        if (s_confirm_reset) {
            lv_label_set_text(s_hint, "再按一次确定即清空记录");
        } else if (s_sel == 1) {
            lv_label_set_text(s_hint, "确定 切换音量档位");
        } else {
            lv_label_set_text(s_hint, "上下选择 · 确定进入");
        }
    }
}

static void title_activate(void)
{
    switch (s_sel) {
        case 0:
            wq_sfx_play(WQ_TONE_ENTER);
            wq_app_goto_world();
            return;

        case 1:
            // 先改档位、再响提示音：从「关」往上调的那一次，提示音必须按**新**档位
            // 响出来。顺序反过来会静默 —— 关档时音效被直接丢弃。
            wq_app_cycle_volume();
            wq_sfx_play(WQ_TONE_ENTER);
            title_refresh();
            return;

        case 2:
            if (!s_confirm_reset) {
                s_confirm_reset = true;
                wq_sfx_play(WQ_TONE_ENTER);
                title_refresh();
                return;
            }
            wq_sfx_play(WQ_TONE_BACK);
            wq_app_reset_progress();
            s_confirm_reset = false;
            title_refresh();
            return;

        default:
            return;
    }
}

lv_obj_t *wq_page_title_enter(void)
{
    s_sel = 0;
    s_confirm_reset = false;
    s_hint = NULL;
    s_stats = NULL;
    for (int index = 0; index < TITLE_ITEMS; index++) s_rows[index] = (wq_row_t){0};

    lv_obj_t *card = NULL;
    lv_obj_t *screen = wq_page_create(&card);
    if (!card) return screen;

    wq_topbar_t bar = wq_topbar_create(card, "围棋闯关", &wq_font_16);
    wq_topbar_add_battery(&bar);
    s_hint = wq_hint_create(card, "");
    lv_obj_t *body = wq_body_create(card);

    lv_obj_t *headline = wq_headline_create(body, WQ_BODY_X, TITLE_HEADLINE_Y,
                                             WQ_BODY_W, TITLE_HEADLINE_H, WQ_C_GOLD);
    lv_label_set_text(headline, "围棋闯关");

    s_stats = wq_note_create(body, WQ_BODY_X, TITLE_STATS_Y, WQ_BODY_W, "",
                             WQ_C_MUTED);

    for (int index = 0; index < TITLE_ITEMS; index++) {
        const int y = TITLE_MENU_Y + index * (WQ_ROW_H + WQ_ROW_GAP);
        s_rows[index] = wq_row_create(body, WQ_BODY_X, y, WQ_BODY_W, WQ_ROW_H,
                                      0, TITLE_NOTE_W);
    }

    title_refresh();
    return screen;
}

void wq_page_title_leave(void)
{
    s_hint = NULL;
    s_stats = NULL;
    s_confirm_reset = false;
    for (int index = 0; index < TITLE_ITEMS; index++) s_rows[index] = (wq_row_t){0};
}

void wq_page_title_key(wq_key_t key)
{
    switch (key) {
        case WQ_KEY_UP:
            if (s_sel == 0) return;
            s_sel--;
            s_confirm_reset = false;
            wq_sfx_play(WQ_TONE_MOVE);
            title_refresh();
            return;

        case WQ_KEY_DOWN:
            if (s_sel + 1 >= TITLE_ITEMS) return;
            s_sel++;
            s_confirm_reset = false;
            wq_sfx_play(WQ_TONE_MOVE);
            title_refresh();
            return;

        case WQ_KEY_OK:
            title_activate();
            return;

        case WQ_KEY_BACK:
            // 标题页是根，长按什么也不做 —— 在一块不能关机的板子上，
            // 「退出应用」没有意义。
            if (s_confirm_reset) {
                s_confirm_reset = false;
                title_refresh();
            }
            return;

        default:
            return;
    }
}
