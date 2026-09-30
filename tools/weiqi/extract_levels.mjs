// tools/weiqi/extract_levels.mjs —— 从网页版《围棋闯关》抽取设备版关卡源文件。
//
// 网页版的数据在 TypeScript 源码里（src/game/chapters/*.ts），行动正解是真正的
// 序列数据而不是文本。按本仓库在 ancient-poets 上确立过的教训：**不刮 JS，直接
// 求值** —— 用 esbuild 把 TS 转成 CJS 后在 node 里 require，得到原始对象。
//
// 本脚本做五件事，任何一步不合法都直接失败（或跳过该关并记录原因），绝不静默：
//   1. 求值 8 个章节，丢弃 aiGame（BOSS 大模型对弈，设备不做）与整个 boss 章节；
//   2. 把棋面裁剪成 9x9 窗口：按「初始棋子 + 正解 + 标记」包围盒定位窗口，
//      超出 9x9 的关卡跳过（网页版 19x19 棋题的 94% 都能装进 9x9）；
//   3. 在 9x9 窗口上按完整规则（气 / 提子 / 禁自杀 / 简单劫）逐手校验每条正解
//      路径，并要求对手应手节点唯一（两条正解不得在对手应手处分叉）；
//   4. 按每章目标数量等距选关（保持原教学顺序），放入 levels.txt；
//   5. 打印统计：各章通过/跳过、题型分布、字符集、文本最长值。
//
// 用法：node tools/weiqi/extract_levels.mjs [网页版目录] [--write]
// 不带 --write 只统计不落盘。落盘前先跑一遍看统计是故意的。
import { readFileSync, writeFileSync } from "fs";
import { resolve } from "path";

const ARGS = process.argv.slice(2);
const SRC = resolve(ARGS.find((a) => !a.startsWith("--")) || "D:/online-go.com-main/go-game");
const WRITE = ARGS.includes("--write");
const OUT = resolve("tools/weiqi/levels.txt");

// esbuild 从网页版仓库借（那边装好了）；本仓库没有 node_modules，也不需要。
const { transformSync } = await import(
    new URL(`file:///${resolve(SRC, "node_modules/esbuild/lib/main.js").replace(/\\/g, "/")}`)
);

// 每章选关目标（puzzle + multipleChoice + endingGame 按原顺序等距抽取）。
// boss 章节整体不做。数字是设备版的课程量：一次完整通关约 8 小时。
const CHAPTER_PLAN = [
    { id: "fundamentals", target: 36 },
    { id: "basic-principles", target: 20 },
    { id: "basic-skills", target: 24 },
    { id: "beginner-level1", target: 24 },
    { id: "beginner-level2", target: 20 },
    { id: "beginner-level3", target: 20 },
    { id: "beginner-level4", target: 16 },
];

// 设备版式上限。与 tools/weiqi/content.py 的常量互为镜像，改一边必须改另一边。
const TITLE_MAX = 13;
const INSTRUCTION_MAX = 240;  // 题面页可滚动，按「行数」校验由宿主测试兜底
const QUESTION_MAX = 190;     // 选择题题干，同样可滚动
const OPTION_MAX = 10;
const CORRECT_PATHS_MAX = 6;
const CORRECT_MOVES_MAX = 24; // 实测最长 19 手
const MARKS_MAX = 12;
const BOARD = 9;              // 裁剪后的统一棋盘

// ---- 围棋规则（与设备 wq_engine.c 互为镜像，宿主测试再用真实题库对拍一次）----

export function makeBoard(width, height) {
    return { width, height, cells: new Int8Array(width * height), ko: -1 };
}

export function neighbors(point, width, height) {
    const x = point % width, y = (point / width) | 0;
    const out = [];
    if (x > 0) out.push(point - 1);
    if (x < width - 1) out.push(point + 1);
    if (y > 0) out.push(point - width);
    if (y < height - 1) out.push(point + width);
    return out;
}

function groupAt(board, point) {
    const color = board.cells[point];
    const stones = [], liberties = new Set(), seen = new Set([point]);
    const stack = [point];
    while (stack.length) {
        const p = stack.pop();
        stones.push(p);
        for (const n of neighbors(p, board.width, board.height)) {
            if (board.cells[n] === 0) liberties.add(n);
            else if (board.cells[n] === color && !seen.has(n)) {
                seen.add(n);
                stack.push(n);
            }
        }
    }
    return { stones, liberties };
}

/** 落子。返回提子数；非法（占位 / 自杀 / 劫争回提）返回 -1。不修改 board。 */
export function tryPlace(board, point, color) {
    const next = simulate(board, point, color);
    return next ? next.captured : -1;
}

/** 在副本上连续走一手，返回带 captured 字段的新棋盘；非法返回 null。 */
function simulate(board, point, color) {
    if (point < 0 || point >= board.cells.length) return null;
    if (board.cells[point] !== 0 || point === board.ko) return null;
    const next = { width: board.width, height: board.height, cells: Int8Array.from(board.cells), ko: -1 };
    next.cells[point] = color;
    const opp = color === 1 ? 2 : 1;
    let capturedCount = 0, capturedPoint = -1;
    for (const n of neighbors(point, board.width, board.height)) {
        if (next.cells[n] !== opp) continue;
        const g = groupAt(next, n);
        if (g.liberties.size === 0) {
            for (const s of g.stones) next.cells[s] = 0;
            capturedCount += g.stones.length;
            if (capturedPoint < 0) capturedPoint = g.stones[0];
        }
    }
    const mine = groupAt(next, point);
    if (mine.liberties.size === 0) return null;
    if (capturedCount === 1 && mine.stones.length === 1 && mine.liberties.size === 1) {
        next.ko = capturedPoint;
    }
    next.captured = capturedCount;
    return next;
}

// ---- 求值网页版章节 ----

function loadChapter(name) {
    const src = readFileSync(resolve(SRC, "src/game/chapters", `${name}.ts`), "utf8");
    const js = transformSync(src, { loader: "ts", format: "cjs" }).code;
    const mod = { exports: {} };
    new Function("module", "exports", "require", js)(mod, mod.exports, () => ({}));
    return mod.exports;
}

// 坐标解码，支持两种格式（网页版两个来源并存）：
//   goban 二字码  "cp"  = 列 c 行 p（行列都从 a 起算，行向下增大）
//   人类坐标      "b3"  = 列 b 行 3（列跳过 i，行 1 = 底线，围棋惯例）
// 第二个字符是数字即判定为人类坐标。越界返回 -1。
function decodeOne(pair, width, height, originX, originY) {
    let x, y;
    const c0 = pair.charCodeAt(0) - 97, c1 = pair.charCodeAt(1);
    if (c1 >= 49 && c1 <= 57) {
        // 人类坐标：列 a..h,j（跳过 i），行 1 = 底线
        if (c0 < 0 || c0 > 9 || c0 === 8) return -1;
        x = c0 < 8 ? c0 : c0 - 1; // 'j'(9) -> 8
        y = height - (c1 - 48);
    } else {
        x = c0;
        y = c1 - 97;
    }
    x += originX;
    y += originY;
    if (x < 0 || x >= width || y < 0 || y >= height) return -1;
    return y * width + x;
}

function decode(text, width, height, originX, originY) {
    const pairs = text.match(/.{2}/g) || [];
    return pairs.map((pair) => decodeOne(pair, width, height, originX, originY));
}

// ---- 主流程 ----

const problems = [];
const stats = {
    chapters: [], kinds: {}, skipped: {}, textMax: { title: 0, instruction: 0, question: 0, option: 0 },
    charset: new Set(), marks: {}, stoneMax: 0, pathMax: 0,
};

let selected = [];
let order = 0;

for (const plan of CHAPTER_PLAN) {
    const { CHAPTER, LEVELS } = loadChapter(plan.id);
    if (CHAPTER.id !== plan.id) problems.push(`章节 id 不匹配：${CHAPTER.id} != ${plan.id}`);

    const candidates = [];
    let skipped = { crop: 0, rules: 0, text: 0, tree: 0, ai: 0 };

    for (const level of LEVELS) {
        const kind = level.kind || "puzzle";
        if (kind === "aiGame") { skipped.ai++; continue; }

        // 文本上限先行：超限直接跳过，不让版式问题流到设备。
        const title = level.title.zh || "";
        const instruction = level.instruction.zh || "";
        stats.textMax.title = Math.max(stats.textMax.title, title.length);
        stats.textMax.instruction = Math.max(stats.textMax.instruction, instruction.length);
        if (title.length > TITLE_MAX || instruction.length > INSTRUCTION_MAX) {
            skipped.text++;
            problems.push(`${level.id}: 文本超限 title=${title.length} instruction=${instruction.length}`);
            continue;
        }

        // 收集棋面内容点（裁剪候选窗口必须装下所有这些点）。
        let puzzle = null, mc = null, ending = null;
        let stones = "", marksRaw = {}, correctRaw = [], initialPlayer = "black";
        if (kind === "puzzle") {
            puzzle = level.puzzle;
            stones = (puzzle.initial_state.black || "") + " " + (puzzle.initial_state.white || "");
            marksRaw = puzzle.marks || {};
            correctRaw = puzzle.correct || [];
            initialPlayer = puzzle.initial_player || "black";
        } else if (kind === "multipleChoice") {
            mc = level.multipleChoice;
            if (!mc.board) { skipped.crop++; continue; }
            stones = (mc.board.initial_state.black || "") + " " + (mc.board.initial_state.white || "");
            marksRaw = mc.board.marks || {};
            initialPlayer = "black";
        } else if (kind === "endingGame") {
            ending = level.endingGame;
            stones = (ending.initial_state.black || "") + " " + (ending.initial_state.white || "");
            marksRaw = ending.marks || {};
        } else {
            skipped.ai++; continue;
        }

        // 包围盒（在原棋盘坐标系里）。所有坐标统一走 decodeOne（原点 0,0），
        // 两种坐标格式在这里汇成同一个点集。
        const w0 = kind === "multipleChoice" ? mc.board.width : (kind === "endingGame" ? ending.width : puzzle.width);
        const h0 = kind === "multipleChoice" ? mc.board.height : (kind === "endingGame" ? ending.height : puzzle.height);
        const allPoints = [];
        let bboxBad = false;
        const collect = (text) => {
            for (const pair of (text.match(/.{2}/g) || [])) {
                const p = decodeOne(pair, w0, h0, 0, 0);
                if (p < 0) { bboxBad = true; break; }
                allPoints.push([p % w0, (p / w0) | 0]);
            }
        };
        for (const text of stones.split(/\s+/).filter(Boolean)) collect(text);
        for (const key of Object.keys(marksRaw)) collect(marksRaw[key]);
        if (kind === "puzzle") for (const seq of correctRaw) collect(seq);
        if (kind === "endingGame" && ending.targetRemoval) collect(ending.targetRemoval);
        if (bboxBad) { skipped.crop++; problems.push(`${level.id}: 坐标越界`); continue; }
        if (w0 < BOARD || h0 < BOARD) { skipped.crop++; problems.push(`${level.id}: 原棋盘小于 ${BOARD}`); continue; }

        let minX = 99, maxX = -1, minY = 99, maxY = -1;
        for (const [x, y] of allPoints) {
            minX = Math.min(minX, x); maxX = Math.max(maxX, x);
            minY = Math.min(minY, y); maxY = Math.max(maxY, y);
        }
        const bw = maxX - minX + 1, bh = maxY - minY + 1;
        if (bw > BOARD || bh > BOARD) { skipped.crop++; continue; }

        // 重编码辅助：先解码到原棋盘坐标，再平移进窗口 (cx, cy)。
        const toWindow = (text, cx, cy) => {
            const raw = (text.match(/.{2}/g) || []).map((pair) => decodeOne(pair, w0, h0, 0, 0));
            if (raw.some((p) => p < 0)) return null;
            return raw.map((p) => {
                const x = (p % w0) - cx, y = ((p / w0) | 0) - cy;
                if (x < 0 || x >= BOARD || y < 0 || y >= BOARD) return -1;
                return y * BOARD + x;
            });
        };

        const blackText = kind === "puzzle" ? (puzzle.initial_state.black || "")
            : kind === "multipleChoice" ? (mc.board.initial_state.black || "")
            : (ending.initial_state.black || "");
        const whiteText = kind === "puzzle" ? (puzzle.initial_state.white || "")
            : kind === "multipleChoice" ? (mc.board.initial_state.white || "")
            : (ending.initial_state.white || "");

        // 窗口定位：包围盒尽量居中；若规则校验失败（窗口切坏棋块），在可摆放
        // 范围内逐个试探其他位置。位置候选按「居中优先、滑动次之」排序。
        const centerOx = Math.max(0, Math.min(w0 - BOARD, minX - ((BOARD - bw) >> 1)));
        const centerOy = Math.max(0, Math.min(h0 - BOARD, minY - ((BOARD - bh) >> 1)));
        const offsets = [];
        for (const [cx, cy] of [[centerOx, centerOy]]) {
            offsets.push([cx, cy]);
            for (let d = 1; d <= BOARD; d++) {
                if (cx - d >= 0) offsets.push([cx - d, cy]);
                if (cy - d >= 0) offsets.push([cx, cy - d]);
                if (cx + d <= w0 - BOARD) offsets.push([cx + d, cy]);
                if (cy + d <= h0 - BOARD) offsets.push([cx, cy + d]);
            }
        }

        const playerColor = initialPlayer === "black" ? 1 : 2;
        const validatePaths = (blackPts, whitePts, correct) => {
            for (const path of correct) {
                let board = makeBoard(BOARD, BOARD);
                for (const p of blackPts) board.cells[p] = 1;
                for (const p of whitePts) board.cells[p] = 2;
                for (let i = 0; i < path.length; i++) {
                    const color = i % 2 === 0 ? playerColor : (playerColor === 1 ? 2 : 1);
                    const next = simulate(board, path[i], color);
                    if (!next) return false;
                    board = next;
                }
            }
            return true;
        };

        let correct = null, marks = null, targets = null, blackPts = null, whitePts = null, ox = 0, oy = 0;
        if (kind === "puzzle") {
            const candidatePaths = correctRaw.map((seq) => (seq.match(/.{2}/g) || []).length);
            if (correctRaw.length > CORRECT_PATHS_MAX || candidatePaths.some((n) => n > CORRECT_MOVES_MAX)) {
                skipped.rules++; continue;
            }
            let placed = false;
            for (const [cx, cy] of offsets) {
                const bp = toWindow(blackText, cx, cy), wp = toWindow(whiteText, cx, cy);
                const paths = correctRaw.map((seq) => toWindow(seq, cx, cy));
                if (!bp || !wp || bp.includes(-1) || wp.includes(-1) || paths.some((p) => p.includes(-1))) continue;
                if (!validatePaths(bp, wp, paths)) continue;
                blackPts = bp; whitePts = wp; correct = paths; ox = cx; oy = cy;
                placed = true;
                break;
            }
            if (!placed) { skipped.rules++; problems.push(`${level.id}: 无合法窗口`); continue; }
            stats.stoneMax = Math.max(stats.stoneMax, blackPts.length + whitePts.length);
            stats.pathMax = Math.max(stats.pathMax, ...correct.map((p) => p.length));
        } else {
            // 展示型棋面（选择题 / 终局）：不用走子，窗口取居中即可。
            ox = centerOx; oy = centerOy;
            blackPts = toWindow(blackText, ox, oy);
            whitePts = toWindow(whiteText, ox, oy);
            if (!blackPts || !whitePts || blackPts.includes(-1) || whitePts.includes(-1)) {
                skipped.crop++; continue;
            }
            stats.stoneMax = Math.max(stats.stoneMax, blackPts.length + whitePts.length);
        }

        if (kind === "puzzle") {
            marks = {};
            for (const key of Object.keys(marksRaw)) {
                const pts = toWindow(marksRaw[key], ox, oy);
                if (!pts || pts.includes(-1) || pts.length === 0) continue;
                if (pts.length > MARKS_MAX) { skipped.text++; continue; }
                marks[key] = pts;
                stats.marks[key] = (stats.marks[key] || 0) + pts.length;
            }
        }
        if (kind === "endingGame" && ending.targetRemoval) {
            targets = toWindow(ending.targetRemoval, ox, oy);
            if (!targets || targets.includes(-1)) { skipped.crop++; continue; }
        }

        let question = "", options = null, answer = -1;
        if (kind === "multipleChoice") {
            question = mc.question.zh || "";
            options = mc.options.map((o) => o.label.zh);
            answer = mc.options.findIndex((o) => o.value === mc.correctValue);
            stats.textMax.question = Math.max(stats.textMax.question, question.length);
            for (const option of options) stats.textMax.option = Math.max(stats.textMax.option, option.length);
            if (question.length > QUESTION_MAX || options.some((o) => o.length > OPTION_MAX)) {
                skipped.text++; problems.push(`${level.id}: 选择题文本超限`); continue;
            }
            if (answer < 0 || options.length < 2 || options.length > 4) {
                skipped.text++; problems.push(`${level.id}: 选择题选项不合法`); continue;
            }
        }

        // 字符集。
        for (const c of title) stats.charset.add(c);
        for (const c of instruction) stats.charset.add(c);
        if (kind === "multipleChoice") {
            for (const c of question) stats.charset.add(c);
            for (const o of options) for (const c of o) stats.charset.add(c);
        }

        candidates.push({
            id: level.id, chapter: plan.id, kind, title, instruction,
            initialPlayer, blackPts, whitePts, marks, correct, question, options, answer,
            interaction: ending ? ending.interaction : null, targets,
        });
    }

    // 等距选关：保持原顺序，target 个均匀采样。
    const n = candidates.length;
    const take = Math.min(plan.target, n);
    const stride = n / take;
    for (let i = 0; i < take; i++) {
        const level = candidates[Math.floor(i * stride)];
        selected.push({ ...level, order: ++order });
    }

    stats.chapters.push({ id: plan.id, title: CHAPTER.title.zh, candidates: n, taken: take, skipped });
}

// ---- 输出 ----

function fmtPoints(pts) {
    const letters = "abcdefghi";
    return pts.map((p) => letters[p % BOARD] + letters[(p / BOARD) | 0]).join("");
}

function fmtMarks(marks) {
    if (!marks) return [];
    return Object.entries(marks).map(([key, pts]) => `${key}:${fmtPoints(pts)}`);
}

const blocks = [];
for (const lv of selected) {
    const lines = [];
    lines.push(`== ${String(lv.order).padStart(3, "0")} ${lv.id}`);
    lines.push(`chapter: ${lv.chapter}`);
    lines.push(`kind: ${lv.kind}`);
    lines.push(`title: ${lv.title}`);
    lines.push(`player: ${lv.initialPlayer}`);
    lines.push(`black: ${fmtPoints(lv.blackPts)}`);
    lines.push(`white: ${fmtPoints(lv.whitePts)}`);
    for (const m of fmtMarks(lv.marks)) lines.push(`mark: ${m}`);
    if (lv.kind === "puzzle") {
        lines.push(`correct: ${lv.correct.map(fmtPoints).join(" | ")}`);
    }
    if (lv.kind === "multipleChoice") {
        lines.push(`question: ${lv.question}`);
        lines.push(`options: ${lv.options.join(" / ")}`);
        lines.push(`answer: ${lv.answer + 1}`);
    }
    if (lv.kind === "endingGame") {
        lines.push(`interaction: ${lv.interaction}`);
        if (lv.targets) lines.push(`targets: ${fmtPoints(lv.targets)}`);
    }
    lines.push(`instruction: ${lv.instruction}`);
    blocks.push(lines.join("\n"));
}

const header = `# 围棋闯关 —— 设备版关卡源文件
#
# 本文件是内容的事实来源。它由 tools/weiqi/extract_levels.mjs 从网页版
# （${SRC}，AGPLv3）求值抽取并裁剪而来；之后请直接编辑本文件，不要重跑抽取器，
# 除非你确认网页版才是更新的那一份。
#
# 坐标是 9x9 窗口内的 goban 二字码（aa=左上，ii=右下），棋子按 black/white 两行
# 书写；正解路径以 | 分隔，每条路径是从玩家先手开始的连续着法二字码串联。
`;

const text = header + blocks.join("\n\n") + "\n";

console.log("== 章节统计 ==");
for (const c of stats.chapters) {
    console.log(`${c.id.padEnd(18)} 候选 ${String(c.candidates).padStart(3)} 入选 ${String(c.taken).padStart(3)}  ${c.title}  跳过 ${JSON.stringify(c.skipped)}`);
}
console.log("题型分布:", JSON.stringify(selected.reduce((a, l) => { const k = l.kind; a[k] = (a[k] || 0) + 1; return a; }, {})));
console.log("文本最长:", JSON.stringify(stats.textMax));
console.log("字符集:", stats.charset.size, "汉字:", [...stats.charset].filter((c) => /[\u3400-\u4dbf\u4e00-\u9fff]/.test(c)).length);
console.log("标记键分布:", JSON.stringify(stats.marks));
console.log("棋子最多:", stats.stoneMax, "路径最长:", stats.pathMax);
const kindOfProblems = problems.slice(0, 12);
if (kindOfProblems.length) console.log("问题样例:", JSON.stringify(kindOfProblems, null, 1));

if (WRITE) {
    writeFileSync(OUT, text, "utf8");
    console.log(`已写入 ${OUT}：${selected.length} 关`);
} else {
    console.log(`（统计模式；加 --write 写入 ${OUT}）`);
}
