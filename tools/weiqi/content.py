"""围棋闯关 —— 设备版内容的解析、校验与版式预算。

与 qiaopi 的 content.py 同构：这是内容层的唯一入口，``gen_content.py``（投影成
C 表）与 ``gen_font.py``（推导字符清单）都 import 本模块，所以「关卡里有什么」
和「该给字库准备哪些字」不会各说各话。

源文件是 ``tools/weiqi/levels.txt``：每关一个区块，以 ``== <序号> <源id>`` 开头，
随后是 ``key: value`` 行。格式要点：

    == 001 fundamentals-rules-intro-3
    chapter: fundamentals
    kind: puzzle            # puzzle | multipleChoice | endingGame
    title: 围棋游戏 · 3/6
    player: white           # 玩家先手颜色（puzzle 用）
    black: cg               # 黑子坐标串，goban 二字码，9x9 窗口内
    white: bgchcf
    mark: triangle:bgd      # 可选，多行；键=标记形状，值=坐标串
    correct: bg | dg | ch   # 仅 puzzle；| 分隔的多条正解路径
    question: ...           # 仅 multipleChoice
    options: 3 / 4 / 5      # 仅 multipleChoice
    answer: 2               # 仅 multipleChoice，1 起算
    interaction: pass       # 仅 endingGame：pass | stoneRemoval | finish
    targets: bgbh           # 仅 stoneRemoval
    instruction: ...

本文件由 extract_levels.mjs 生成后**手工不可再改坐标**（改了规则校验就失效）；
文本层面的修订允许，但必须重跑 gen_content.py 让 C 表跟上。

版式上限的由来（240x320 屏，正文可用宽 210px，与 qiaopi 同一块屏）：

    字号   字宽   每行字数   行高
    32px   32      6         38
    24px   24      8         29
    16px   16      13        20

题面页（BRIEF）是唯一可滚动页面，文本按「行数」校验由宿主测试兜底；这里守门的
是各页一屏内**必须**放下的部分：标题（顶栏）、选项（作答页 24px 一行）、
棋面（点数与标记数上限）。

坐标一律是 9x9 窗口内的 goban 二字码（aa 左上 .. ii 右下），在解析阶段就转成
点下标 y*9+x 并做范围检查 —— 格式错误在这里炸，不流到设备。
"""
from __future__ import annotations

import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_LEVELS_PATH = ROOT / "tools" / "weiqi" / "levels.txt"

BOARD = 9
BOARD_POINTS = BOARD * BOARD
BOARD_LETTERS = "abcdefghi"

KINDS = ("puzzle", "multipleChoice", "endingGame")
INTERACTIONS = ("pass", "stoneRemoval", "finish")
# 标记形状白名单：设备渲染器只认这些键。字母与数字键（A..Z / 1..12）以正则放行。
MARK_SHAPE_FIXED = ("triangle", "square", "circle", "cross")
MARK_SHAPE_LABEL = re.compile(r"^([A-Z]|[0-9]{1,2})$")

# ---- 设备版式上限（与 main/wq_ui.c 的 _Static_assert 互为镜像）----
TITLE_MAX_CHARS = 13        # 16px 顶栏，与章节进度同一行
INSTRUCTION_MAX_CHARS = 240 # 题面页 16px 可滚动（约 19 行），宿主测试按真实数据断言行数
QUESTION_MAX_CHARS = 190    # 选择题题干，同题面页
OPTION_TEXT_MAX_CHARS = 10  # 24px 选项行，含「甲乙丙」标签后一行放得下

CORRECT_PATHS_MAX = 6
CORRECT_MOVES_MAX = 24
MARKS_MAX = 12
STONES_MAX = 64
OPTIONS_MAX = 4

CHAPTERS = (
    ("fundamentals", "青铜 · 入门启蒙"),
    ("basic-principles", "白银 · 气与提子"),
    ("basic-skills", "黄金 · 吃子手筋"),
    ("beginner-level1", "铂金 · 死活初步"),
    ("beginner-level2", "钻石 · 眼位棋形"),
    ("beginner-level3", "星耀 · 劫与收官"),
    ("beginner-level4", "王者 · 高阶战术"),
)
CHAPTER_IDS = tuple(name for name, _ in CHAPTERS)

STARS_POINTS = 100  # 每星 100 分，与网页版 pointsForStars 一致

# 标记渲染字符：形状标记在设备上用这些字形画（gen_font 把它们强制进字库）。
MARK_GLYPHS = {"triangle": "▲", "square": "□", "circle": "○", "cross": "×"}


class ContentError(Exception):
    """关卡源文件不合法。生成器应当据此失败，而不是发出一个有缺陷的表。"""


def _decode_coords(text: str, where: str) -> list[int]:
    """goban 二字码串 -> 点下标列表。任何越界/奇数字符数都直接报错。"""
    if len(text) % 2 != 0:
        raise ContentError(f"{where}: 坐标串长度不是偶数：{text!r}")
    points = []
    for i in range(0, len(text), 2):
        x = ord(text[i]) - ord("a")
        y = ord(text[i + 1]) - ord("a")
        if not (0 <= x < BOARD and 0 <= y < BOARD):
            raise ContentError(
                f"{where}: 坐标 {text[i:i + 2]!r} 超出 {BOARD}x{BOARD} 窗口")
        points.append(y * BOARD + x)
    return points


class Level:
    """一关，字段名与 levels.txt 的键一一对应。"""

    __slots__ = (
        "lid", "source_id", "chapter", "kind", "title", "player",
        "black", "white", "marks", "correct", "question", "options",
        "answer", "interaction", "targets", "instruction",
    )

    def __init__(self, lid: str, source_id: str) -> None:
        self.lid = lid                # 设备序号，如 "001"
        self.source_id = source_id    # 网页版原 id，用于追溯
        self.chapter = ""
        self.kind = ""
        self.title = ""
        self.player = "black"
        self.black: list[int] = []
        self.white: list[int] = []
        self.marks: list[tuple[str, list[int]]] = []
        self.correct: list[list[int]] = []
        self.question = ""
        self.options: list[str] = []
        self.answer = -1
        self.interaction = ""
        self.targets: list[int] = []
        self.instruction = ""

    @property
    def chapter_index(self) -> int:
        return CHAPTER_IDS.index(self.chapter)

    @property
    def is_ending_removal(self) -> bool:
        return self.kind == "endingGame" and self.interaction == "stoneRemoval"

    def stone_points(self) -> list[tuple[int, int]]:
        """(点, 颜色) 列表，颜色 1=黑 2=白，黑在前。"""
        return [(p, 1) for p in self.black] + [(p, 2) for p in self.white]


def load_levels(path: Path | None = None) -> list[Level]:
    """读取并严格解析关卡源文件。任何格式问题都直接报错，不猜。"""
    levels_path = Path(path) if path else DEFAULT_LEVELS_PATH
    if not levels_path.is_file():
        raise ContentError(f"找不到关卡源文件：{levels_path}")

    levels: list[Level] = []
    current: dict[str, list[str]] | None = None
    current_id = ""

    def flush() -> None:
        nonlocal current, current_id
        if current is None:
            return
        head = current_id.split(None, 1)
        if len(head) != 2:
            raise ContentError(f"{current_id or '<无 id>'}: 区块头应是 '== <序号> <源id>'")
        lid, source_id = head[0], head[1]
        level = Level(lid, source_id)
        _fill(level, current, current_id)
        levels.append(level)
        current = None
        current_id = ""

    for lineno, raw in enumerate(
            levels_path.read_text(encoding="utf-8").splitlines(), start=1):
        if raw.startswith("#"):
            continue
        if not raw.strip():
            flush()
            continue

        if raw.startswith("== "):
            flush()
            current_id = raw[3:].strip()
            current = {}
            continue

        if current is None:
            raise ContentError(
                f"{levels_path.name}:{lineno}: 字段出现在任何 \"== <id>\" 区块之外：{raw[:40]!r}")
        key, sep, value = raw.partition(":")
        if not sep:
            raise ContentError(
                f"{levels_path.name}:{lineno}: 不是 key: value 形式：{raw[:40]!r}")
        key = key.strip()
        value = value[1:] if value.startswith(" ") else value
        current.setdefault(key, []).append(value)

    flush()

    if not levels:
        raise ContentError(f"关卡源文件里一关都没有：{levels_path}")
    return levels


def _fill(level: Level, fields: dict[str, list[str]], where: str) -> None:
    def one(key: str) -> str:
        values = fields.get(key)
        if not values:
            raise ContentError(f"{where}: 缺少字段 {key}")
        if len(values) > 1:
            raise ContentError(f"{where}: 字段 {key} 出现 {len(values)} 次")
        return values[0]

    level.chapter = one("chapter")
    level.kind = one("kind")
    level.title = one("title")
    level.instruction = one("instruction")

    if level.chapter not in CHAPTER_IDS:
        raise ContentError(f"{where}: 未知章节 {level.chapter!r}")
    if level.kind not in KINDS:
        raise ContentError(f"{where}: 未知题型 {level.kind!r}")
    if len(level.title) > TITLE_MAX_CHARS:
        raise ContentError(
            f"{where}: 标题长 {len(level.title)} 字，超出上限 {TITLE_MAX_CHARS}")
    if len(level.instruction) > INSTRUCTION_MAX_CHARS:
        raise ContentError(
            f"{where}: 说明长 {len(level.instruction)} 字，超出上限 {INSTRUCTION_MAX_CHARS}")

    level.black = _decode_coords(one("black"), f"{where}: black")
    level.white = _decode_coords(one("white"), f"{where}: white")
    # 同色串里的重复点按集合语义去重（网页源数据偶发，goban 也这样容忍）；
    # 跨色重叠才是真矛盾，响亮报错。
    level.black = list(dict.fromkeys(level.black))
    level.white = list(dict.fromkeys(level.white))
    overlap = set(level.black) & set(level.white)
    if overlap:
        raise ContentError(f"{where}: 黑白子坐标重叠：{sorted(overlap)}")
    if len(level.black) + len(level.white) > STONES_MAX:
        raise ContentError(
            f"{where}: 棋子 {len(level.black) + len(level.white)} 颗，超出上限 {STONES_MAX}")

    for mark_line in fields.get("mark", []):
        shape, _, coords = mark_line.partition(":")
        if shape not in MARK_SHAPE_FIXED and not MARK_SHAPE_LABEL.match(shape):
            raise ContentError(f"{where}: 未知标记形状 {shape!r}")
        pts = _decode_coords(coords, f"{where}: mark {shape}")
        # 注意：形状标记（三角/方/圆/叉）允许压在棋子上 —— 棋谱术语里「标记之子」
        # 是常规表达；字母/数字标记通常标空点，但压子也照常渲染，不做限制。
        if len(level.marks) + len(pts) > MARKS_MAX:
            raise ContentError(f"{where}: 标记总数超出上限 {MARKS_MAX}")
        level.marks.append((shape, pts))

    if level.kind == "puzzle":
        level.player = one("player")
        if level.player not in ("black", "white"):
            raise ContentError(f"{where}: player 应是 black/white，得到 {level.player!r}")
        for path_text in one("correct").split(" | "):
            moves = _decode_coords(path_text.strip(), f"{where}: correct")
            if not moves:
                raise ContentError(f"{where}: 正解路径为空")
            if len(moves) > CORRECT_MOVES_MAX:
                raise ContentError(
                    f"{where}: 正解路径 {len(moves)} 手，超出上限 {CORRECT_MOVES_MAX}")
            level.correct.append(moves)
        if len(level.correct) > CORRECT_PATHS_MAX:
            raise ContentError(
                f"{where}: 正解路径 {len(level.correct)} 条，超出上限 {CORRECT_PATHS_MAX}")
        return

    if level.kind == "multipleChoice":
        level.question = one("question")
        if len(level.question) > QUESTION_MAX_CHARS:
            raise ContentError(
                f"{where}: 题干长 {len(level.question)} 字，超出上限 {QUESTION_MAX_CHARS}")
        level.options = [piece.strip() for piece in one("options").split(" / ")]
        if not 2 <= len(level.options) <= OPTIONS_MAX:
            raise ContentError(f"{where}: 选项数 {len(level.options)} 不在 2..{OPTIONS_MAX}")
        for option in level.options:
            if not option:
                raise ContentError(f"{where}: 有空选项")
            if len(option) > OPTION_TEXT_MAX_CHARS:
                raise ContentError(
                    f"{where}: 选项 {option!r} 长 {len(option)} 字，超出上限 {OPTION_TEXT_MAX_CHARS}")
        if len(set(level.options)) != len(level.options):
            raise ContentError(f"{where}: 选项重复")
        answer_text = one("answer")
        if not answer_text.isdigit():
            raise ContentError(f"{where}: answer 应是 1 起算的序号，得到 {answer_text!r}")
        level.answer = int(answer_text) - 1
        if not 0 <= level.answer < len(level.options):
            raise ContentError(f"{where}: answer={answer_text} 越界")
        return

    # endingGame
    level.interaction = one("interaction")
    if level.interaction not in INTERACTIONS:
        raise ContentError(f"{where}: 未知终局交互 {level.interaction!r}")
    if level.interaction == "stoneRemoval":
        level.targets = _decode_coords(one("targets"), f"{where}: targets")
        if not level.targets:
            raise ContentError(f"{where}: stoneRemoval 缺少目标子")
        stones = set(level.black) | set(level.white)
        for p in level.targets:
            if p not in stones:
                coord = BOARD_LETTERS[p % BOARD] + BOARD_LETTERS[p // BOARD]
                raise ContentError(f"{where}: 移除目标 {coord} 不在有子点上")


def validate(levels: list[Level]) -> list[str]:
    """返回问题清单（空表示通过）。规则校验与抽取器同源：气 / 提子 / 禁自杀 / 简单劫。

    抽取器已经在**原棋盘**上校验过，但 levels.txt 是独立事实源（人可能改它），
    所以这里对**窗口棋盘**完整重放一遍 —— 校验器和设备 C 引擎是同一套规则的两份
    实现，宿主测试再把两边对拍一次。
    """
    problems: list[str] = []

    def group_liberties(cells: list[int], start: int) -> tuple[list[int], set[int]]:
        color = cells[start]
        stones, stack, seen = [], [start], {start}
        liberties: set[int] = set()
        while stack:
            p = stack.pop()
            stones.append(p)
            x, y = p % BOARD, p // BOARD
            for dx, dy in ((-1, 0), (1, 0), (0, -1), (0, 1)):
                nx, ny = x + dx, y + dy
                if not (0 <= nx < BOARD and 0 <= ny < BOARD):
                    continue
                n = ny * BOARD + nx
                if cells[n] == 0:
                    liberties.add(n)
                elif cells[n] == color and n not in seen:
                    seen.add(n)
                    stack.append(n)
        return stones, liberties

    def simulate(cells: list[int], point: int, color: int, ko: int) -> tuple[list[int], int] | None:
        if cells[point] != 0 or point == ko:
            return None
        nxt = list(cells)
        nxt[point] = color
        opp = 3 - color
        captured = 0
        captured_point = -1
        x, y = point % BOARD, point // BOARD
        for dx, dy in ((-1, 0), (1, 0), (0, -1), (0, 1)):
            nx, ny = x + dx, y + dy
            if not (0 <= nx < BOARD and 0 <= ny < BOARD):
                continue
            n = ny * BOARD + nx
            if nxt[n] != opp:
                continue
            stones, liberties = group_liberties(nxt, n)
            if not liberties:
                for s in stones:
                    nxt[s] = 0
                captured += len(stones)
                if captured_point < 0:
                    captured_point = stones[0]
        stones, liberties = group_liberties(nxt, point)
        if not liberties:
            return None  # 自杀
        ko_next = -1
        if captured == 1 and len(stones) == 1 and len(liberties) == 1:
            ko_next = captured_point
        return nxt, ko_next

    seen_ids: set[str] = set()
    previous_order = 0
    chapter_seen: list[str] = []

    for level in levels:
        where = f"{level.lid}({level.source_id})"

        if not re.fullmatch(r"\d{3}", level.lid):
            problems.append(f"{where}: 序号应是三位数字")
        lid_number = int(level.lid)
        if lid_number != previous_order + 1:
            problems.append(f"{where}: 序号不连续（前一个是 {previous_order:03d}）")
        previous_order = lid_number
        if level.lid in seen_ids:
            problems.append(f"{where}: 序号重复")
        seen_ids.add(level.lid)

        if not chapter_seen or chapter_seen[-1] != level.chapter:
            if level.chapter in chapter_seen:
                problems.append(f"{where}: 章节 {level.chapter} 在中间重新出现")
            chapter_seen.append(level.chapter)

        occupied = set(level.black) | set(level.white)
        if level.kind == "puzzle":
            color_of = level.player
            cells = [0] * BOARD_POINTS
            for p in level.black:
                cells[p] = 1
            for p in level.white:
                cells[p] = 2
            for path in level.correct:
                board = list(cells)
                ko = -1
                for i, move in enumerate(path):
                    color = 1 if (i % 2 == 0) == (color_of == "black") else 2
                    nxt = simulate(board, move, color, ko)
                    if nxt is None:
                        why = "占位" if board[move] != 0 else ("劫争" if move == ko else "自杀")
                        coord = (BOARD_LETTERS[move % BOARD] +
                                 BOARD_LETTERS[move // BOARD])
                        problems.append(f"{where}: 正解第 {i + 1} 手 {coord} 非法（{why}）")
                        break
                    board, ko = nxt
            # 注意不查「路径内落点重复」：提子之后同一点可以再落，劫争与杀气
            # 教学正是如此（ko-5 整关在教这个）。真正的约束是模拟时的占位检查。
            # 标记点重复标注
            mark_points: set[int] = set()
            for _, pts in level.marks:
                for p in pts:
                    if p in mark_points:
                        problems.append(f"{where}: 标记点 {p} 重复标注")
                    mark_points.add(p)
        elif level.kind == "multipleChoice":
            del occupied
        else:
            del occupied

    return problems


def content_characters(levels: list[Level]) -> set[str]:
    """内容里出现过的所有字符，用于字库清单。

    字库清单 = 本函数的结果 + 界面字符串（后者由 gen_font.py 扫 ``main/*.c|*.h``
    得到）+ 标记渲染字形（▲□○✕，只要内容里出现过对应形状就带上）。
    """
    chars: set[str] = set()
    for level in levels:
        chars.update(level.title)
        chars.update(level.instruction)
        if level.kind == "multipleChoice":
            chars.update(level.question)
            for option in level.options:
                chars.update(option)
        shapes = {shape for shape, _ in level.marks}
        for shape in shapes:
            chars.update(MARK_GLYPHS.get(shape, ""))
            if shape in MARK_GLYPHS:
                continue
            chars.update(shape)  # 字母 / 数字标记按字面渲染
    # 章节/评级文案属于内容，不是界面常量。
    for _, subtitle in CHAPTERS:
        chars.update(subtitle)
    return {c for c in chars if not c.isspace()}


def chapter_bounds(levels: list[Level]) -> list[tuple[int, int, int]]:
    """返回每章 (章节下标, 起始关卡下标, 关卡数)，按 levels.txt 顺序聚合。"""
    bounds: list[tuple[int, int, int]] = []
    for index, level in enumerate(levels):
        ci = level.chapter_index
        if bounds and bounds[-1][0] == ci:
            bounds[-1] = (ci, bounds[-1][1], bounds[-1][2] + 1)
        else:
            bounds.append((ci, index, 1))
    return bounds
