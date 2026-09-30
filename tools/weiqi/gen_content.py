#!/usr/bin/env python3
"""从关卡源文件生成 ``main/wq_content.c`` 与 ``main/wq_content.h``。

与 qiaopi 的 gen_content.py 同构：C 表只是 ``tools/weiqi/levels.txt`` 的投影，
除此之外没有任何来源。在仓库根目录运行：

    python3 tools/weiqi/gen_content.py            # 重新生成两张表
    python3 tools/weiqi/gen_content.py --check    # 只校验，过期就失败

``--check`` 是 CI 与 ``tools/validate.sh`` 用的那一个：改了关卡却忘了重新生成，
会在这里失败，而不是把一个过期的表发到设备上。
"""
from __future__ import annotations

import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import content  # noqa: E402  （上面的 sys.path 已经指到同目录）

ROOT = Path(__file__).resolve().parents[2]
OUT_C = ROOT / "main" / "wq_content.c"
OUT_H = ROOT / "main" / "wq_content.h"

HEADER_NOTICE = (
    "// 由 tools/weiqi/gen_content.py 从 tools/weiqi/levels.txt 生成。\n"
    "// 请勿手改；改关卡源文件后重跑生成器（validate.sh 会用 --check 拦住过期的表）。\n"
)

KIND_ENUM = {
    "puzzle": "WQ_KIND_PUZZLE",
    "multipleChoice": "WQ_KIND_CHOICE",
    "endingGame": None,  # 按交互细分，见 kind_of()
}

INTERACTION_ENUM = {
    "pass": "WQ_KIND_END_PASS",
    "stoneRemoval": "WQ_KIND_END_REMOVE",
    "finish": "WQ_KIND_END_FINISH",
}

# 与网页版 computeStars 一致：0 错 3 星，1 错 2 星，2 错及以上 1 星。
STARS_RULE = (
    "#define WQ_STARS_FOR_ZERO_WRONG 3\n"
    "#define WQ_STARS_FOR_ONE_WRONG 2\n"
    "#define WQ_STARS_FOR_REST 1\n"
    "#define WQ_POINTS_PER_STAR 100\n"
)


def c_string(text: str) -> str:
    """把任意 UTF-8 文本变成 C 字符串字面量。"""
    escaped = text.replace("\\", "\\\\").replace('"', '\\"').replace("\t", "\\t")
    return f'"{escaped}"'


def kind_of(level: content.Level) -> str:
    if level.kind == "puzzle":
        return "WQ_KIND_PUZZLE"
    if level.kind == "multipleChoice":
        return "WQ_KIND_CHOICE"
    return INTERACTION_ENUM[level.interaction]


def point_bytes(points: list[int]) -> str:
    return ", ".join(str(p) for p in points)


def stone_bytes(level: content.Level) -> str:
    return ", ".join(f"{p}, {color}" for p, color in level.stone_points())


def mark_glyph(shape: str) -> str:
    return content.MARK_GLYPHS.get(shape, shape)


def render_header(levels: list[content.Level]) -> str:
    bounds = content.chapter_bounds(levels)
    stones_max = max(len(level.black) + len(level.white) for level in levels)
    paths_max = max((len(level.correct) for level in levels if level.kind == "puzzle"), default=0)
    moves_max = max(
        (len(path) for level in levels if level.kind == "puzzle" for path in level.correct),
        default=0,
    )
    marks_max = max((sum(len(pts) for _, pts in level.marks) for level in levels), default=0)
    options_max = max((len(level.options) for level in levels if level.kind == "multipleChoice"), default=0)
    removal_max = max((len(level.targets) for level in levels if level.is_ending_removal), default=0)

    lines = [
        HEADER_NOTICE,
        "#pragma once",
        "",
        "#include <stdint.h>",
        "",
        "/* 棋盘。所有关卡统一裁剪进 9x9 窗口（extract_levels.mjs 负责）， */",
        "/* 点下标 = y * WQ_BOARD + x，坐标串 aa..ii 对应左上..右下。 */",
        f"#define WQ_BOARD {content.BOARD}",
        f"#define WQ_BOARD_POINTS {content.BOARD_POINTS}",
        "",
        "/* 关卡与章节规模。 */",
        f"#define WQ_LEVEL_COUNT {len(levels)}",
        f"#define WQ_CHAPTER_COUNT {len(content.CHAPTERS)}",
        "",
        "/* 实测规模上限（生成器按真实数据算出，界面与测试用它开缓冲）。 */",
        f"#define WQ_STONES_MAX {stones_max}",
        f"#define WQ_CORRECT_PATHS_MAX {paths_max}",
        f"#define WQ_CORRECT_MOVES_MAX {moves_max}",
        f"#define WQ_MARKS_MAX {marks_max}",
        f"#define WQ_OPTIONS_MAX {options_max}",
        f"#define WQ_REMOVAL_MAX {removal_max}",
        "",
        "/* 设备版式预算，来源是 tools/weiqi/content.py 顶部那张算术推导。",
        " * 宿主测试拿真实题库断言折行结果不超这些值。 */",
        f"#define WQ_TITLE_MAX_CHARS {content.TITLE_MAX_CHARS}",
        f"#define WQ_INSTRUCTION_MAX_CHARS {content.INSTRUCTION_MAX_CHARS}",
        f"#define WQ_QUESTION_MAX_CHARS {content.QUESTION_MAX_CHARS}",
        f"#define WQ_OPTION_TEXT_MAX_CHARS {content.OPTION_TEXT_MAX_CHARS}",
        "",
        "/* 评级规则，与网页版 computeStars / pointsForStars 一致。 */",
        STARS_RULE,
        "/* 题型。终局三态是 endingGame 的三种交互。 */",
        "typedef enum {",
        "    WQ_KIND_PUZZLE = 0,  /* 落子解谜：按正解路径走完即过 */",
        "    WQ_KIND_CHOICE,      /* 选择题：题干 + 棋盘展示 + 选项 */",
        "    WQ_KIND_END_PASS,    /* 终局教学：只读棋盘，确定即停一手 */",
        "    WQ_KIND_END_REMOVE,  /* 终局教学：移除全部死子（targets） */",
        "    WQ_KIND_END_FINISH,  /* 终局教学：只读棋盘，确定即完成 */",
        "} wq_kind_t;",
        "",
        "/* 一条正解路径：从玩家先手开始的连续着法（黑白交替）。 */",
        "typedef struct {",
        "    uint8_t len;",
        "    const uint8_t *moves;  /* 点下标序列，len 个 */",
        "} wq_path_t;",
        "",
        "typedef struct {",
        "    const char *title;              /* 关卡标题，顶栏 */",
        "    const char *instruction;        /* 题面说明，题面页（可滚动） */",
        "    uint8_t kind;                   /* wq_kind_t */",
        "    uint8_t player;                 /* 先手颜色：1=黑 2=白（puzzle 用） */",
        "    const uint8_t *stones;          /* {点, 颜色} 序列，stone_count 对 */",
        "    uint8_t stone_count;",
        "    const uint8_t *mark_points;     /* 标记点，mark_count 个 */",
        "    const char *const *mark_glyphs; /* 与 mark_points 一一对应的字形 */",
        "    uint8_t mark_count;",
        "    const wq_path_t *correct;       /* 正解路径（puzzle 用） */",
        "    uint8_t correct_count;",
        "    const char *question;           /* 题干（choice 用） */",
        "    const char *const *options;     /* 选项（choice 用） */",
        "    uint8_t option_count;",
        "    uint8_t answer;                 /* 正确选项下标（choice 用） */",
        "    const uint8_t *targets;         /* 待移除死子（END_REMOVE 用） */",
        "    uint8_t target_count;",
        "} wq_level_t;",
        "",
        "typedef struct {",
        "    const char *title;  /* 章节名（如「青铜 · 入门启蒙」） */",
        "    uint16_t first;     /* 首关在全局关卡数组里的下标 */",
        "    uint16_t count;     /* 关卡数 */",
        "} wq_chapter_t;",
        "",
        "extern const wq_level_t wq_levels[WQ_LEVEL_COUNT];",
        "extern const wq_chapter_t wq_chapters[WQ_CHAPTER_COUNT];",
        "",
    ]
    return "\n".join(lines)


def render_source(levels: list[content.Level]) -> str:
    lines = [
        HEADER_NOTICE,
        '#include "wq_content.h"',
        "",
        "#include <stddef.h>  /* NULL */",
        "",
    ]

    for index, level in enumerate(levels):
        tag = f"static const uint8_t level_{index:03d}"

        if level.stone_points():
            lines.append(f"{tag}_stones[] = {{ {stone_bytes(level)} }};")
        if level.marks:
            points: list[int] = []
            glyphs: list[str] = []
            for shape, pts in level.marks:
                for _ in pts:
                    glyphs.append(mark_glyph(shape))
                points.extend(pts)
            lines.append(f"{tag}_mark_points[] = {{ {point_bytes(points)} }};")
            glyph_rows = ", ".join(c_string(g) for g in glyphs)
            lines.append(f"static const char *const level_{index:03d}_glyphs[] = {{ {glyph_rows} }};")
        for path_index, path in enumerate(level.correct):
            moves = ", ".join(str(m) for m in path)
            lines.append(f"{tag}_path_{path_index}[] = {{ {moves} }};")
        if level.correct:
            rows = ", ".join(
                f"{{ {len(path)}, level_{index:03d}_path_{pi} }}"
                for pi, path in enumerate(level.correct)
            )
            lines.append(f"static const wq_path_t level_{index:03d}_correct[] = {{ {rows} }};")
        if level.is_ending_removal:
            lines.append(f"{tag}_targets[] = {{ {point_bytes(level.targets)} }};")
        if level.kind == "multipleChoice":
            option_rows = ", ".join(c_string(option) for option in level.options)
            lines.append(f"static const char *const level_{index:03d}_options[] = {{ {option_rows} }};")
        lines.append("")

    level_rows = []
    for index, level in enumerate(levels):
        stones_ref = (
            f"level_{index:03d}_stones, {len(level.black) + len(level.white)}"
            if level.black or level.white else "NULL, 0"
        )
        if level.marks:
            mark_ref = (
                f"level_{index:03d}_mark_points, level_{index:03d}_glyphs, "
                f"{sum(len(pts) for _, pts in level.marks)}"
            )
        else:
            mark_ref = "NULL, NULL, 0"
        correct_ref = (
            f"level_{index:03d}_correct, {len(level.correct)}"
            if level.correct else "NULL, 0"
        )
        targets_ref = (
            f"level_{index:03d}_targets, {len(level.targets)}"
            if level.is_ending_removal else "NULL, 0"
        )
        if level.kind == "multipleChoice":
            question = c_string(level.question)
            options_ref = f"level_{index:03d}_options, {len(level.options)}, {level.answer}"
        else:
            question = '""'
            options_ref = "NULL, 0, 0"
        level_rows.append(
            "    {\n"
            f"        .title = {c_string(level.title)},\n"
            f"        .instruction = {c_string(level.instruction)},\n"
            f"        .kind = {kind_of(level)},\n"
            f"        .player = {1 if level.player == 'black' else 2},\n"
            f"        .stones = {stones_ref.split(', ')[0]},\n"
            f"        .stone_count = {stones_ref.split(', ')[1]},\n"
            f"        .mark_points = {mark_ref.split(', ')[0]},\n"
            f"        .mark_glyphs = {mark_ref.split(', ')[1]},\n"
            f"        .mark_count = {mark_ref.split(', ')[2]},\n"
            f"        .correct = {correct_ref.split(', ')[0]},\n"
            f"        .correct_count = {correct_ref.split(', ')[1]},\n"
            f"        .question = {question},\n"
            f"        .options = {options_ref.split(', ')[0]},\n"
            f"        .option_count = {options_ref.split(', ')[1]},\n"
            f"        .answer = {options_ref.split(', ')[2]},\n"
            f"        .targets = {targets_ref.split(', ')[0]},\n"
            f"        .target_count = {targets_ref.split(', ')[1]},\n"
            "    },"
        )

    chapter_rows = []
    for chapter_index, first, count in content.chapter_bounds(levels):
        title = content.CHAPTERS[chapter_index][1]
        chapter_rows.append(
            f"    {{ {c_string(title)}, {first}, {count} }},"
        )

    lines.extend([
        f"const wq_level_t wq_levels[WQ_LEVEL_COUNT] = {{",
        *level_rows,
        "};",
        "",
        f"const wq_chapter_t wq_chapters[WQ_CHAPTER_COUNT] = {{",
        *chapter_rows,
        "};",
        "",
    ])
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--check", action="store_true", help="只校验，过期就失败")
    args = parser.parse_args()

    try:
        levels = content.load_levels()
        problems = content.validate(levels)
    except content.ContentError as err:
        print(f"内容校验失败：{err}", file=sys.stderr)
        return 1
    if problems:
        print("内容校验失败：", file=sys.stderr)
        for problem in problems:
            print(f"  - {problem}", file=sys.stderr)
        return 1

    header = render_header(levels)
    source = render_source(levels)

    if args.check:
        stale = []
        for path, expected in ((OUT_H, header), (OUT_C, source)):
            if not path.is_file() or path.read_text(encoding="utf-8") != expected:
                stale.append(str(path))
        if stale:
            print(f"STALE: {', '.join(stale)} —— 关卡内容已变化，请重跑 gen_content.py",
                  file=sys.stderr)
            return 1
        return 0

    OUT_H.write_text(header, encoding="utf-8")
    OUT_C.write_text(source, encoding="utf-8")
    print(f"已生成 {OUT_H} 与 {OUT_C}：{len(levels)} 关")
    return 0


if __name__ == "__main__":
    sys.exit(main())
