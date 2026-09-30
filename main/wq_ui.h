// main/wq_ui.h —— 界面层：主题、字体与可复用控件。
//
// 配色取自网页版《围棋闯关》的 CSS 变量：深蓝夜空底（#1a1d2e）+ 金（#f5c451）
// + 绿（#6bce8a）+ 红（#e74c3c），棋盘用传统木色（#dcb35c）压在深底上。
// 与前几个应用的「浅色纸面」不同族 —— 这一版是深色主题，全靠网页版原值。
//
// 版式沿用同一块屏的物理事实：240x320，四角有 30px 圆角遮罩。逻辑屏底取深蓝
// （与遮罩的纯黑过渡自然），页面是一张四周内缩 5px、圆角 25px 的深色卡片 ——
// 半径 25 < 遮罩半径 30，卡片本身完整落在可见区里。
//
// 棋盘渲染是本应用新增的：9x9 交叉点 = 木色底板 + 18 条线 + 5 个星位 + 每点一个
// 棋子对象（圆），标记用 16px 字形叠在交叉点上，光标是一个金色方框。
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "lvgl.h"

// 版式预算与生成的内容上限是同一套数字的两端，所以这里显式依赖生成物：
// wq_ui.c 用 _Static_assert 把「预算 x 字号 <= 内容区宽」与「内容上限 <= 每行
// 预算」钉在编译期，改了任何一边另一边没跟上就编译不过。
#include "wq_content.h"
#include "wq_layout.h"
#include "wq_session.h"

// ------------------------------------------------------------- 字体 -------
// 三档字库由 tools/weiqi/gen_font.py 生成到 assets/fonts/，符号在这里声明。
LV_FONT_DECLARE(wq_font_16);
LV_FONT_DECLARE(wq_font_24);
LV_FONT_DECLARE(wq_font_32);

// ------------------------------------------------------------- 控件 -------
lv_obj_t *wq_label_create(lv_obj_t *parent, const char *text,
                          const lv_font_t *font, uint32_t color);
// 把 text 按每行 chars_per_line 个字折行后写进 label（中文没有空格，必须自己折）。
void wq_text_set(lv_obj_t *label, const char *text, int chars_per_line);

lv_obj_t *wq_page_create(lv_obj_t **out_card);
lv_obj_t *wq_body_create(lv_obj_t *card);
// 题面页的滚动容器：本应用里唯一允许滚动的对象。
lv_obj_t *wq_scroll_create(lv_obj_t *body);

lv_obj_t *wq_headline_create(lv_obj_t *parent, int x, int y, int w, int h,
                             uint32_t color);
lv_obj_t *wq_paragraph_create(lv_obj_t *parent, int x, int y, int w, int h,
                              const lv_font_t *font, uint32_t color);
lv_obj_t *wq_note_create(lv_obj_t *parent, int x, int y, int w,
                         const char *text, uint32_t color);

typedef struct {
    lv_obj_t *bar;
    lv_obj_t *left;
    lv_obj_t *right;
} wq_topbar_t;

wq_topbar_t wq_topbar_create(lv_obj_t *card, const char *left, const lv_font_t *left_font);
void wq_topbar_set_left(wq_topbar_t *bar, const char *text);
void wq_topbar_set_right(wq_topbar_t *bar, const char *text);
void wq_topbar_add_battery(wq_topbar_t *bar);

lv_obj_t *wq_hint_create(lv_obj_t *card, const char *text);

typedef enum {
    WQ_STATE_NORMAL = 0,
    WQ_STATE_SELECTED,
    WQ_STATE_DISABLED,   // 锁定的关卡：灰显
    WQ_STATE_GOOD,       // 通关（绿）
    WQ_STATE_BAD,        // 走错/错误（红）
} wq_state_t;

typedef struct {
    lv_obj_t *box;
    lv_obj_t *tag;
    lv_obj_t *text;
    lv_obj_t *note;
} wq_row_t;

#define WQ_ROW_BORDER 3
#define WQ_ROW_PAD    8
#define WQ_ROW_H      36
#define WQ_ROW_GAP    6

wq_row_t wq_row_create(lv_obj_t *parent, int x, int y, int w, int h,
                       int tag_width, int note_width);
// 16px 小行：正文与标记都用小字号。关卡列表的标题最长 13 字、选择题选项最长
// 10 字，24px 一行都放不下，16px 才装得下 —— 行高仍是 36px，触达面积不变。
wq_row_t wq_row_small_create(lv_obj_t *parent, int x, int y, int w, int h,
                             int tag_width, int note_width);
void wq_row_update(wq_row_t *row, const char *tag, const char *text,
                   const char *note, wq_state_t state);
void wq_row_set_state(wq_row_t *row, wq_state_t state);

// ----------------------------------------------------------- 棋盘视图 -----
// 9x9 棋盘渲染。cell 决定整体大小：视图边长 = 8*cell + 2*(cell/2)。
#define WQ_BOARD_CELL        23   // 作答页：视图 206px
#define WQ_BOARD_CELL_SMALL  13   // 选择题题面页：视图 116px
#define WQ_BOARD_VIEW_PX(cell) (8 * (cell) + 2 * ((cell) / 2))

typedef struct {
    lv_obj_t *box;
    lv_obj_t *stones[WQ_BOARD_POINTS];
    lv_obj_t *marks[WQ_MARKS_MAX];
    lv_obj_t *cursor;
    int cell;
    int margin;
    int stone;
} wq_board_view_t;

// 在 parent 的 (x,y) 处建一块 cell 规格的棋盘。stones/marks/cursor 隐藏待同步。
void wq_board_view_create(wq_board_view_t *view, lv_obj_t *parent, int x, int y, int cell);

// 按 session 同步棋盘：棋子、标记、光标。标记颜色随底下棋子颜色自适应。
void wq_board_view_sync(wq_board_view_t *view, const wq_session_t *session);

// 无 session 的静态棋面（备用）；目前页面都走 sync。
void wq_board_view_hide_cursor(wq_board_view_t *view);
