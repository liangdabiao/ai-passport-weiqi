// main/wq_ui.c —— 见 wq_ui.h。移植自本仓库前一个应用（侨批填字问答）的 qpq_ui.c，
// 版式几何与控件行为未改；配色换成网页版围棋闯关的深蓝夜空 + 金，并新增棋盘视图。
#include "wq_ui.h"

#include <stdio.h>
#include <string.h>

#include "bsp_battery.h"
#include "wq_wrap.h"

// 「每行几个字」是算术，不是手感。三个预算各自乘以自己的字号，都必须放得进
// 内容区的 210px —— 放不进就说明内容区的宽度或者字号被改过，而另一处没跟上。
_Static_assert(WQ_CHARS_HEADLINE * 32 <= WQ_BODY_W, "32px 每行字数不再放得下");
_Static_assert(WQ_CHARS_BODY * 24 <= WQ_BODY_W, "24px 每行字数不再放得下");
_Static_assert(WQ_CHARS_SMALL * 16 <= WQ_BODY_W, "16px 每行字数不再放得下");

// 生成的关卡上限与这里的折行预算必须彼此相容。选择题选项要在一行内放得下
// （含左侧甲乙丙丁标记）；标题要与章节进度同处顶栏一行。
_Static_assert(WQ_OPTION_TEXT_MAX_CHARS <= WQ_CHARS_SMALL,
               "选项在 16px 小行里要一行放得下（含左侧甲乙丙丁标记）");
_Static_assert(WQ_TITLE_MAX_CHARS <= WQ_CHARS_SMALL + 4,
               "标题在 16px 顶栏里至多省略号收尾，不许折行");

// 所有控件都关掉滚动、清掉默认内边距，位置一律用绝对坐标 —— 尺寸在编译期
// 就算死，不依赖主题默认值，也就不会「换个主题就错位」。
static lv_obj_t *plain_obj(lv_obj_t *parent, int x, int y, int w, int h)
{
    lv_obj_t *obj = lv_obj_create(parent);
    lv_obj_remove_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_pos(obj, x, y);
    lv_obj_set_size(obj, w, h);
    lv_obj_set_style_radius(obj, 0, 0);
    lv_obj_set_style_border_width(obj, 0, 0);
    lv_obj_set_style_pad_all(obj, 0, 0);
    return obj;
}

static lv_obj_t *filled(lv_obj_t *parent, int x, int y, int w, int h, uint32_t color)
{
    lv_obj_t *obj = plain_obj(parent, x, y, w, h);
    lv_obj_set_style_bg_color(obj, lv_color_hex(color), 0);
    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
    return obj;
}

lv_obj_t *wq_label_create(lv_obj_t *parent, const char *text,
                          const lv_font_t *font, uint32_t color)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, text ? text : "");
    lv_obj_set_style_text_font(label, font, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(color), 0);
    lv_obj_set_style_pad_all(label, 0, 0);
    lv_obj_set_style_border_width(label, 0, 0);
    return label;
}

// 折行缓冲。模块内一份就够：每次都是「折好 -> 拷进标签」一气做完，
// 调用方拿到标签之后就不再引用这块内存。
//
// 容量按最费的那个调用方开：题面说明最长 240 字，16px 每行 13 字，
// 240 字 x 3 字节 = 720 字节，断点前移最多让行数比 240/13 多出几行，
// 按 24 个换行算 = 24 字节，结尾 NUL 1 字节 —— 768 有余量。
// 按平均题面（约 40 字）去估，第一次渲染长说明就会溢出。
#if WQ_WRAP_CAPACITY < 768
#error "wq_wrap.h 的折行缓冲装不下最长的题面说明（240 字 x 3 字节 + 换行）"
#endif

static char s_wrapped[WQ_WRAP_CAPACITY];

void wq_text_set(lv_obj_t *label, const char *text, int chars_per_line)
{
    if (!label) return;

    const size_t length =
        wq_wrap_utf8(text, chars_per_line, s_wrapped, sizeof(s_wrapped));
    if (length == 0) {
        // 折行返回 0 只有两种原因：容量不够（缓冲区开小了，属编程错误），
        // 或者入参为空/非法（正常路径上就是空串）。两种都写空串 ——
        // 把上一屏的残字留在标签上，是最难查的一类 bug。
        lv_label_set_text(label, "");
        return;
    }
    lv_label_set_text(label, s_wrapped);
}

lv_obj_t *wq_page_create(lv_obj_t **out_card)
{
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_obj_remove_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(scr, 0, 0);
    lv_obj_set_style_border_width(scr, 0, 0);
    lv_obj_set_style_pad_all(scr, 0, 0);
    lv_obj_set_style_bg_color(scr, lv_color_hex(WQ_C_SCREEN), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    lv_obj_t *card = lv_obj_create(scr);
    lv_obj_remove_flag(card, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_pos(card, WQ_PAGE_INSET, WQ_PAGE_INSET);
    lv_obj_set_size(card, WQ_PAGE_W, WQ_PAGE_H);
    lv_obj_set_style_radius(card, WQ_PAGE_RADIUS, 0);
    lv_obj_set_style_border_width(card, 0, 0);
    lv_obj_set_style_pad_all(card, 0, 0);
    lv_obj_set_style_bg_color(card, lv_color_hex(WQ_C_PANEL), 0);
    lv_obj_set_style_bg_opa(card, LV_OPA_COVER, 0);
    // 顶/底栏是直角矩形，靠裁角让步进卡片的圆角里，不靠「颜色碰巧一样」兜住。
    lv_obj_set_style_clip_corner(card, true, 0);

    if (out_card) *out_card = card;
    return scr;
}

lv_obj_t *wq_body_create(lv_obj_t *card)
{
    lv_obj_t *body = plain_obj(card, 0, WQ_BODY_TOP, WQ_PAGE_W, WQ_BODY_H);
    lv_obj_set_style_bg_opa(body, LV_OPA_TRANSP, 0);
    return body;
}

lv_obj_t *wq_scroll_create(lv_obj_t *body)
{
    // 容器自己可滚动（这是本应用里唯一允许滚动的对象）。题面说明最长 240 字，
    // 16px 每行 13 字要滚约两屏 —— 与其砍内容，不如让它滚。
    lv_obj_t *container = plain_obj(body, 0, 0, WQ_PAGE_W, WQ_BODY_H);
    lv_obj_set_style_bg_opa(container, LV_OPA_TRANSP, 0);
    lv_obj_add_flag(container, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scroll_dir(container, LV_DIR_VER);
    lv_obj_set_scrollbar_mode(container, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_top(container, 2, 0);
    lv_obj_set_style_pad_bottom(container, 2, 0);
    return container;
}

// 电池外壳 20x11。外框自己用四条实心边画，不用 border —— 这样 shell 的坐标
// 原点就是它的左上角。
#define WQ_BAT_W 20
#define WQ_BAT_H 11
#define WQ_BAT_EDGE 2

static void battery_create(lv_obj_t *bar)
{
    const int soc = bsp_battery_soc();
    const int pct = soc > 100 ? 100 : soc;

    char text[16];
    if (soc >= 0) {
        snprintf(text, sizeof(text), "%d%%", pct);
    } else {
        snprintf(text, sizeof(text), "--");
    }

    lv_obj_t *label = wq_label_create(bar, text, &wq_font_16, WQ_C_HINTINK);
    lv_obj_align(label, LV_ALIGN_RIGHT_MID, -40, 0);

    lv_obj_t *shell = plain_obj(bar, 0, 0, WQ_BAT_W, WQ_BAT_H);
    lv_obj_set_style_bg_opa(shell, LV_OPA_TRANSP, 0);
    lv_obj_align(shell, LV_ALIGN_RIGHT_MID, -13, 0);

    filled(shell, 0, 0, WQ_BAT_W, WQ_BAT_EDGE, WQ_C_HINTINK);
    filled(shell, 0, WQ_BAT_H - WQ_BAT_EDGE, WQ_BAT_W, WQ_BAT_EDGE, WQ_C_HINTINK);
    filled(shell, 0, 0, WQ_BAT_EDGE, WQ_BAT_H, WQ_C_HINTINK);
    filled(shell, WQ_BAT_W - WQ_BAT_EDGE, 0, WQ_BAT_EDGE, WQ_BAT_H, WQ_C_HINTINK);

    // 正极触点与外壳同层，否则会被外壳裁掉。
    lv_obj_t *cap = filled(bar, 0, 0, 3, 5, WQ_C_HINTINK);
    lv_obj_set_style_radius(cap, 1, 0);
    lv_obj_align(cap, LV_ALIGN_RIGHT_MID, -10, 0);

    if (soc > 0) {
        const int usable = WQ_BAT_W - 2 * (WQ_BAT_EDGE + 1);
        int width = (usable * pct) / 100;
        if (width < 1) width = 1;
        // 电量本身没有褒贬，用一档中性灰蓝，不引入第三种彩色。
        lv_obj_t *fill = filled(shell, WQ_BAT_EDGE + 1, WQ_BAT_EDGE + 1, width,
                                WQ_BAT_H - 2 * (WQ_BAT_EDGE + 1), WQ_C_MUTED);
        lv_obj_set_style_radius(fill, 2, 0);
    }
}

// 顶栏左右两侧各留多少宽度：左侧 14 起，右侧 56 封顶（进度 "12/154" 与电量都要
// 放得进这个区间）。
#define WQ_BAR_PAD        14
#define WQ_BAR_RIGHT_W    56
#define WQ_BAR_LEFT_W     (WQ_PAGE_W - WQ_BAR_PAD - WQ_BAR_RIGHT_W - 6)

wq_topbar_t wq_topbar_create(lv_obj_t *card, const char *left, const lv_font_t *left_font)
{
    wq_topbar_t bar = {0};
    bar.bar = filled(card, 0, 0, WQ_PAGE_W, WQ_BAR_H, WQ_C_PANEL_ALT);

    if (left && left[0]) {
        bar.left = wq_label_create(bar.bar, left, left_font ? left_font : &wq_font_24,
                                   WQ_C_INK);
        lv_obj_set_width(bar.left, WQ_BAR_LEFT_W);
        lv_obj_set_height(bar.left, LV_SIZE_CONTENT);
        lv_label_set_long_mode(bar.left, LV_LABEL_LONG_MODE_DOTS);
        lv_obj_align(bar.left, LV_ALIGN_LEFT_MID, WQ_BAR_PAD, 0);
    }
    return bar;
}

void wq_topbar_set_left(wq_topbar_t *bar, const char *text)
{
    if (!bar || !bar->left) return;
    lv_label_set_text(bar->left, text ? text : "");
}

void wq_topbar_set_right(wq_topbar_t *bar, const char *text)
{
    if (!bar || !bar->bar) return;
    if (bar->right) {
        lv_obj_delete(bar->right);
        bar->right = NULL;
    }
    bar->right = wq_label_create(bar->bar, text ? text : "", &wq_font_16, WQ_C_HINTINK);
    lv_obj_set_width(bar->right, WQ_BAR_RIGHT_W);
    lv_obj_set_height(bar->right, LV_SIZE_CONTENT);
    lv_label_set_long_mode(bar->right, LV_LABEL_LONG_MODE_DOTS);
    lv_obj_set_style_text_align(bar->right, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_align(bar->right, LV_ALIGN_RIGHT_MID, -WQ_BAR_PAD, 0);
}

void wq_topbar_add_battery(wq_topbar_t *bar)
{
    if (!bar || !bar->bar) return;
    battery_create(bar->bar);
}

lv_obj_t *wq_hint_create(lv_obj_t *card, const char *text)
{
    lv_obj_t *bar = filled(card, 0, WQ_PAGE_H - WQ_HINT_H, WQ_PAGE_W, WQ_HINT_H,
                           WQ_C_PANEL_ALT);
    lv_obj_t *label = wq_label_create(bar, text, &wq_font_16, WQ_C_HINTINK);
    // 底栏只有 26px 高，一行 16px 字占 20px。宽度封死并禁用换行 ——
    // 文案变长时宁可在右边打省略号，也不能折成两行顶出底栏。
    lv_obj_set_width(label, WQ_PAGE_W - 12);
    lv_obj_set_height(label, LV_SIZE_CONTENT);
    lv_label_set_long_mode(label, LV_LABEL_LONG_MODE_DOTS);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_center(label);
    return label;
}

lv_obj_t *wq_headline_create(lv_obj_t *parent, int x, int y, int w, int h,
                             uint32_t color)
{
    // 折行模式必须在设完宽度之后再设，否则 LVGL 会先按内容算一次尺寸。
    lv_obj_t *label = wq_label_create(parent, "", &wq_font_32, color);
    lv_obj_set_pos(label, x, y);
    lv_obj_set_width(label, w);
    lv_obj_set_height(label, h);
    lv_label_set_long_mode(label, LV_LABEL_LONG_MODE_WRAP);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_line_space(label, 4, 0);
    return label;
}

lv_obj_t *wq_paragraph_create(lv_obj_t *parent, int x, int y, int w, int h,
                              const lv_font_t *font, uint32_t color)
{
    lv_obj_t *label = wq_label_create(parent, "", font, color);
    lv_obj_set_pos(label, x, y);
    lv_obj_set_width(label, w);
    lv_obj_set_height(label, h);
    lv_label_set_long_mode(label, LV_LABEL_LONG_MODE_WRAP);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, 0);
    // 行距压到 4px：16px 字库的行高本身是 20px。题面页虽然可滚动，但行距松一格
    // 就多滚一屏，读起来反而累。
    lv_obj_set_style_text_line_space(label, 4, 0);
    return label;
}

lv_obj_t *wq_note_create(lv_obj_t *parent, int x, int y, int w,
                         const char *text, uint32_t color)
{
    lv_obj_t *label = wq_label_create(parent, text, &wq_font_16, color);
    lv_obj_set_pos(label, x, y);
    lv_obj_set_width(label, w);
    lv_obj_set_height(label, LV_SIZE_CONTENT);
    lv_label_set_long_mode(label, LV_LABEL_LONG_MODE_DOTS);
    return label;
}

static void row_apply(wq_row_t *row, wq_state_t state)
{
    if (!row || !row->box) return;

    uint32_t bg = WQ_C_PANEL_ALT;
    uint32_t border = WQ_C_LINE;
    uint32_t ink = WQ_C_INK;
    uint32_t note_ink = WQ_C_MUTED;

    switch (state) {
        case WQ_STATE_SELECTED:
            bg = WQ_C_GOLD_S;
            border = WQ_C_GOLD;
            ink = WQ_C_GOLD_D;
            note_ink = WQ_C_GOLD_D;
            break;
        case WQ_STATE_GOOD:
            bg = WQ_C_PANEL_ALT;
            border = WQ_C_GREEN;
            ink = WQ_C_GREEN;
            note_ink = WQ_C_GREEN;
            break;
        case WQ_STATE_BAD:
            bg = WQ_C_PANEL_ALT;
            border = WQ_C_RED;
            ink = WQ_C_RED;
            note_ink = WQ_C_RED;
            break;
        case WQ_STATE_DISABLED:
            bg = WQ_C_PANEL;
            border = WQ_C_PANEL_ALT;
            ink = WQ_C_MUTED;
            note_ink = WQ_C_MUTED;
            break;
        case WQ_STATE_NORMAL:
        default:
            break;
    }

    lv_obj_set_style_bg_color(row->box, lv_color_hex(bg), 0);
    lv_obj_set_style_border_color(row->box, lv_color_hex(border), 0);
    if (row->tag) lv_obj_set_style_text_color(row->tag, lv_color_hex(ink), 0);
    if (row->text) lv_obj_set_style_text_color(row->text, lv_color_hex(ink), 0);
    if (row->note) lv_obj_set_style_text_color(row->note, lv_color_hex(note_ink), 0);
}

static wq_row_t row_build(lv_obj_t *parent, int x, int y, int w, int h,
                          int tag_width, int note_width, bool small)
{
    const lv_font_t *text_font = small ? &wq_font_16 : &wq_font_24;
    wq_row_t row = {0};
    row.box = plain_obj(parent, x, y, w, h);
    lv_obj_set_style_radius(row.box, 8, 0);
    lv_obj_set_style_bg_opa(row.box, LV_OPA_COVER, 0);
    // 边框宽度恒为 3，状态切换只换颜色，文字不会跳。
    lv_obj_set_style_border_width(row.box, WQ_ROW_BORDER, 0);

    // 左侧标记与右侧状态先把宽度占掉，主文字用剩下的 —— 状态永远贴着右边，
    // 不会因为主文字变长而被顶走。宽度为 0 表示这一侧没有东西。
    const int tag_w = tag_width > 0 ? tag_width : 0;
    const int note_w = note_width > 0 ? note_width : 0;
    const int inner = w - 2 * WQ_ROW_BORDER - 2 * WQ_ROW_PAD - tag_w - note_w;

    if (tag_w > 0) {
        // 标记与正文同字号，基线一致；不单独做一个小字号的方框，
        // 免得在 36px 的行高里塞两级字号反而更乱。
        row.tag = wq_label_create(row.box, "", text_font, WQ_C_INK);
        lv_obj_set_width(row.tag, tag_w);
        lv_obj_set_height(row.tag, LV_SIZE_CONTENT);
        lv_obj_align(row.tag, LV_ALIGN_LEFT_MID, WQ_ROW_PAD, 0);
    }

    // 文字宽度写死，不让它按内容自己长；真放不下时 LVGL 打省略号，
    // 不会溢出到边框外面。
    row.text = wq_label_create(row.box, "", text_font, WQ_C_INK);
    lv_obj_set_width(row.text, inner);
    lv_obj_set_height(row.text, LV_SIZE_CONTENT);
    lv_label_set_long_mode(row.text, LV_LABEL_LONG_MODE_DOTS);
    lv_obj_align(row.text, LV_ALIGN_LEFT_MID, WQ_ROW_PAD + tag_w, 0);

    if (note_w > 0) {
        row.note = wq_label_create(row.box, "", &wq_font_16, WQ_C_MUTED);
        lv_obj_set_width(row.note, note_w);
        lv_obj_set_height(row.note, LV_SIZE_CONTENT);
        lv_label_set_long_mode(row.note, LV_LABEL_LONG_MODE_DOTS);
        lv_obj_set_style_text_align(row.note, LV_TEXT_ALIGN_RIGHT, 0);
        lv_obj_align(row.note, LV_ALIGN_RIGHT_MID, -WQ_ROW_PAD, 0);
    }

    row_apply(&row, WQ_STATE_NORMAL);
    return row;
}

wq_row_t wq_row_create(lv_obj_t *parent, int x, int y, int w, int h,
                       int tag_width, int note_width)
{
    return row_build(parent, x, y, w, h, tag_width, note_width, false);
}

wq_row_t wq_row_small_create(lv_obj_t *parent, int x, int y, int w, int h,
                             int tag_width, int note_width)
{
    return row_build(parent, x, y, w, h, tag_width, note_width, true);
}

void wq_row_update(wq_row_t *row, const char *tag, const char *text,
                   const char *note, wq_state_t state)
{
    if (!row || !row->box) return;
    if (row->tag) lv_label_set_text(row->tag, tag ? tag : "");
    if (row->text) lv_label_set_text(row->text, text ? text : "");
    if (row->note) lv_label_set_text(row->note, note ? note : "");
    row_apply(row, state);
}

void wq_row_set_state(wq_row_t *row, wq_state_t state)
{
    row_apply(row, state);
}

// ------------------------------------------------------------ 棋盘视图 -----

// 交叉点 (x,y) 的像素坐标（视图内）。
static int grid_px(int cell, int margin, int index)
{
    return margin + index * cell;
}

void wq_board_view_create(wq_board_view_t *view, lv_obj_t *parent, int x, int y, int cell)
{
    const int size = WQ_BOARD_VIEW_PX(cell);
    view->cell = cell;
    view->margin = cell / 2;
    view->stone = cell - 4 > 10 ? cell - 4 : 10;

    // 木色底板。
    view->box = plain_obj(parent, x, y, size, size);
    lv_obj_set_style_bg_color(view->box, lv_color_hex(WQ_C_WOOD), 0);
    lv_obj_set_style_bg_opa(view->box, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(view->box, 6, 0);

    // 18 条线（9 横 9 竖），1px。
    for (int i = 0; i < WQ_BOARD; i++) {
        const int p = grid_px(view->cell, view->margin, i);
        filled(view->box, view->margin, p, size - 2 * view->margin, 1, WQ_C_WOOD_LINE);
        filled(view->box, p, view->margin, 1, size - 2 * view->margin, WQ_C_WOOD_LINE);
    }

    // 星位：9x9 的 (2,2) (2,6) (6,2) (6,6) (4,4)。
    static const uint8_t stars[5][2] = {
        { 2, 2 }, { 2, 6 }, { 6, 2 }, { 6, 6 }, { 4, 4 },
    };
    for (int i = 0; i < 5; i++) {
        const int px = grid_px(view->cell, view->margin, stars[i][0]);
        const int py = grid_px(view->cell, view->margin, stars[i][1]);
        lv_obj_t *dot = filled(view->box, px - 1, py - 1, 3, 3, WQ_C_WOOD_LINE);
        lv_obj_set_style_radius(dot, LV_RADIUS_CIRCLE, 0);
    }

    // 每个交叉点一个棋子对象（圆）。空点隐藏。
    for (uint8_t p = 0; p < WQ_BOARD_POINTS; p++) {
        const int px = grid_px(view->cell, view->margin, p % WQ_BOARD);
        const int py = grid_px(view->cell, view->margin, p / WQ_BOARD);
        lv_obj_t *stone = plain_obj(view->box, px - view->stone / 2, py - view->stone / 2,
                                    view->stone, view->stone);
        lv_obj_set_style_radius(stone, LV_RADIUS_CIRCLE, 0);
        lv_obj_set_style_border_width(stone, 1, 0);
        lv_obj_set_style_border_color(stone, lv_color_hex(WQ_C_WOOD_LINE), 0);
        lv_obj_add_flag(stone, LV_OBJ_FLAG_HIDDEN);
        view->stones[p] = stone;
    }

    // 标记：最多 WQ_MARKS_MAX 个 16px 字形叠在交叉点上。
    for (uint8_t i = 0; i < WQ_MARKS_MAX; i++) {
        lv_obj_t *mark = wq_label_create(view->box, "", &wq_font_16, WQ_C_RED);
        lv_obj_add_flag(mark, LV_OBJ_FLAG_HIDDEN);
        view->marks[i] = mark;
    }

    // 光标：金色方框，套在交叉点外面。
    const int cursor_size = cell + 4;
    view->cursor = plain_obj(view->box, 0, 0, cursor_size, cursor_size);
    lv_obj_set_style_bg_opa(view->cursor, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(view->cursor, 2, 0);
    lv_obj_set_style_border_color(view->cursor, lv_color_hex(WQ_C_GOLD), 0);
    lv_obj_set_style_radius(view->cursor, 3, 0);
}

void wq_board_view_sync(wq_board_view_t *view, const wq_session_t *session)
{
    const wq_level_t *level = wq_session_level(session);
    if (!level || !view->box) return;

    for (uint8_t p = 0; p < WQ_BOARD_POINTS; p++) {
        lv_obj_t *stone = view->stones[p];
        const uint8_t color = session->board.cells[p];
        if (color == WQ_COLOR_EMPTY) {
            lv_obj_add_flag(stone, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_obj_remove_flag(stone, LV_OBJ_FLAG_HIDDEN);
            lv_obj_set_style_bg_color(
                stone, lv_color_hex(color == WQ_COLOR_BLACK ? WQ_C_STONE_B : WQ_C_STONE_W), 0);
        }
    }

    uint8_t shown = 0;
    for (uint8_t mi = 0; mi < level->mark_count && shown < WQ_MARKS_MAX; mi++) {
        const uint8_t point = level->mark_points[mi];
        lv_obj_t *mark = view->marks[shown++];
        lv_label_set_text(mark, level->mark_glyphs[mi]);
        const int px = grid_px(view->cell, view->margin, point % WQ_BOARD);
        const int py = grid_px(view->cell, view->margin, point / WQ_BOARD);
        // 字形高 20px、宽至多 32px（两位数字）；以交叉点为中心摆放。
        lv_obj_move_foreground(mark);
        lv_obj_set_pos(mark, px - 8, py - 10);
        // 颜色随底下棋子自适应：黑子上用亮金，木底/白子上用深红。
        const uint8_t under = session->board.cells[point];
        const bool on_black = level->stone_count > 0 && under == WQ_COLOR_BLACK &&
                              !lv_obj_has_flag(view->stones[point], LV_OBJ_FLAG_HIDDEN);
        lv_obj_set_style_text_color(
            mark, lv_color_hex(on_black ? WQ_C_GOLD_D : WQ_C_RED), 0);
        lv_obj_remove_flag(mark, LV_OBJ_FLAG_HIDDEN);
    }
    for (uint8_t i = shown; i < WQ_MARKS_MAX; i++) {
        lv_obj_add_flag(view->marks[i], LV_OBJ_FLAG_HIDDEN);
    }

    const uint8_t cursor = wq_session_cursor(session);
    const int px = grid_px(view->cell, view->margin, cursor % WQ_BOARD);
    const int py = grid_px(view->cell, view->margin, cursor / WQ_BOARD);
    lv_obj_set_pos(view->cursor, px - view->cell / 2 - 2, py - view->cell / 2 - 2);
}

void wq_board_view_hide_cursor(wq_board_view_t *view)
{
    if (view && view->cursor) lv_obj_add_flag(view->cursor, LV_OBJ_FLAG_HIDDEN);
}
