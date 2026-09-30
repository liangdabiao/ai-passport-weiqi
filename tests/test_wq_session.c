// tests/test_wq_session.c —— 闯关状态机：全题库通关、判题、走错复位、终局。
//
// 核心用例是把 154 关**全部真打通**一遍：每关用内容里的第一条正解路径喂键，
// 必须恰好走到结算；这等价于「设备上每一关都确实可通关」的机器证明。
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "wq_session.h"

static void enter_level(wq_session_t *session, uint16_t level)
{
    session->level = level;
    session->stage = WQ_STAGE_BRIEF;
    assert(wq_session_key(session, WQ_KEY_OK) == WQ_ACT_BOARD_READY);
    assert(session->stage == WQ_STAGE_SOLVE);
}

static void test_full_playthrough(void)
{
    wq_session_t session;
    wq_session_init(&session);
    session.level_cursor = 0;

    unsigned puzzle = 0, choice = 0, ending = 0;
    for (uint16_t li = 0; li < (uint16_t)WQ_LEVEL_COUNT; li++) {
        enter_level(&session, li);
        const wq_level_t *level = wq_session_level(&session);
        assert(level == &wq_levels[li]);

        switch (level->kind) {
            case WQ_KIND_PUZZLE: {
                const wq_path_t *path = &level->correct[0];
                for (uint8_t mi = 0; mi < path->len; mi += 2) {
                    // 玩家手在路径的偶数位；把光标摆到落点再按确定。
                    session.cursor = path->moves[mi];
                    const wq_action_t placed = wq_session_key(&session, WQ_KEY_OK);
                    assert(placed == WQ_ACT_PLACED || placed == WQ_ACT_PASSED);
                }
                puzzle++;
                break;
            }
            case WQ_KIND_CHOICE: {
                // 把选项光标拨到正确项再确认。
                for (uint8_t k = 0; k < level->answer; k++) {
                    assert(wq_session_key(&session, WQ_KEY_DOWN) == WQ_ACT_MOVED);
                }
                assert(wq_session_key(&session, WQ_KEY_OK) == WQ_ACT_PASSED);
                choice++;
                break;
            }
            case WQ_KIND_END_REMOVE: {
                for (uint8_t ti = 0; ti < level->target_count; ti++) {
                    session.cursor = level->targets[ti];
                    const wq_action_t removed = wq_session_key(&session, WQ_KEY_OK);
                    assert(removed == WQ_ACT_PLACED || removed == WQ_ACT_PASSED);
                }
                ending++;
                break;
            }
            case WQ_KIND_END_PASS:
            case WQ_KIND_END_FINISH:
                assert(wq_session_key(&session, WQ_KEY_OK) == WQ_ACT_PASSED);
                ending++;
                break;
            default:
                assert(0);
        }

        assert(session.stage == WQ_STAGE_RESULT);
        assert(wq_session_result_stars(&session) == WQ_STARS_FOR_ZERO_WRONG);
    }
    printf("ok  全题库通关：puzzle %u / choice %u / 终局 %u\n",
           puzzle, choice, ending);
    assert(puzzle == 119 && choice == 32 && ending == 3);
}

static void test_wrong_move_resets_and_costs_a_star(void)
{
    wq_session_t session;
    wq_session_init(&session);
    enter_level(&session, 0);
    const wq_level_t *level = wq_session_level(&session);

    // 找一个「合法但不延续任何正解」的落点。
    uint8_t bad_point = WQ_BOARD_POINTS;
    for (uint8_t p = 0; p < WQ_BOARD_POINTS; p++) {
        if (session.board.cells[p] != WQ_COLOR_EMPTY) continue;
        if (!wq_board_legal(&session.board, p, level->player)) continue;
        bool on_path = false;
        for (uint8_t pi = 0; pi < level->correct_count; pi++) {
            if (level->correct[pi].len > 0 && level->correct[pi].moves[0] == p) {
                on_path = true;
                break;
            }
        }
        if (!on_path) {
            bad_point = p;
            break;
        }
    }
    if (bad_point == WQ_BOARD_POINTS) {
        puts("ok  （第 1 关所有合法点都是正解，跳过走错用例）");
        return;
    }

    session.cursor = bad_point;
    assert(wq_session_key(&session, WQ_KEY_OK) == WQ_ACT_WRONG);
    assert(session.wrong_count == 1);

    // 复位后按正解走完：星级降为「1 错 2 星」。
    const wq_path_t *path = &level->correct[0];
    for (uint8_t mi = 0; mi < path->len; mi += 2) {
        session.cursor = path->moves[mi];
        const wq_action_t action = wq_session_key(&session, WQ_KEY_OK);
        assert(action == WQ_ACT_PLACED || action == WQ_ACT_PASSED);
    }
    assert(session.stage == WQ_STAGE_RESULT);
    assert(wq_session_result_stars(&session) == WQ_STARS_FOR_ONE_WRONG);
    puts("ok  走错复位记错，星级降档");
}

static void test_wrong_choice_costs_a_star(void)
{
    wq_session_t session;
    wq_session_init(&session);
    // 第一个选择题关卡。
    uint16_t choice_level = WQ_LEVEL_COUNT;
    for (uint16_t li = 0; li < (uint16_t)WQ_LEVEL_COUNT; li++) {
        if (wq_levels[li].kind == WQ_KIND_CHOICE) {
            choice_level = li;
            break;
        }
    }
    assert(choice_level < WQ_LEVEL_COUNT);
    enter_level(&session, choice_level);

    // 故意选错：光标拨到正确项之外的那一个。
    const wq_level_t *level = wq_session_level(&session);
    const uint8_t wrong = (uint8_t)(level->answer == 0 ? 1 : 0);
    for (uint8_t k = 0; k < wrong; k++) {
        assert(wq_session_key(&session, WQ_KEY_DOWN) == WQ_ACT_MOVED);
    }
    assert(wq_session_key(&session, WQ_KEY_OK) == WQ_ACT_WRONG);
    assert(session.wrong_count == 1);
    assert(session.option == 0); // 光标被拨回第一项

    // 再答对：2 星。
    for (uint8_t k = 0; k < level->answer; k++) {
        assert(wq_session_key(&session, WQ_KEY_DOWN) == WQ_ACT_MOVED);
    }
    assert(wq_session_key(&session, WQ_KEY_OK) == WQ_ACT_PASSED);
    assert(wq_session_result_stars(&session) == WQ_STARS_FOR_ONE_WRONG);
    puts("ok  选择题答错记错、可再答");
}

static void test_navigation_flow(void)
{
    wq_session_t session;
    wq_session_init(&session);
    assert(session.stage == WQ_STAGE_WORLD);

    // WORLD -> LEVELS -> BRIEF -> SOLVE -> BACK 回题面 -> OK 回作答。
    assert(wq_session_key(&session, WQ_KEY_OK) == WQ_ACT_MOVED);
    assert(session.stage == WQ_STAGE_LEVELS);
    assert(wq_session_key(&session, WQ_KEY_OK) == WQ_ACT_ENTERED);
    assert(session.stage == WQ_STAGE_BRIEF);
    assert(wq_session_key(&session, WQ_KEY_OK) == WQ_ACT_BOARD_READY);
    assert(session.stage == WQ_STAGE_SOLVE);
    assert(wq_session_key(&session, WQ_KEY_BACK) == WQ_ACT_LEFT);
    assert(session.stage == WQ_STAGE_BRIEF);
    assert(wq_session_key(&session, WQ_KEY_BACK) == WQ_ACT_LEFT);
    assert(session.stage == WQ_STAGE_LEVELS);

    // 未通关的第 1 关之后没有解锁判定在 session 里 —— 那是应用层与存档的事；
    // 这里只确认边界键不越界。
    assert(wq_session_key(&session, WQ_KEY_UP) == WQ_ACT_NONE);
    assert(wq_session_key(&session, WQ_KEY_OK) == WQ_ACT_ENTERED);
    puts("ok  导航链路 WORLD->LEVELS->BRIEF->SOLVE->BACK 全通");
}

static void test_illegal_move_is_free(void)
{
    wq_session_t session;
    wq_session_init(&session);
    enter_level(&session, 0);
    const wq_level_t *level = wq_session_level(&session);

    // 找一个占位点（初始棋子）——落子被拒且不记错。
    uint8_t occupied = WQ_BOARD_POINTS;
    for (uint8_t p = 0; p < WQ_BOARD_POINTS; p++) {
        if (session.board.cells[p] != WQ_COLOR_EMPTY) {
            occupied = p;
            break;
        }
    }
    if (occupied == WQ_BOARD_POINTS) {
        puts("ok  （第 1 关没有初始棋子，跳过占位用例）");
        return;
    }
    (void)level;
    session.cursor = occupied;
    assert(wq_session_key(&session, WQ_KEY_OK) == WQ_ACT_NONE);
    assert(session.wrong_count == 0);
    puts("ok  占位/非法落子不记错");
}

int main(void)
{
    test_navigation_flow();
    test_wrong_move_resets_and_costs_a_star();
    test_wrong_choice_costs_a_star();
    test_illegal_move_is_free();
    test_full_playthrough();
    puts("test_wq_session: PASS");
    return 0;
}
