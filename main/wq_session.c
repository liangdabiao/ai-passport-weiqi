// main/wq_session.c —— 见 wq_session.h。
// 不依赖 ESP-IDF 与 LVGL，宿主测试直接编译它。
#include "wq_session.h"

#include <string.h>

#include "wq_content.h"

// 第一条仍存活且还没走完的候选路径下标。找不到返回 correct_count。
static uint8_t first_alive(const wq_session_t *session)
{
    const wq_level_t *level = wq_session_level(session);
    if (!level) return 0;
    for (uint8_t ci = 0; ci < level->correct_count && ci < WQ_CORRECT_PATHS_MAX; ci++) {
        if (session->alive[ci]) return ci;
    }
    return level->correct_count;
}

// 复位作答状态：棋盘回初始、路径回起点。光标保留 —— 玩家刚在哪试，
// 下一次大概率还在那附近。走错复位与放弃重进共用这一条路径。
static void reset_attempt(wq_session_t *session)
{
    const wq_level_t *level = wq_session_level(session);
    wq_board_init(&session->board, level);
    session->depth = 0;
    for (uint8_t ci = 0; ci < WQ_CORRECT_PATHS_MAX; ci++) {
        session->alive[ci] = ci < level->correct_count;
    }
    session->removed_count = 0;
    session->board_dirty = true;
}

static void enter_solve(wq_session_t *session)
{
    const wq_level_t *level = wq_session_level(session);
    reset_attempt(session);

    // 光标初始位置：优先落在第一个字母标记点（题面说「下在 A 点」时，
    // A 就是起点），否则棋盘中心。从有子点再向前找到最近的空点。
    uint8_t start = WQ_BOARD_POINTS / 2;
    for (uint8_t mi = 0; mi < level->mark_count; mi++) {
        const char glyph = level->mark_glyphs[mi][0];
        if (glyph >= 'A' && glyph <= 'Z') {
            start = level->mark_points[mi];
            break;
        }
    }
    if (session->board.cells[start] != WQ_COLOR_EMPTY) {
        uint8_t found = start;
        for (uint8_t p = 0; p < WQ_BOARD_POINTS; p++) {
            if (session->board.cells[p] == WQ_COLOR_EMPTY) {
                found = p;
                break;
            }
        }
        start = found;
    }
    session->cursor = start;
    session->option = 0;
    session->stage = WQ_STAGE_SOLVE;
}

static wq_action_t pass_level(wq_session_t *session)
{
    // 与网页版 computeStars 一致：0 错 3 星、1 错 2 星、其余 1 星。
    session->result_stars =
        session->wrong_count == 0 ? WQ_STARS_FOR_ZERO_WRONG
        : session->wrong_count == 1 ? WQ_STARS_FOR_ONE_WRONG
                                    : WQ_STARS_FOR_REST;
    session->stage = WQ_STAGE_RESULT;
    return WQ_ACT_PASSED;
}

// puzzle：玩家落子。返回动作；内部维护路径匹配与对手应手。
static wq_action_t puzzle_move(wq_session_t *session, uint8_t point)
{
    const wq_level_t *level = wq_session_level(session);
    const uint8_t color = level->player;

    if (session->board.cells[point] != WQ_COLOR_EMPTY) return WQ_ACT_NONE;
    if (!wq_board_legal(&session->board, point, color)) return WQ_ACT_NONE; // 非法不罚

    // 这一手是否延续某条候选路径。
    bool extends[WQ_CORRECT_PATHS_MAX] = { false };
    bool any = false;
    for (uint8_t ci = 0; ci < level->correct_count && ci < WQ_CORRECT_PATHS_MAX; ci++) {
        if (!session->alive[ci]) continue;
        if (session->depth < level->correct[ci].len &&
            level->correct[ci].moves[session->depth] == point) {
            extends[ci] = true;
            any = true;
        }
    }
    if (!any) {
        session->wrong_count++;
        reset_attempt(session);
        return WQ_ACT_WRONG;
    }

    // 落子（合法性已由引擎与内容校验双保险）。
    const int captured = wq_board_place(&session->board, point, color);
    (void)captured;
    session->board_dirty = true;
    for (uint8_t ci = 0; ci < WQ_CORRECT_PATHS_MAX; ci++) {
        session->alive[ci] = session->alive[ci] && extends[ci];
    }
    session->depth++;

    // 走完任一条候选路径即过关。
    for (uint8_t ci = 0; ci < level->correct_count && ci < WQ_CORRECT_PATHS_MAX; ci++) {
        if (session->alive[ci] && session->depth >= level->correct[ci].len) {
            return pass_level(session);
        }
    }

    // 对手应手：取第一条存活路径的下一手（与网页引擎按分支序自动落子一致）。
    const uint8_t ci = first_alive(session);
    const wq_path_t *path = &level->correct[ci];
    const uint8_t reply = path->moves[session->depth];
    (void)wq_board_place(&session->board, reply, (uint8_t)(3 - color));
    session->board_dirty = true;
    session->depth++;
    // 收窄候选：应手不同的路径全部出局。
    for (uint8_t cj = 0; cj < level->correct_count && cj < WQ_CORRECT_PATHS_MAX; cj++) {
        if (!session->alive[cj]) continue;
        if (session->depth > level->correct[cj].len ||
            level->correct[cj].moves[session->depth - 1] != reply) {
            session->alive[cj] = false;
        }
    }
    return WQ_ACT_PLACED;
}

// END_REMOVE：选中一颗子。目标是死子则移除，凑齐过关；活子算走错。
static wq_action_t removal_pick(wq_session_t *session, uint8_t point)
{
    const wq_level_t *level = wq_session_level(session);

    if (session->board.cells[point] == WQ_COLOR_EMPTY) return WQ_ACT_NONE;

    for (uint8_t i = 0; i < level->target_count && i < WQ_REMOVAL_MAX; i++) {
        if (level->targets[i] != point) continue;
        // 已移除的不能再选。
        for (uint8_t r = 0; r < session->removed_count; r++) {
            if (session->removed[r] == point) return WQ_ACT_NONE;
        }
        session->removed[session->removed_count++] = point;
        session->board.cells[point] = WQ_COLOR_EMPTY;
        session->board_dirty = true;
        if (session->removed_count >= level->target_count) {
            return pass_level(session);
        }
        return WQ_ACT_PLACED;
    }

    // 活子：走错，移除进度清零重来。
    session->wrong_count++;
    reset_attempt(session);
    return WQ_ACT_WRONG;
}

// 由全局关卡号反推（章节下标, 章内光标）。关卡表按章节连续存放，
// wq_chapters 的 first/count 就是分段表。
static void locate_level(wq_session_t *session, uint16_t level)
{
    for (uint8_t ci = 0; ci < (uint8_t)WQ_CHAPTER_COUNT; ci++) {
        const wq_chapter_t *chapter = &wq_chapters[ci];
        if (level >= chapter->first && level < (uint16_t)(chapter->first + chapter->count)) {
            session->chapter = ci;
            session->level_cursor = (uint16_t)(level - chapter->first);
            return;
        }
    }
}

wq_action_t wq_session_key(wq_session_t *session, wq_key_t key)
{
    if (!session) return WQ_ACT_NONE;

    switch (session->stage) {
        case WQ_STAGE_WORLD: {
            const uint8_t count = (uint8_t)WQ_CHAPTER_COUNT;
            if (key == WQ_KEY_UP) {
                if (session->chapter == 0) return WQ_ACT_NONE;
                session->chapter--;
                return WQ_ACT_MOVED;
            }
            if (key == WQ_KEY_DOWN) {
                if (session->chapter + 1 >= count) return WQ_ACT_NONE;
                session->chapter++;
                return WQ_ACT_MOVED;
            }
            if (key == WQ_KEY_OK) {
                session->level_cursor = 0;
                session->stage = WQ_STAGE_LEVELS;
                return WQ_ACT_MOVED;
            }
            return WQ_ACT_NONE;
        }

        case WQ_STAGE_LEVELS: {
            const wq_chapter_t *chapter = &wq_chapters[session->chapter];
            if (key == WQ_KEY_UP) {
                if (session->level_cursor == 0) return WQ_ACT_NONE;
                session->level_cursor--;
                return WQ_ACT_MOVED;
            }
            if (key == WQ_KEY_DOWN) {
                if (session->level_cursor + 1 >= chapter->count) return WQ_ACT_NONE;
                session->level_cursor++;
                return WQ_ACT_MOVED;
            }
            if (key == WQ_KEY_OK) {
                session->level = (uint16_t)(chapter->first + session->level_cursor);
                session->wrong_count = 0;
                session->scroll = 0;
                session->scroll_max = 0;
                session->stage = WQ_STAGE_BRIEF;
                return WQ_ACT_ENTERED;
            }
            return WQ_ACT_NONE;
        }

        case WQ_STAGE_BRIEF: {
            if (key == WQ_KEY_UP) {
                if (session->scroll == 0) return WQ_ACT_NONE;
                session->scroll--;
                return WQ_ACT_MOVED;
            }
            if (key == WQ_KEY_DOWN) {
                if (session->scroll >= session->scroll_max) return WQ_ACT_NONE;
                session->scroll++;
                return WQ_ACT_MOVED;
            }
            if (key == WQ_KEY_OK) {
                enter_solve(session);
                return WQ_ACT_BOARD_READY;
            }
            if (key == WQ_KEY_BACK) {
                session->stage = WQ_STAGE_LEVELS;
                return WQ_ACT_LEFT;
            }
            return WQ_ACT_NONE;
        }

        case WQ_STAGE_SOLVE: {
            const wq_level_t *level = wq_session_level(session);
            if (key == WQ_KEY_BACK) {
                // 作答中长按：先回题面（再按一次才回关卡列表）。
                session->stage = WQ_STAGE_BRIEF;
                return WQ_ACT_LEFT;
            }

            if (level->kind == WQ_KIND_PUZZLE) {
                const uint8_t step = WQ_BOARD; // 行距
                if (key == WQ_KEY_UP) {
                    while (session->cursor >= step) {
                        session->cursor = (uint8_t)(session->cursor - step);
                        if (session->board.cells[session->cursor] == WQ_COLOR_EMPTY) break;
                    }
                    return WQ_ACT_MOVED;
                }
                if (key == WQ_KEY_DOWN) {
                    while (session->cursor + step < WQ_BOARD_POINTS) {
                        session->cursor = (uint8_t)(session->cursor + step);
                        if (session->board.cells[session->cursor] == WQ_COLOR_EMPTY) break;
                    }
                    return WQ_ACT_MOVED;
                }
                if (key == WQ_KEY_LEFT) {
                    while (session->cursor % WQ_BOARD > 0) {
                        session->cursor = (uint8_t)(session->cursor - 1);
                        if (session->board.cells[session->cursor] == WQ_COLOR_EMPTY) break;
                    }
                    return WQ_ACT_MOVED;
                }
                if (key == WQ_KEY_RIGHT) {
                    while (session->cursor % WQ_BOARD < WQ_BOARD - 1) {
                        session->cursor = (uint8_t)(session->cursor + 1);
                        if (session->board.cells[session->cursor] == WQ_COLOR_EMPTY) break;
                    }
                    return WQ_ACT_MOVED;
                }
                if (key == WQ_KEY_OK) return puzzle_move(session, session->cursor);
                return WQ_ACT_NONE;
            }

            if (level->kind == WQ_KIND_CHOICE) {
                if (key == WQ_KEY_UP) {
                    if (session->option == 0) return WQ_ACT_NONE;
                    session->option--;
                    return WQ_ACT_MOVED;
                }
                if (key == WQ_KEY_DOWN) {
                    if (session->option + 1 >= level->option_count) return WQ_ACT_NONE;
                    session->option++;
                    return WQ_ACT_MOVED;
                }
                if (key == WQ_KEY_OK) {
                    if (session->option == level->answer) {
                        return pass_level(session);
                    }
                    session->wrong_count++;
                    session->option = 0;
                    return WQ_ACT_WRONG;
                }
                return WQ_ACT_NONE;
            }

            if (level->kind == WQ_KIND_END_REMOVE) {
                // 光标同 puzzle（在有子点间也停下 —— 移除要在有子点上确认）。
                const uint8_t step = WQ_BOARD;
                if (key == WQ_KEY_UP) {
                    if (session->cursor >= step) session->cursor = (uint8_t)(session->cursor - step);
                    return WQ_ACT_MOVED;
                }
                if (key == WQ_KEY_DOWN) {
                    if (session->cursor + step < WQ_BOARD_POINTS) {
                        session->cursor = (uint8_t)(session->cursor + step);
                    }
                    return WQ_ACT_MOVED;
                }
                if (key == WQ_KEY_LEFT) {
                    if (session->cursor % WQ_BOARD > 0) session->cursor = (uint8_t)(session->cursor - 1);
                    return WQ_ACT_MOVED;
                }
                if (key == WQ_KEY_RIGHT) {
                    if (session->cursor % WQ_BOARD < WQ_BOARD - 1) {
                        session->cursor = (uint8_t)(session->cursor + 1);
                    }
                    return WQ_ACT_MOVED;
                }
                if (key == WQ_KEY_OK) return removal_pick(session, session->cursor);
                return WQ_ACT_NONE;
            }

            // END_PASS / END_FINISH：确定即完成。
            if (key == WQ_KEY_OK) return pass_level(session);
            return WQ_ACT_NONE;
        }

        case WQ_STAGE_RESULT: {
            if (key == WQ_KEY_OK) {
                if (wq_session_has_next(session)) {
                    session->level++;
                    locate_level(session, session->level);
                    session->wrong_count = 0;
                    session->scroll = 0;
                    session->scroll_max = 0;
                    session->stage = WQ_STAGE_BRIEF;
                    return WQ_ACT_ENTERED;
                }
                session->stage = WQ_STAGE_WORLD;
                return WQ_ACT_LEFT;
            }
            if (key == WQ_KEY_BACK) {
                session->stage = WQ_STAGE_LEVELS;
                return WQ_ACT_LEFT;
            }
            return WQ_ACT_NONE;
        }

        default:
            return WQ_ACT_NONE;
    }
}

void wq_session_init(wq_session_t *session)
{
    if (!session) return;
    for (size_t i = 0; i < sizeof(*session); i++) ((uint8_t *)session)[i] = 0;
    session->stage = WQ_STAGE_WORLD;
}

const wq_level_t *wq_session_level(const wq_session_t *session)
{
    if (!session || session->level >= (uint16_t)WQ_LEVEL_COUNT) return NULL;
    return &wq_levels[session->level];
}

bool wq_session_solved(const wq_session_t *session)
{
    return session && session->stage == WQ_STAGE_RESULT;
}

uint8_t wq_session_result_stars(const wq_session_t *session)
{
    return session ? session->result_stars : 0;
}

uint8_t wq_session_wrong_count(const wq_session_t *session)
{
    return session ? session->wrong_count : 0;
}

uint8_t wq_session_cursor(const wq_session_t *session)
{
    return session ? session->cursor : 0;
}

bool wq_session_removed(const wq_session_t *session, uint8_t point)
{
    if (!session) return false;
    for (uint8_t i = 0; i < session->removed_count; i++) {
        if (session->removed[i] == point) return true;
    }
    return false;
}

bool wq_session_has_next(const wq_session_t *session)
{
    if (!session) return false;
    return session->level + 1 < (uint16_t)WQ_LEVEL_COUNT;
}
