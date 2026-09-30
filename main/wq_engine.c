// main/wq_engine.c —— 见 wq_engine.h。
#include "wq_engine.h"

#include <string.h>

static const int8_t DIR_X[4] = { -1, 1, 0, 0 };
static const int8_t DIR_Y[4] = { 0, 0, -1, 1 };

void wq_board_init(wq_board_t *board, const wq_level_t *level)
{
    memset(board, 0, sizeof(*board));
    board->ko = -1;
    for (uint8_t i = 0; i < level->stone_count; i++) {
        const uint8_t point = level->stones[i * 2];
        const uint8_t color = level->stones[i * 2 + 1];
        if (point < WQ_BOARD_POINTS &&
            (color == WQ_COLOR_BLACK || color == WQ_COLOR_WHITE)) {
            board->cells[point] = color;
        }
    }
}

void wq_point_name(uint8_t point, char *out)
{
    static const char letters[] = "abcdefghi";
    out[0] = letters[point % WQ_BOARD];
    out[1] = letters[point / WQ_BOARD];
    out[2] = '\0';
}

// 从 start 出发洪填同色棋块：group 收棋子下标（返回个数），
// liberties 位图记这块棋的所有气（调用方先 memset 清零）。
static uint8_t find_group(const uint8_t *cells, uint8_t start,
                          uint8_t *group, uint8_t *liberties)
{
    uint8_t seen[WQ_BOARD_POINTS];
    uint8_t stack[WQ_BOARD_POINTS];
    uint8_t top = 0;
    uint8_t count = 0;

    memset(seen, 0, sizeof(seen));
    seen[start] = 1;
    stack[top++] = start;

    while (top > 0) {
        const uint8_t point = stack[--top];
        group[count++] = point;
        const uint8_t x = point % WQ_BOARD;
        const uint8_t y = point / WQ_BOARD;
        const uint8_t color = cells[start];
        for (uint8_t d = 0; d < 4; d++) {
            const int nx = x + DIR_X[d];
            const int ny = y + DIR_Y[d];
            if (nx < 0 || nx >= WQ_BOARD || ny < 0 || ny >= WQ_BOARD) continue;
            const uint8_t neighbor = (uint8_t)(ny * WQ_BOARD + nx);
            if (cells[neighbor] == WQ_COLOR_EMPTY) {
                liberties[neighbor] = 1;
            } else if (cells[neighbor] == color && !seen[neighbor]) {
                seen[neighbor] = 1;
                stack[top++] = neighbor;
            }
        }
    }
    return count;
}

// 位图里是否有任何一气。
static bool has_liberty(const uint8_t *liberties)
{
    for (uint8_t i = 0; i < WQ_BOARD_POINTS; i++) {
        if (liberties[i]) return true;
    }
    return false;
}

bool wq_board_legal(const wq_board_t *board, uint8_t point, uint8_t color)
{
    if (point >= WQ_BOARD_POINTS) return false;
    if (color != WQ_COLOR_BLACK && color != WQ_COLOR_WHITE) return false;
    if (board->cells[point] != WQ_COLOR_EMPTY) return false;
    if (board->ko >= 0 && point == (uint8_t)board->ko) return false;

    uint8_t cells[WQ_BOARD_POINTS];
    memcpy(cells, board->cells, sizeof(cells));
    cells[point] = color;

    // 先看四邻有没有无气的对方块 —— 提子发生在自杀判定之前，
    // 所以「至少提一子」的落子永远合法。
    const uint8_t x = point % WQ_BOARD;
    const uint8_t y = point / WQ_BOARD;
    for (uint8_t d = 0; d < 4; d++) {
        const int nx = x + DIR_X[d];
        const int ny = y + DIR_Y[d];
        if (nx < 0 || nx >= WQ_BOARD || ny < 0 || ny >= WQ_BOARD) continue;
        const uint8_t neighbor = (uint8_t)(ny * WQ_BOARD + nx);
        if (cells[neighbor] != (uint8_t)(3 - color)) continue;
        uint8_t group[WQ_BOARD_POINTS];
        uint8_t liberties[WQ_BOARD_POINTS];
        memset(liberties, 0, sizeof(liberties));
        find_group(cells, neighbor, group, liberties);
        if (has_liberty(liberties)) continue;
        return true; // 提掉对方，合法
    }

    // 不提子：己方这块必须有气。
    uint8_t group[WQ_BOARD_POINTS];
    uint8_t liberties[WQ_BOARD_POINTS];
    memset(liberties, 0, sizeof(liberties));
    find_group(cells, point, group, liberties);
    return has_liberty(liberties);
}

int wq_board_place(wq_board_t *board, uint8_t point, uint8_t color)
{
    if (!wq_board_legal(board, point, color)) return -1;

    uint8_t cells[WQ_BOARD_POINTS];
    memcpy(cells, board->cells, sizeof(cells));
    cells[point] = color;

    const uint8_t x = point % WQ_BOARD;
    const uint8_t y = point / WQ_BOARD;
    uint8_t captured = 0;
    uint8_t captured_point = 0;

    for (uint8_t d = 0; d < 4; d++) {
        const int nx = x + DIR_X[d];
        const int ny = y + DIR_Y[d];
        if (nx < 0 || nx >= WQ_BOARD || ny < 0 || ny >= WQ_BOARD) continue;
        const uint8_t neighbor = (uint8_t)(ny * WQ_BOARD + nx);
        if (cells[neighbor] != (uint8_t)(3 - color)) continue;

        uint8_t group[WQ_BOARD_POINTS];
        uint8_t liberties[WQ_BOARD_POINTS];
        memset(liberties, 0, sizeof(liberties));
        const uint8_t size = find_group(cells, neighbor, group, liberties);
        if (has_liberty(liberties)) continue;

        for (uint8_t i = 0; i < size; i++) {
            cells[group[i]] = WQ_COLOR_EMPTY;
        }
        if (captured == 0) captured_point = group[0];
        captured = (uint8_t)(captured + size);
    }

    // legal 已保证活着，这里再确认一次提子后的己方气数（简单劫判定要用）。
    uint8_t group[WQ_BOARD_POINTS];
    uint8_t liberties[WQ_BOARD_POINTS];
    memset(liberties, 0, sizeof(liberties));
    const uint8_t group_size = find_group(cells, point, group, liberties);
    if (!has_liberty(liberties)) return -1; // 防御：不应到达

    memcpy(board->cells, cells, sizeof(board->cells));
    board->ko = -1;
    // 简单劫：恰好提一子、落子自成单子棋块、且该块只剩一口气
    // （那口气必然就是被提的点）—— 立即回提会还原局面，禁止。
    if (captured == 1 && group_size == 1) {
        uint8_t liberty_count = 0;
        for (uint8_t i = 0; i < WQ_BOARD_POINTS; i++) {
            if (liberties[i]) liberty_count++;
        }
        if (liberty_count == 1) board->ko = (int8_t)captured_point;
    }
    return captured;
}
