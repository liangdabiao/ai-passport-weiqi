// main/wq_app.h —— 导航、应用状态与按键语义。
//
// 硬件只有三个键（上/下/确定，共用一个 ADC 分压引脚），所以全局只用一套语义：
//   上 / 下 短按   在当前页面里移动（选项、列表、题面滚动、棋盘光标上下）
//   上 / 下 长按   棋盘光标左右（仅作答页；列表页忽略）
//   确定    短按   往下走一步（确认 / 落子 / 作答 / 下一关）
//   确定    长按   返回上一层（作答中先回题面，再按回关卡列表）
//
// 页面模块只实现「进入 / 离开 / 按键」三个动作，页面之间怎么跳由页面自己调
// goto_*（与侨批同构）：谁触发的跳转写在谁那里，「返回该回哪儿」就只有一处答案。
#pragma once

#include "lvgl.h"

#include "wq_progress.h"
#include "wq_session.h"

// 建立并加载标题页。需在持有 LVGL 锁时调用。
void wq_app_start(void);

// 处理一次按键。内部自行加解锁，可从任意任务调用。
void wq_app_key(wq_key_t key);

// ---- 页面跳转。都在持有 LVGL 锁的前提下调用（页面模块内部使用）----
void wq_app_goto_title(void);
void wq_app_goto_world(void);
void wq_app_goto_levels(void);
void wq_app_goto_play(void);
void wq_app_goto_result(void);

// ---- 共享状态。页面模块通过这几个入口读写，不各自持有副本 ----
wq_session_t *wq_app_session(void);
const wq_progress_t *wq_app_progress(void);

// 当前音量档位（0 = 关）。档位表与缩放算术在 main/wq_volume.c。
uint8_t wq_app_volume(void);
// 切到下一个档位并落盘（标题页的「音量」项用确定键调它）。到顶回绕到关。
void wq_app_cycle_volume(void);
// 把当前档位写进 out（"关" / "80%"）。返回写入的字节数，容量不足返回 0。
uint16_t wq_app_volume_text(char *out, size_t capacity);

// 过关结算：把当前关的星级并进存档（只升不降）并落盘。
// 由作答页在 WQ_ACT_PASSED 那一刻调用，每次过关恰好一次。
void wq_app_commit_result(void);

// 清空全部记录（星级与最近进度），并落盘。
void wq_app_reset_progress(void);

// ---- 页面模块（只由导航层与 wq_app_key 调用）----
lv_obj_t *wq_page_title_enter(void);
void wq_page_title_leave(void);
void wq_page_title_key(wq_key_t key);

lv_obj_t *wq_page_world_enter(void);
void wq_page_world_leave(void);
void wq_page_world_key(wq_key_t key);

lv_obj_t *wq_page_levels_enter(void);
void wq_page_levels_leave(void);
void wq_page_levels_key(wq_key_t key);

lv_obj_t *wq_page_play_enter(void);
void wq_page_play_leave(void);
void wq_page_play_key(wq_key_t key);
// 作答页内部在题面/作答两个形态之间重排（session 阶段变化后由本页或导航层调）。
void wq_page_play_refresh(void);

lv_obj_t *wq_page_result_enter(void);
void wq_page_result_leave(void);
void wq_page_result_key(wq_key_t key);
