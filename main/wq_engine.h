// main/wq_engine.h —— 围棋规则内核：气 / 提子 / 禁自杀 / 简单劫。
//
// 只服务 9x9 裁剪棋盘（见 wq_content.h），不依赖 ESP-IDF 与 LVGL，宿主测试直接
// 编译它。规则与 tools/weiqi/content.py 的校验器是同一套语义的两份实现，两边由
// tests/test_wq_engine.c 用真实题库对拍：任何一边改了规则另一边没跟上，测试就炸。
//
// 设备上的判题不搜索、不评估：正解路径是内容里脚本化的一条条序列（与网页版
// move_tree 一致），引擎只负责「这一手合不合法、提了几颗」，对错由
// wq_session 按路径前缀匹配判定。
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wq_content.h"

#define WQ_COLOR_EMPTY 0
#define WQ_COLOR_BLACK 1
#define WQ_COLOR_WHITE 2

typedef struct {
    uint8_t cells[WQ_BOARD_POINTS]; // WQ_COLOR_*
    int8_t ko;                      // 简单劫禁着点，-1 = 无
} wq_board_t;

// 按 wq_level_t 摆出初始局面。ko 清零。
void wq_board_init(wq_board_t *board, const wq_level_t *level);

// 点下标 -> 列行坐标串（"ae" 形式）。out 至少 3 字节。
void wq_point_name(uint8_t point, char *out);

// 试下一手：返回提子数；非法（占位 / 劫争回提 / 自杀）返回 -1。
// 合法时 board 被更新（含 ko 标记）；非法时 board 保持不变。
int wq_board_place(wq_board_t *board, uint8_t point, uint8_t color);

// 只问合不合法，不动棋盘。
bool wq_board_legal(const wq_board_t *board, uint8_t point, uint8_t color);
