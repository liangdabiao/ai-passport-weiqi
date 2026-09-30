// main/wq_page_world.c —— 世界地图页：七个章节，按段位从青铜到王者。
//
// 章节名用 24px、行内不放进度数字 —— 「青铜 · 入门启蒙」八个全角字符本来就会
// 被右侧的 x/y 挤成省略号（真机反馈：文字被挤出去了），进度挪到底栏提示行，
// 行内只留标题，一行稳放。真机反馈：全部解锁，不做锁定。
#include "wq_app.h"

#include <stdio.h>
#include <string.h>

#include "wq_content.h"
#include "wq_sfx.h"
#include "wq_ui.h"

#define WORLD_ROWS (WQ_CHAPTER_COUNT > 6 ? 7 : WQ_CHAPTER_COUNT)
_Static_assert(WQ_CHAPTER_COUNT == 7, "世界地图按 7 章排；章数变了要重排版");

// 版式：7 行 x 36px 一行放不下（288 > 248），行高压到 32px、间隔压到 3px：
// 顶部 4 + 7x32 + 6x3 = 246 <= 248。
#define WORLD_ROW_H 32
#define WORLD_ROW_GAP 3
#define WORLD_ROWS_END \
    (WORLD_ROW_GAP + WORLD_ROWS * WORLD_ROW_H + (WORLD_ROWS - 1) * WORLD_ROW_GAP)
_Static_assert(WORLD_ROWS_END <= WQ_BODY_H, "章节行超出正文区，会被裁掉");

static wq_row_t s_rows[WORLD_ROWS];
static lv_obj_t *s_hint;
static char s_hint_text[48];
static int s_sel;

static void world_refresh(void)
{
    for (int index = 0; index < WORLD_ROWS; index++) {
        wq_row_update(&s_rows[index], NULL, wq_chapters[index].title, "",
                      index == s_sel ? WQ_STATE_SELECTED : WQ_STATE_NORMAL);
    }

    if (s_hint) {
        // 进度放提示行：行内放了它，八个字的章节名就要被挤成省略号。
        const wq_chapter_t *chapter = &wq_chapters[s_sel];
        uint16_t cleared = 0;
        for (uint16_t i = 0; i < chapter->count; i++) {
            if (wq_progress_stars(wq_app_progress(),
                                  (uint16_t)(chapter->first + i)) > 0) {
                cleared++;
            }
        }
        snprintf(s_hint_text, sizeof(s_hint_text), "已通关 %u/%u · 确定进入",
                 (unsigned)cleared, (unsigned)chapter->count);
        lv_label_set_text(s_hint, s_hint_text);
    }
}

static void world_activate(void)
{
    wq_sfx_play(WQ_TONE_ENTER);
    wq_app_goto_levels();
}

lv_obj_t *wq_page_world_enter(void)
{
    // 会话里的章节光标即页面状态；进来时夹取一次，防止越界。
    if (wq_app_session()->chapter >= WQ_CHAPTER_COUNT) {
        wq_app_session()->chapter = 0;
    }
    s_sel = wq_app_session()->chapter;
    s_hint = NULL;
    for (int index = 0; index < WORLD_ROWS; index++) s_rows[index] = (wq_row_t){0};

    lv_obj_t *card = NULL;
    lv_obj_t *screen = wq_page_create(&card);
    if (!card) return screen;

    wq_topbar_t bar = wq_topbar_create(card, "世界地图", &wq_font_16);
    wq_topbar_set_right(&bar, "章节");
    s_hint = wq_hint_create(card, "");
    lv_obj_t *body = wq_body_create(card);

    for (int index = 0; index < WORLD_ROWS; index++) {
        const int y = WORLD_ROW_GAP + index * (WORLD_ROW_H + WORLD_ROW_GAP);
        s_rows[index] = wq_row_create(body, WQ_BODY_X, y, WQ_BODY_W, WORLD_ROW_H,
                                      0, 56);
    }

    world_refresh();
    return screen;
}

void wq_page_world_leave(void)
{
    s_hint = NULL;
    for (int index = 0; index < WORLD_ROWS; index++) s_rows[index] = (wq_row_t){0};
}

void wq_page_world_key(wq_key_t key)
{
    wq_session_t *session = wq_app_session();

    switch (key) {
        case WQ_KEY_UP:
            if (s_sel == 0) return;
            s_sel--;
            session->chapter = (uint8_t)s_sel;
            wq_sfx_play(WQ_TONE_MOVE);
            world_refresh();
            return;

        case WQ_KEY_DOWN:
            if (s_sel + 1 >= WORLD_ROWS) return;
            s_sel++;
            session->chapter = (uint8_t)s_sel;
            wq_sfx_play(WQ_TONE_MOVE);
            world_refresh();
            return;

        case WQ_KEY_OK:
            session->chapter = (uint8_t)s_sel;
            world_activate();
            return;

        case WQ_KEY_BACK:
            wq_sfx_play(WQ_TONE_BACK);
            wq_app_goto_title();
            return;

        default:
            return;
    }
}
