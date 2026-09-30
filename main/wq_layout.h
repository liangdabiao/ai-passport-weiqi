// main/wq_layout.h —— 版式几何、每行字数预算与配色。
//
// 刻意不依赖 LVGL：这些数字是「一屏放得下」的算术两端，界面（wq_ui）与宿主
// 测试（tests/test_wq_wrap.c）必须引用**同一份**定义 —— 复制一份迟早走样。
#pragma once

// ---------------------------------------------------------------- 配色 -----
// 全部由网页版《围棋闯关》的十六进制值转成 RGB565（R5 G6 B5），转换过程记在
// 注释里，免得以后有人对着一个 0xF62A 猜它原本是什么颜色。
#define WQ_C_SCREEN     0x18E5   // 逻辑屏底：#1a1d2e 深蓝夜空
#define WQ_C_PANEL      0x0948   // 页面卡片：#232845 深蓝面板
#define WQ_C_PANEL_ALT  0x298A   // 次级面板：#2a3050 行底（未选中）
#define WQ_C_INK        0xEF5E   // 正文：#e8e8f0 亮灰白
#define WQ_C_INK_SOFT   0xC65B   // 次级正文：#c5c9dd
#define WQ_C_MUTED      0x8C74   // 次级文字：#8b8fa3 灰蓝
#define WQ_C_GOLD       0xF62A   // 金：#f5c451 强调与当前选择
#define WQ_C_GOLD_D     0xFEAE   // 亮金：#ffd470 选中行里的文字
#define WQ_C_GOLD_S     0x49C2   // 金淡：#4a3a15 选中行的底
#define WQ_C_LINE       0x31CB   // 行边框：#33395c
#define WQ_C_HINTINK    0x8C74   // 底栏提示文字（与 muted 同源）
#define WQ_C_GREEN      0x6E71   // 对：#6bce8a
#define WQ_C_RED        0xE267   // 错：#e74c3c
#define WQ_C_WOOD       0xDD8B   // 棋盘木色：#dcb35c
#define WQ_C_WOOD_LINE  0x3943   // 棋盘线：#3a2a1a 深棕
#define WQ_C_STONE_B    0x2060   // 黑子：#210f00 近黑（比纯黑温和）
#define WQ_C_STONE_W    0xFFDF   // 白子：#fffeff 近白

// --------------------------------------------------------------- 版式 ------
#define WQ_SCREEN_W     240
#define WQ_SCREEN_H     320
#define WQ_PAGE_INSET   5
#define WQ_PAGE_W       (WQ_SCREEN_W - 2 * WQ_PAGE_INSET)          // 230
#define WQ_PAGE_H       (WQ_SCREEN_H - 2 * WQ_PAGE_INSET)          // 310
#define WQ_PAGE_RADIUS  25
#define WQ_BAR_H        36
#define WQ_HINT_H       26
#define WQ_BODY_TOP     WQ_BAR_H                                    // 36
#define WQ_BODY_BOTTOM  (WQ_PAGE_H - WQ_HINT_H)                    // 284
#define WQ_BODY_H       (WQ_BODY_BOTTOM - WQ_BODY_TOP)              // 248
#define WQ_BODY_X       10
#define WQ_BODY_W       (WQ_PAGE_W - 2 * WQ_BODY_X)                // 210

// ------------------------------------------------------- 每行字数预算 -----
// 「一屏放得下」不是感觉，是一道除法：内容区宽 210px，同一字号下汉字等宽
// （Noto Sans CJK 的全角字形，前进宽度就等于字号），所以每行几个字 = 除法取整。
#define WQ_CHARS_HEADLINE 6   // 32px
#define WQ_CHARS_BODY     8   // 24px
#define WQ_CHARS_SMALL    13  // 16px
