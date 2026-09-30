// main/wq_page_play.c —— 作答页：题面 / 落子 / 选择 / 终局，一个页面三种形态。
//
// 形态由 session 阶段决定：
//   BRIEF        题面：可滚动容器里放说明（选择题先放小棋盘再放题干）
//   SOLVE+棋类   落子：9x9 棋盘 + 底部状态行（puzzle / 终局三态共用）
//   SOLVE+选择题 选择：题面页的样子 + 选项行，光标在选项间移动
//
// 棋盘光标的移动规则（也是全应用唯一的「二维光标」，真机反馈后从长按改成双击）：
//   上 / 下 短按 = 上下移一行；上 / 下 双击 = 左右移一列。
//   光标只在空点上停（puzzle）；移除死子（END_REMOVE）时在有子点上停。
//   走到头就停在头 —— 不绕圈，绕圈会让「我到底在第几行」失去参照。
#include "wq_app.h"

#include <stdio.h>
#include <string.h>

#include "wq_content.h"
#include "wq_sfx.h"
#include "wq_ui.h"

// 落子形态的棋盘位置：视图 206px 在 230px 宽的正文里水平居中，顶部留 2px。
#define SOLVE_BOARD_X ((WQ_PAGE_W - WQ_BOARD_VIEW_PX(WQ_BOARD_CELL)) / 2)
#define SOLVE_BOARD_Y 2
#define SOLVE_NOTE_Y  (SOLVE_BOARD_Y + WQ_BOARD_VIEW_PX(WQ_BOARD_CELL) + 4)
#define SOLVE_NOTE_H  20
_Static_assert(SOLVE_NOTE_Y + SOLVE_NOTE_H <= WQ_BODY_H,
               "棋盘加状态行超出正文区，会被裁掉");
_Static_assert(WQ_BOARD_VIEW_PX(WQ_BOARD_CELL) <= WQ_PAGE_W, "棋盘比正文区还宽");

// 选择题形态：小棋盘 + 题干 + 选项行，全部放进滚动容器。
#define CHOICE_BOARD_X ((WQ_PAGE_W - WQ_BOARD_VIEW_PX(WQ_BOARD_CELL_SMALL)) / 2)
#define CHOICE_TEXT_GAP 6
#define CHOICE_OPTION_H WQ_ROW_H
#define CHOICE_OPTION_GAP WQ_ROW_GAP

static lv_obj_t *s_body;
static lv_obj_t *s_hint;
static wq_topbar_t s_bar;
// 题面形态
static lv_obj_t *s_scroll;
static lv_obj_t *s_text;
static wq_board_view_t s_small_board;
static bool s_small_board_used;
// 落子形态
static wq_board_view_t s_board;
static lv_obj_t *s_note;
// 选择题形态
static wq_row_t s_options[WQ_OPTIONS_MAX];
static lv_obj_t *s_question;

static const wq_level_t *current_level(void)
{
    return wq_session_level(wq_app_session());
}

static void reset_pointers(void)
{
    s_scroll = NULL;
    s_text = NULL;
    s_question = NULL;
    s_note = NULL;
    s_small_board_used = false;
    for (int i = 0; i < WQ_OPTIONS_MAX; i++) s_options[i] = (wq_row_t){0};
}

static void topbar_refresh(void)
{
    const wq_session_t *session = wq_app_session();
    const wq_level_t *level = current_level();
    if (!level) return;
    wq_topbar_set_left(&s_bar, level->title);
    char progress[16];
    snprintf(progress, sizeof(progress), "%u/%u",
             (unsigned)(session->level + 1), (unsigned)WQ_LEVEL_COUNT);
    wq_topbar_set_right(&s_bar, progress);
}

// ---- 题面形态 ----

static void render_brief(void)
{
    reset_pointers();
    lv_obj_clean(s_body);

    const wq_session_t *session = wq_app_session();
    const wq_level_t *level = current_level();
    if (!level) return;

    s_scroll = wq_scroll_create(s_body);
    int y = 2;

    if (level->kind == WQ_KIND_CHOICE) {
        // 小棋盘居中，题干跟在下面 —— 题干常引用棋面上的标记（A 点 / 1 号子）。
        s_small_board_used = true;
        wq_board_view_create(&s_small_board, s_scroll, CHOICE_BOARD_X, y,
                             WQ_BOARD_CELL_SMALL);
        wq_board_view_sync(&s_small_board, session);
        wq_board_view_hide_cursor(&s_small_board);
        y += WQ_BOARD_VIEW_PX(WQ_BOARD_CELL_SMALL) + CHOICE_TEXT_GAP;

        s_question = wq_paragraph_create(s_scroll, WQ_BODY_X, y, WQ_BODY_W,
                                         LV_SIZE_CONTENT, &wq_font_16, WQ_C_INK);
        wq_text_set(s_question, level->question, WQ_CHARS_SMALL);
    } else {
        s_text = wq_paragraph_create(s_scroll, WQ_BODY_X, y, WQ_BODY_W,
                                     LV_SIZE_CONTENT, &wq_font_16, WQ_C_INK);
        wq_text_set(s_text, level->instruction, WQ_CHARS_SMALL);
    }

    if (s_hint) {
        lv_label_set_text(s_hint, level->kind == WQ_KIND_CHOICE
                                      ? "确定 作答 · 长按 返回"
                                      : "确定 开始 · 长按 返回");
    }
}

// ---- 落子形态 ----

static void solve_note_refresh(void)
{
    if (!s_note) return;
    const wq_session_t *session = wq_app_session();
    const wq_level_t *level = current_level();
    char note[48];
    switch (level->kind) {
        case WQ_KIND_PUZZLE:
            if (session->wrong_count > 0) {
                snprintf(note, sizeof(note), "错误 %u · 走错即复位重开",
                         (unsigned)session->wrong_count);
            } else {
                snprintf(note, sizeof(note), "执%s 先行",
                         level->player == WQ_COLOR_BLACK ? "黑" : "白");
            }
            break;
        case WQ_KIND_END_REMOVE:
            snprintf(note, sizeof(note), "已移除 %u/%u 颗死子",
                     (unsigned)session->removed_count, (unsigned)level->target_count);
            break;
        case WQ_KIND_END_PASS:
            snprintf(note, sizeof(note), "确定 = 停一手");
            break;
        case WQ_KIND_END_FINISH:
            snprintf(note, sizeof(note), "确定 = 完成终局");
            break;
        default:
            note[0] = '\0';
            break;
    }
    lv_label_set_text(s_note, note);
}

static void choice_paint_options(void)
{
    const wq_session_t *session = wq_app_session();
    const wq_level_t *level = current_level();
    if (!level) return;
    static const char *const SLOTS[] = { "甲", "乙", "丙", "丁" };
    for (uint8_t i = 0; i < level->option_count && i < WQ_OPTIONS_MAX; i++) {
        wq_row_update(&s_options[i], SLOTS[i], level->options[i], "",
                      i == session->option ? WQ_STATE_SELECTED : WQ_STATE_NORMAL);
    }
    lv_obj_t *selected = s_options[session->option].box;
    if (selected) lv_obj_scroll_to_view(selected, LV_ANIM_OFF);
}

static void render_solve(void)
{
    reset_pointers();
    lv_obj_clean(s_body);

    const wq_session_t *session = wq_app_session();
    const wq_level_t *level = current_level();
    if (!level) return;

    if (level->kind == WQ_KIND_CHOICE) {
        // 选择题：题面页的样子 + 选项行。选项光标由 session 维护，
        // 页面把选中的行滚进可视区。
        s_scroll = wq_scroll_create(s_body);
        int y = 2;
        s_small_board_used = true;
        wq_board_view_create(&s_small_board, s_scroll, CHOICE_BOARD_X, y,
                             WQ_BOARD_CELL_SMALL);
        wq_board_view_sync(&s_small_board, session);
        wq_board_view_hide_cursor(&s_small_board);
        y += WQ_BOARD_VIEW_PX(WQ_BOARD_CELL_SMALL) + CHOICE_TEXT_GAP;

        s_question = wq_paragraph_create(s_scroll, WQ_BODY_X, y, WQ_BODY_W,
                                         LV_SIZE_CONTENT, &wq_font_16, WQ_C_INK);
        wq_text_set(s_question, level->question, WQ_CHARS_SMALL);
        lv_obj_update_layout(s_question);
        y += lv_obj_get_height(s_question) + CHOICE_TEXT_GAP;

        for (uint8_t i = 0; i < level->option_count && i < WQ_OPTIONS_MAX; i++) {
            s_options[i] = wq_row_small_create(s_scroll, WQ_BODY_X, y, WQ_BODY_W,
                                               CHOICE_OPTION_H, 26, 0);
            y += CHOICE_OPTION_H + CHOICE_OPTION_GAP;
        }
        choice_paint_options();

        if (s_hint) lv_label_set_text(s_hint, "上下选择 · 确定作答");
        return;
    }

    // 棋类：棋盘 + 状态行。
    wq_board_view_create(&s_board, s_body, SOLVE_BOARD_X, SOLVE_BOARD_Y,
                         WQ_BOARD_CELL);
    wq_board_view_sync(&s_board, session);
    s_note = wq_note_create(s_body, WQ_BODY_X, SOLVE_NOTE_Y, WQ_BODY_W, "",
                            WQ_C_MUTED);
    solve_note_refresh();

    if (s_hint) {
        lv_label_set_text(s_hint, level->kind == WQ_KIND_PUZZLE
                                      ? "双击上下移列 · 确定落子"
                                      : "确定 确认 · 长按 返回题面");
    }
}

void wq_page_play_refresh(void)
{
    const wq_session_t *session = wq_app_session();
    topbar_refresh();
    if (session->stage == WQ_STAGE_BRIEF) {
        render_brief();
    } else {
        render_solve();
    }
}

lv_obj_t *wq_page_play_enter(void)
{
    s_body = NULL;
    s_hint = NULL;
    reset_pointers();

    lv_obj_t *card = NULL;
    lv_obj_t *screen = wq_page_create(&card);
    if (!card) return screen;

    s_bar = wq_topbar_create(card, "", &wq_font_16);
    s_hint = wq_hint_create(card, "");
    s_body = wq_body_create(card);

    wq_page_play_refresh();
    return screen;
}

void wq_page_play_leave(void)
{
    s_body = NULL;
    s_hint = NULL;
    reset_pointers();
}

void wq_page_play_key(wq_key_t key)
{
    wq_session_t *session = wq_app_session();
    const wq_level_t *level = current_level();
    if (!level) return;

    if (session->stage == WQ_STAGE_BRIEF) {
        // 题面：滚动交给 LVGL 容器，会话只记进度（回进来时还在原地）。
        if (key == WQ_KEY_UP || key == WQ_KEY_DOWN) {
            if (s_scroll) {
                const int step = 24;
                lv_obj_scroll_by(s_scroll, 0, key == WQ_KEY_UP ? step : -step,
                                 LV_ANIM_OFF);
                session->scroll =
                    (uint16_t)(lv_obj_get_scroll_y(s_scroll) / step);
            }
            return;
        }
        const wq_action_t action = wq_session_key(session, key);
        if (action == WQ_ACT_BOARD_READY) {
            wq_sfx_play(WQ_TONE_ENTER);
            wq_page_play_refresh();
        } else if (action == WQ_ACT_LEFT) {
            wq_sfx_play(WQ_TONE_BACK);
            wq_app_goto_levels();
        }
        return;
    }

    const wq_action_t action = wq_session_key(session, key);
    switch (action) {
        case WQ_ACT_MOVED:
            wq_sfx_play(WQ_TONE_MOVE);
            if (level->kind == WQ_KIND_CHOICE) {
                // 选项光标动了：原位重画选项（不重建容器，保住滚动位置）。
                choice_paint_options();
            } else if (s_board.box) {
                wq_board_view_sync(&s_board, session);
            }
            return;

        case WQ_ACT_PLACED:
            wq_sfx_play(level->kind == WQ_KIND_END_REMOVE ? WQ_TONE_CAPTURE
                                                          : WQ_TONE_PLACE);
            if (s_board.box) wq_board_view_sync(&s_board, session);
            solve_note_refresh();
            return;

        case WQ_ACT_WRONG:
            wq_sfx_play(WQ_TONE_WRONG);
            if (level->kind == WQ_KIND_CHOICE) {
                choice_paint_options(); // 选项光标被会话拨回第一个
            } else if (s_board.box) {
                wq_board_view_sync(&s_board, session);
            }
            solve_note_refresh();
            return;

        case WQ_ACT_PASSED: {
            // 章末关用更明亮的通关音。
            const wq_chapter_t *chapter = &wq_chapters[session->chapter];
            const bool chapter_end =
                session->level + 1 >= (uint16_t)(chapter->first + chapter->count);
            wq_sfx_play(chapter_end ? WQ_TONE_COMPLETE : WQ_TONE_CORRECT);
            wq_app_commit_result();
            wq_app_goto_result();
            return;
        }

        case WQ_ACT_LEFT:
            // 作答中长按返回：先回题面（会话已把阶段退回 BRIEF）。
            wq_sfx_play(WQ_TONE_BACK);
            wq_page_play_refresh();
            return;

        default:
            return;
    }
}
