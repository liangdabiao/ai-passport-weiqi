// main/wq_page_world.c —— 世界地图页：七个章节，按段位从青铜到王者。
//
// 章节名用 24px（最长 8 个全角字符，188px 的行内放得下）；该章的进度放底栏
// 提示行 —— 行内右侧还要留给「锁定」提示，塞不下第二组数字。
// 章节「可进入」的判定：它的第一关已解锁（即上一章最后一关已通关）。
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

static bool chapter_enterable(int index)
{
    const wq_chapter_t *chapter = &wq_chapters[index];
    return wq_progress_unlocked(wq_app_progress(), chapter->first);
}

static void world_refresh(void)
{
    for (int index = 0; index < WORLD_ROWS; index++) {
        char note[16];
        const wq_chapter_t *chapter = &wq_chapters[index];
        uint16_t cleared = 0;
        for (uint16_t i = 0; i < chapter->count; i++) {
            if (wq_progress_stars(wq_app_progress(),
                                  (uint16_t)(chapter->first + i)) > 0) {
                cleared++;
            }
        }
        snprintf(note, sizeof(note), "%u/%u", (unsigned)cleared,
                 (unsigned)chapter->count);
        const bool enterable = chapter_enterable(index);
        wq_state_t state;
        if (index == s_sel) {
            state = WQ_STATE_SELECTED;
        } else if (!enterable) {
            state = WQ_STATE_DISABLED;
        } else {
            state = WQ_STATE_NORMAL;
        }
        wq_row_update(&s_rows[index], NULL, chapter->title,
                      enterable ? note : "锁定", state);
    }

    if (s_hint) {
        const wq_chapter_t *chapter = &wq_chapters[s_sel];
        if (chapter_enterable(s_sel)) {
            snprintf(s_hint_text, sizeof(s_hint_text), "%u 关 · 确定进入 · 长按返回",
                     (unsigned)chapter->count);
        } else {
            snprintf(s_hint_text, sizeof(s_hint_text), "通关上一章后解锁");
        }
        lv_label_set_text(s_hint, s_hint_text);
    }
}

static void world_activate(void)
{
    if (!chapter_enterable(s_sel)) {
        wq_sfx_play(WQ_TONE_WRONG);
        return;
    }
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
    wq_topbar_set_right(&bar, "关卡进度");
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
