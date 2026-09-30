// main/wq_page_levels.c —— 关卡列表页：当前章节的关卡，序号 + 标题 + 星级。
//
// 章内最多 30 关，一屏至多放下 5 行 36px；列表做成滑动窗口：光标动，窗口跟着
// 滚（与手机上按方向键翻列表一致）。行内左侧是章内序号（16px），中间标题
// （16px，最长 13 字），右侧星级（16px 的 ★☆）。
//
// 「进入未解锁的关卡」在页面这一层就拒绝 —— 存档在应用层，session 不持有它；
// 拒绝时抖一下边框颜色（红）并响错误音，不改会话状态。
#include "wq_app.h"

#include <stdio.h>
#include <string.h>

#include "wq_content.h"
#include "wq_sfx.h"
#include "wq_ui.h"

// 一屏行数：正文区 248px，36 + 6 一行 42px，5 行 210px、6 行 246px；
// 取 5 行留出窗口上下喘息（6 行会顶满，滑动窗口没有余量）。
#define LEVELS_VISIBLE 5
#define LEVELS_ROW_W_TAG 26
#define LEVELS_ROW_W_NOTE 52

static wq_row_t s_rows[LEVELS_VISIBLE];
static lv_obj_t *s_hint;
static wq_topbar_t s_bar;
static int s_window;   // 窗口起始的章内偏移
static bool s_denied;  // 拒绝进入时的提示状态（下次按键即清除）

static const wq_chapter_t *current_chapter(void)
{
    return &wq_chapters[wq_app_session()->chapter];
}

static void levels_clamp_window(void)
{
    const wq_session_t *session = wq_app_session();
    const wq_chapter_t *chapter = current_chapter();
    if (session->level_cursor < (uint16_t)s_window) {
        s_window = session->level_cursor;
    }
    if (session->level_cursor >= (uint16_t)(s_window + LEVELS_VISIBLE)) {
        s_window = session->level_cursor - LEVELS_VISIBLE + 1;
    }
    if (s_window < 0) s_window = 0;
    const int max_window = (int)chapter->count - LEVELS_VISIBLE;
    if (s_window > max_window) s_window = max_window > 0 ? max_window : 0;
}

static void levels_refresh(void)
{
    const wq_session_t *session = wq_app_session();
    const wq_chapter_t *chapter = current_chapter();
    levels_clamp_window();

    const wq_progress_t *progress = wq_app_progress();
    for (int row = 0; row < LEVELS_VISIBLE; row++) {
        const int offset = s_window + row;
        if (offset >= (int)chapter->count) {
            wq_row_update(&s_rows[row], "", "", "", WQ_STATE_NORMAL);
            continue;
        }
        const uint16_t level = (uint16_t)(chapter->first + offset);
        const wq_level_t *data = &wq_levels[level];
        const uint8_t stars = wq_progress_stars(progress, level);
        const bool unlocked = wq_progress_unlocked(progress, level);

        char tag[16];
        snprintf(tag, sizeof(tag), "%u", (unsigned)(offset + 1));
        char note[12];
        if (stars > 0) {
            snprintf(note, sizeof(note), "%.*s%.*s",
                     stars, "★★★", 3 - stars, "☆☆☆");
        } else {
            snprintf(note, sizeof(note), "%s", unlocked ? "　" : "锁");
        }

        wq_state_t state;
        if (offset == (int)session->level_cursor) {
            state = WQ_STATE_SELECTED;
        } else if (stars > 0) {
            state = WQ_STATE_GOOD;
        } else if (!unlocked) {
            state = WQ_STATE_DISABLED;
        } else {
            state = WQ_STATE_NORMAL;
        }
        wq_row_update(&s_rows[row], tag, data->title, note, state);
    }

    wq_topbar_set_left(&s_bar, chapter->title);
    char progress_text[16];
    uint16_t cleared = 0;
    for (uint16_t i = 0; i < chapter->count; i++) {
        if (wq_progress_stars(progress, (uint16_t)(chapter->first + i)) > 0) cleared++;
    }
    snprintf(progress_text, sizeof(progress_text), "%u/%u", (unsigned)cleared,
             (unsigned)chapter->count);
    wq_topbar_set_right(&s_bar, progress_text);

    if (s_hint) {
        if (s_denied) {
            lv_label_set_text(s_hint, "先通关上一关，才能进这一关");
        } else {
            lv_label_set_text(s_hint, "确定 进入关卡 · 长按 返回地图");
        }
    }
}

lv_obj_t *wq_page_levels_enter(void)
{
    wq_session_t *session = wq_app_session();
    const wq_chapter_t *chapter = current_chapter();
    // 会话的章内光标夹取（从结算页跳章时可能越界）。
    if (session->level_cursor >= chapter->count) {
        session->level_cursor = 0;
    }
    s_window = 0;
    s_denied = false;
    s_hint = NULL;
    for (int row = 0; row < LEVELS_VISIBLE; row++) s_rows[row] = (wq_row_t){0};

    lv_obj_t *card = NULL;
    lv_obj_t *screen = wq_page_create(&card);
    if (!card) return screen;

    s_bar = wq_topbar_create(card, "", &wq_font_16);
    s_hint = wq_hint_create(card, "");
    lv_obj_t *body = wq_body_create(card);

    for (int row = 0; row < LEVELS_VISIBLE; row++) {
        const int y = row * (WQ_ROW_H + WQ_ROW_GAP);
        s_rows[row] = wq_row_small_create(body, WQ_BODY_X, y, WQ_BODY_W, WQ_ROW_H,
                                          LEVELS_ROW_W_TAG, LEVELS_ROW_W_NOTE);
    }

    levels_refresh();
    return screen;
}

void wq_page_levels_leave(void)
{
    s_hint = NULL;
    for (int row = 0; row < LEVELS_VISIBLE; row++) s_rows[row] = (wq_row_t){0};
}

void wq_page_levels_key(wq_key_t key)
{
    wq_session_t *session = wq_app_session();
    const wq_chapter_t *chapter = current_chapter();
    s_denied = false;

    switch (key) {
        case WQ_KEY_UP:
            if (session->level_cursor == 0) return;
            session->level_cursor--;
            wq_sfx_play(WQ_TONE_MOVE);
            levels_refresh();
            return;

        case WQ_KEY_DOWN:
            if (session->level_cursor + 1 >= chapter->count) return;
            session->level_cursor++;
            wq_sfx_play(WQ_TONE_MOVE);
            levels_refresh();
            return;

        case WQ_KEY_OK: {
            session->level = (uint16_t)(chapter->first + session->level_cursor);
            if (!wq_progress_unlocked(wq_app_progress(), session->level)) {
                s_denied = true;
                wq_sfx_play(WQ_TONE_WRONG);
                levels_refresh();
                return;
            }
            session->wrong_count = 0;
            session->scroll = 0;
            session->scroll_max = 0;
            session->stage = WQ_STAGE_BRIEF;
            wq_sfx_play(WQ_TONE_ENTER);
            wq_app_goto_play();
            return;
        }

        case WQ_KEY_BACK:
            session->stage = WQ_STAGE_WORLD;
            wq_sfx_play(WQ_TONE_BACK);
            wq_app_goto_world();
            return;

        default:
            return;
    }
}
