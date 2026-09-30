// main/wq_session.h —— 闯关状态机：选章 / 选关 / 题面 / 作答 / 结算。
//
// 与 qiaopi 的 qpq_session 同构：纯逻辑、不依赖 ESP-IDF 与 LVGL，宿主测试直接
// 编译；页面模块只做「把 session 的状态画出来、把按键喂进来」。
//
// 判题模型与网页版 move_tree 一致：
//   * 正解路径是内容里脚本化的序列（黑白交替，从玩家先手开始）；
//   * 玩家每一手必须延续**某一条**还没走完的候选路径 —— 走完任一条即过关；
//   * 对手应手取「第一条仍然匹配的候选路径」的下一手（网页引擎按分支插入序
//     自动落子，语义相同）；
//   * 合法但不延续任何路径的一手 = 走错：错误数 +1，棋盘复位重开（网页版
//     走错后 bump resetKey 重建棋面，行为一致）；
//   * 占位 / 自杀 / 劫回提在引擎层就落不下去，不算错误，光标原地不动。
//
// 星级与网页版 computeStars 一致：0 错 3 星、1 错 2 星、2 错及以上 1 星。
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wq_engine.h"

typedef enum {
    WQ_STAGE_WORLD = 0,  // 世界地图：选章节
    WQ_STAGE_LEVELS,     // 关卡列表：选关卡
    WQ_STAGE_BRIEF,      // 题面页：读说明（可滚动）
    WQ_STAGE_SOLVE,      // 作答：落子 / 选择 / 终局
    WQ_STAGE_RESULT,     // 结算
} wq_stage_t;

// 按键。硬件三个键 + 派生：
//   上 / 下 短按   移动（列表选项、棋盘光标上下、题面滚动）
//   上 / 下 双击   棋盘光标左右（列表页忽略；真机反馈长按太慢，改双击）
//   确定    短按   确认（进入 / 落子 / 作答 / 下一关）
//   确定    长按   返回上一层（作答中 = 放弃本关回关卡列表）
typedef enum {
    WQ_KEY_UP = 0,
    WQ_KEY_DOWN,
    WQ_KEY_LEFT,
    WQ_KEY_RIGHT,
    WQ_KEY_OK,
    WQ_KEY_BACK,
    WQ_KEY_COUNT,
} wq_key_t;

// 按键事件给应用层的回执。应用层据此跳页、播音效、落盘。
typedef enum {
    WQ_ACT_NONE = 0,
    WQ_ACT_MOVED,      // 光标 / 选项 / 滚动动了（页面重画）
    WQ_ACT_ENTERED,    // 进入一关（应用层跳题面页）
    WQ_ACT_PLACED,     // 落了一子（重画棋盘）
    WQ_ACT_WRONG,      // 走错（错误音 + 重画：棋盘已复位）
    WQ_ACT_PASSED,     // 过关（应用层记星、跳结算页）
    WQ_ACT_LEFT,       // 返回上一层（应用层跳页）
    WQ_ACT_BOARD_READY,// 作答状态已就绪（BRIEF 按 OK 进入 SOLVE 时）
} wq_action_t;

typedef struct {
    wq_stage_t stage;

    uint8_t chapter;         // 世界地图光标：章节下标
    uint16_t level;          // 当前关卡（全局下标）
    uint16_t level_cursor;   // 关卡列表光标（章内偏移）
    uint16_t scroll;         // 题面页滚动行
    uint16_t scroll_max;     // 题面页最大滚动行（页面进入时按版式写入）

    // ---- 作答状态 ----
    wq_board_t board;
    uint8_t cursor;          // 落子光标（点下标）
    uint8_t option;          // 选择题选项光标
    uint8_t depth;           // 当前路径深度（已走手数）
    bool alive[WQ_CORRECT_PATHS_MAX]; // 候选路径存活表
    uint8_t wrong_count;     // 本关错误次数
    uint8_t removed[WQ_REMOVAL_MAX];  // END_REMOVE 已移除的点
    uint8_t removed_count;
    uint8_t result_stars;    // 结算时定下的星级
    bool board_dirty;        // 棋面已变（落子/提子/复位/移除），页面需要重画棋盘
} wq_session_t;

// 初始化到世界地图。进度光标的落点（最近章节、第一个未通关）由应用层
// 拿存档算好后写 chapter / level_cursor —— session 不持有存档。
void wq_session_init(wq_session_t *session);

// 喂一次按键。恒可用：页面只管转发。
wq_action_t wq_session_key(wq_session_t *session, wq_key_t key);

// ---- 页面要的派生查询 ----

// 当前关卡（LEVELS/BRIEF/SOLVE/RESULT 阶段有效）。
const wq_level_t *wq_session_level(const wq_session_t *session);

// 作答是否已经完成本关（路径走完 / 死子移完 / 终局确认）。RESULT 阶段恒 true。
bool wq_session_solved(const wq_session_t *session);

// 结算星级。仅 RESULT 阶段有意义。
uint8_t wq_session_result_stars(const wq_session_t *session);

// 走错之后的复位次数（本关）。星级由它派生。
uint8_t wq_session_wrong_count(const wq_session_t *session);

// 光标（SOLVE，puzzle / END_REMOVE 阶段）。
uint8_t wq_session_cursor(const wq_session_t *session);

// 某点是否已被移除（END_REMOVE）。
bool wq_session_removed(const wq_session_t *session, uint8_t point);

// 下一关是否存在（RESULT 页决定「下一关」还是「回到章节」）。
bool wq_session_has_next(const wq_session_t *session);
