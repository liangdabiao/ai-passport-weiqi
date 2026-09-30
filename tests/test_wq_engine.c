// tests/test_wq_engine.c —— 围棋规则内核。
//
// 两层断言：
//   1. 规则单元用例：气 / 提子 / 禁自杀 / 简单劫 / 占位。这些用例与
//      tools/weiqi/extract_levels.mjs 里校验器的语义一一对应，任何一边改了
//      规则另一边没跟上，就会在这里或生成器里炸。
//   2. 全题库重放：把 154 关的正解路径逐手喂给引擎，每手必须合法 ——
//      内容生成器校验过一遍（node），宿主测试用 C 引擎再校验一遍，
//      设备上跑的是第三遍（同一份 C 代码）。
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "wq_engine.h"

// 点下标 = y * WQ_BOARD + x；测试里用 (列,行) 书写，避免再手算。
static uint8_t at(int x, int y)
{
    return (uint8_t)(y * WQ_BOARD + x);
}

// 在空棋盘上落一串同色子。
static void seed(wq_board_t *board, const char *coords, uint8_t color)
{
    for (const char *p = coords; p[0] && p[1]; p += 2) {
        const uint8_t x = (uint8_t)(p[0] - 'a');
        const uint8_t y = (uint8_t)(p[1] - 'a');
        assert(x < WQ_BOARD && y < WQ_BOARD);
        board->cells[y * WQ_BOARD + x] = color;
    }
}

static void test_capture_single_stone(void)
{
    wq_board_t board;
    memset(&board, 0, sizeof(board));
    board.ko = -1;
    // 白子 aa；黑子 ab、ac —— aa 只剩右边的 ba 一口气。
    board.cells[0] = WQ_COLOR_WHITE;
    seed(&board, "abac", WQ_COLOR_BLACK);

    // 黑在 ba 落子，提掉 aa。
    const int captured = wq_board_place(&board, 1, WQ_COLOR_BLACK);
    assert(captured == 1);
    assert(board.cells[0] == WQ_COLOR_EMPTY);
    puts("ok  单子无气被提");
}

static void test_capture_group(void)
{
    wq_board_t board;
    memset(&board, 0, sizeof(board));
    board.ko = -1;
    // 白棋两子 aa、ab；黑已在 ba、bb，最后在 ac 收气 —— 整块同提。
    board.cells[0] = WQ_COLOR_WHITE;
    board.cells[WQ_BOARD] = WQ_COLOR_WHITE;
    seed(&board, "babb", WQ_COLOR_BLACK);

    // ac = x0,y2 = 点 18。
    const int captured = wq_board_place(&board, 18, WQ_COLOR_BLACK);
    assert(captured == 2);
    assert(board.cells[0] == WQ_COLOR_EMPTY);
    assert(board.cells[WQ_BOARD] == WQ_COLOR_EMPTY);
    puts("ok  棋块同提");
}

static void test_suicide_is_rejected(void)
{
    wq_board_t board;
    memset(&board, 0, sizeof(board));
    board.ko = -1;
    // 黑子 ba(点1) 与 ab(点9)：白若在 aa(点0) 落子，自己零气、又提不了任何
    // 黑子（两块黑都有外气）=> 自杀，非法。
    seed(&board, "baab", WQ_COLOR_BLACK);

    assert(!wq_board_legal(&board, 0, WQ_COLOR_WHITE));
    assert(wq_board_place(&board, 0, WQ_COLOR_WHITE) == -1);
    assert(board.cells[0] == WQ_COLOR_EMPTY); // 棋盘不变
    puts("ok  自杀被拒（棋盘不变）");
}

static void test_snapback_capture_beats_suicide(void)
{
    wq_board_t board;
    memset(&board, 0, sizeof(board));
    board.ko = -1;
    // 白两子 aa(0)、ab(9)，唯一气 = ac(18)；黑已围 ba(1) bb(10) bc(11) cc(19)。
    // 黑在 ac 落子：落完自身零气，但先提掉白两子 —— 提来的两个空点就是气，
    // 所以合法（提子判定先于自杀判定）。
    board.cells[0] = WQ_COLOR_WHITE;
    board.cells[9] = WQ_COLOR_WHITE;
    seed(&board, "babb", WQ_COLOR_BLACK);
    seed(&board, "bccc", WQ_COLOR_BLACK);

    assert(wq_board_legal(&board, 18, WQ_COLOR_BLACK));
    assert(wq_board_place(&board, 18, WQ_COLOR_BLACK) == 2);
    assert(board.cells[0] == WQ_COLOR_EMPTY);
    assert(board.cells[9] == WQ_COLOR_EMPTY);
    assert(board.cells[18] == WQ_COLOR_BLACK);
    puts("ok  提子优先于自杀判定（先提后活合法）");
}

static void test_occupied_is_rejected(void)
{
    wq_board_t board;
    memset(&board, 0, sizeof(board));
    board.ko = -1;
    board.cells[0] = WQ_COLOR_BLACK;
    assert(!wq_board_legal(&board, 0, WQ_COLOR_WHITE));
    puts("ok  占位被拒");
}

static void test_simple_ko(void)
{
    // 教科书劫形。白子 (2,1) 的其余三邻全是黑，唯一气 = (1,1)；
    // (1,1) 的其余三邻全是白 —— 黑落 (1,1) 提白单子后，黑 (1,1) 自成单子、
    // 只剩被提的那个点一口气 => 成劫。
    wq_board_t board;
    memset(&board, 0, sizeof(board));
    board.ko = -1;

    board.cells[at(2, 0)] = WQ_COLOR_BLACK;
    board.cells[at(2, 2)] = WQ_COLOR_BLACK;
    board.cells[at(3, 1)] = WQ_COLOR_BLACK;
    board.cells[at(0, 1)] = WQ_COLOR_WHITE;
    board.cells[at(1, 0)] = WQ_COLOR_WHITE;
    board.cells[at(1, 2)] = WQ_COLOR_WHITE;
    board.cells[at(2, 1)] = WQ_COLOR_WHITE;

    const int captured = wq_board_place(&board, at(1, 1), WQ_COLOR_BLACK);
    assert(captured == 1);
    assert(board.cells[at(2, 1)] == WQ_COLOR_EMPTY);
    // 劫点 = 被提的点：白立即回提被禁。
    assert(board.ko == at(2, 1));
    assert(!wq_board_legal(&board, at(2, 1), WQ_COLOR_WHITE));
    puts("ok  简单劫：单提单成劫，回提被禁");
}

static void test_ko_cleared_after_other_move(void)
{
    wq_board_t board;
    memset(&board, 0, sizeof(board));
    board.ko = -1;
    // 复用上一用例的劫形，白在远处落一手后劫点应当解除。
    board.cells[at(2, 0)] = WQ_COLOR_BLACK;
    board.cells[at(2, 2)] = WQ_COLOR_BLACK;
    board.cells[at(3, 1)] = WQ_COLOR_BLACK;
    board.cells[at(0, 1)] = WQ_COLOR_WHITE;
    board.cells[at(1, 0)] = WQ_COLOR_WHITE;
    board.cells[at(1, 2)] = WQ_COLOR_WHITE;
    board.cells[at(2, 1)] = WQ_COLOR_WHITE;
    assert(wq_board_place(&board, at(1, 1), WQ_COLOR_BLACK) == 1);
    assert(board.ko == at(2, 1));
    if (wq_board_legal(&board, at(8, 8), WQ_COLOR_WHITE)) {
        wq_board_place(&board, at(8, 8), WQ_COLOR_WHITE);
        assert(board.ko == -1);
        assert(wq_board_legal(&board, at(2, 1), WQ_COLOR_WHITE));
    }
    puts("ok  劫点随下一手解除");
}

static void test_replay_every_correct_path(void)
{
    // 全题库重放：每条正解路径在 C 引擎下逐手合法。
    unsigned replayed = 0, moves_total = 0;
    for (uint16_t li = 0; li < (uint16_t)WQ_LEVEL_COUNT; li++) {
        const wq_level_t *level = &wq_levels[li];
        if (level->kind != WQ_KIND_PUZZLE) continue;
        for (uint8_t pi = 0; pi < level->correct_count; pi++) {
            const wq_path_t *path = &level->correct[pi];
            wq_board_t board;
            wq_board_init(&board, level);
            for (uint8_t mi = 0; mi < path->len; mi++) {
                const uint8_t color =
                    (uint8_t)((mi % 2 == 0) ? level->player : 3 - level->player);
                const int captured = wq_board_place(&board, path->moves[mi], color);
                if (captured < 0) {
                    char name[3];
                    wq_point_name(path->moves[mi], name);
                    printf("FAIL: 关 %u 路径 %u 第 %u 手 %s 非法\n",
                           (unsigned)li + 1, (unsigned)pi + 1, (unsigned)mi + 1, name);
                    assert(0);
                }
                moves_total++;
            }
            replayed++;
        }
    }
    printf("ok  全题库正解路径重放：%u 条 / %u 手逐手合法\n",
           (unsigned)replayed, (unsigned)moves_total);
    assert(replayed > 100); // 内容在，测试才有效
}

int main(void)
{
    test_capture_single_stone();
    test_capture_group();
    test_suicide_is_rejected();
    test_snapback_capture_beats_suicide();
    test_occupied_is_rejected();
    test_simple_ko();
    test_ko_cleared_after_other_move();
    test_replay_every_correct_path();
    puts("test_wq_engine: PASS");
    return 0;
}
