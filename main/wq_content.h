// 由 tools/weiqi/gen_content.py 从 tools/weiqi/levels.txt 生成。
// 请勿手改；改关卡源文件后重跑生成器（validate.sh 会用 --check 拦住过期的表）。

#pragma once

#include <stdint.h>

/* 棋盘。所有关卡统一裁剪进 9x9 窗口（extract_levels.mjs 负责）， */
/* 点下标 = y * WQ_BOARD + x，坐标串 aa..ii 对应左上..右下。 */
#define WQ_BOARD 9
#define WQ_BOARD_POINTS 81

/* 关卡与章节规模。 */
#define WQ_LEVEL_COUNT 154
#define WQ_CHAPTER_COUNT 7

/* 实测规模上限（生成器按真实数据算出，界面与测试用它开缓冲）。 */
#define WQ_STONES_MAX 43
#define WQ_CORRECT_PATHS_MAX 4
#define WQ_CORRECT_MOVES_MAX 9
#define WQ_MARKS_MAX 11
#define WQ_OPTIONS_MAX 3
#define WQ_REMOVAL_MAX 4

/* 设备版式预算，来源是 tools/weiqi/content.py 顶部那张算术推导。
 * 宿主测试拿真实题库断言折行结果不超这些值。 */
#define WQ_TITLE_MAX_CHARS 13
#define WQ_INSTRUCTION_MAX_CHARS 240
#define WQ_QUESTION_MAX_CHARS 190
#define WQ_OPTION_TEXT_MAX_CHARS 10

/* 评级规则，与网页版 computeStars / pointsForStars 一致。 */
#define WQ_STARS_FOR_ZERO_WRONG 3
#define WQ_STARS_FOR_ONE_WRONG 2
#define WQ_STARS_FOR_REST 1
#define WQ_POINTS_PER_STAR 100

/* 题型。终局三态是 endingGame 的三种交互。 */
typedef enum {
    WQ_KIND_PUZZLE = 0,  /* 落子解谜：按正解路径走完即过 */
    WQ_KIND_CHOICE,      /* 选择题：题干 + 棋盘展示 + 选项 */
    WQ_KIND_END_PASS,    /* 终局教学：只读棋盘，确定即停一手 */
    WQ_KIND_END_REMOVE,  /* 终局教学：移除全部死子（targets） */
    WQ_KIND_END_FINISH,  /* 终局教学：只读棋盘，确定即完成 */
} wq_kind_t;

/* 一条正解路径：从玩家先手开始的连续着法（黑白交替）。 */
typedef struct {
    uint8_t len;
    const uint8_t *moves;  /* 点下标序列，len 个 */
} wq_path_t;

typedef struct {
    const char *title;              /* 关卡标题，顶栏 */
    const char *instruction;        /* 题面说明，题面页（可滚动） */
    uint8_t kind;                   /* wq_kind_t */
    uint8_t player;                 /* 先手颜色：1=黑 2=白（puzzle 用） */
    const uint8_t *stones;          /* {点, 颜色} 序列，stone_count 对 */
    uint8_t stone_count;
    const uint8_t *mark_points;     /* 标记点，mark_count 个 */
    const char *const *mark_glyphs; /* 与 mark_points 一一对应的字形 */
    uint8_t mark_count;
    const wq_path_t *correct;       /* 正解路径（puzzle 用） */
    uint8_t correct_count;
    const char *question;           /* 题干（choice 用） */
    const char *const *options;     /* 选项（choice 用） */
    uint8_t option_count;
    uint8_t answer;                 /* 正确选项下标（choice 用） */
    const uint8_t *targets;         /* 待移除死子（END_REMOVE 用） */
    uint8_t target_count;
} wq_level_t;

typedef struct {
    const char *title;  /* 章节名（如「青铜 · 入门启蒙」） */
    uint16_t first;     /* 首关在全局关卡数组里的下标 */
    uint16_t count;     /* 关卡数 */
} wq_chapter_t;

extern const wq_level_t wq_levels[WQ_LEVEL_COUNT];
extern const wq_chapter_t wq_chapters[WQ_CHAPTER_COUNT];
