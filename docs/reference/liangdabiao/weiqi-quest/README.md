<p align="right">
  <a href="README.zh_CN.md">简体中文</a> · <strong>English</strong>
</p>

# Weiqi Quest — application record

The fourth app in this repository family, derived from `qiaopi-quiz` with its full git history.
Content source: the web game *Go Quest Ladder*, itself extracted from the
LearningHub tutorial of online-go.com (AGPL-3.0).

## Content model and pipeline

The web game holds 3564 levels in eight chapters of TypeScript data. The device keeps the
chapter ladder but carries a curated subset:

| Decision | Value | Why |
| --- | --- | --- |
| Levels carried | 154 of 3564 (119 puzzle / 32 quiz / 3 endgame) | A complete run is about eight hours; the stride selection keeps the original teaching order inside each chapter |
| Board size | 9x9, always | 80% of the web levels sit on 19x19; the bounding box of stones + solution + marks fits inside 9x9 for **94% of them** (2696/2860). One uniform board size means one renderer and one layout arithmetic |
| AI duel | dropped | The web finale plays against the DeepSeek API; an offline device gets no LLM, and a greedy bot on a 19x19 board is not a game |
| Background music | dropped (2.8 MB) | The user's call: effects are synthesized, audio budget is zero |
| Languages | Chinese only | The device has one speaker of text and a 603-codepoint font budget |

The pipeline lives in `tools/weiqi/`:

1. `extract_levels.mjs` (node) **evaluates** the web game's TypeScript chapters with esbuild —
   the lesson from the previous app applies: solution paths are data, never scrape them with
   regexes. It also handles two coordinate dialects in the source (goban letter pairs `cp` and
   human coordinates `b3` with the *i* column skipped).
2. For every candidate level it computes the bounding box of stones + solution moves + marks,
   slides a 9x9 window over the original board (centre first), and **re-validates every solution
   path under the full rules** (liberties, captures, suicide, simple ko) on the cropped board.
   Cropping can sever a group and change its liberties; those levels are dropped, and the window
   search rescues most others.
3. Accepted levels land in `levels.txt` — the single source of truth, human-readable blocks of
   `key: value` lines. Nothing downstream may invent data.
4. `content.py` re-parses and re-validates the file (the same rules as the extractor, mirrored),
   `gen_content.py` projects it into `main/wq_content.c/h`, and `gen_font.py` unions the
   character inventory with the interface strings into the three font subsets.

Data findings worth keeping: the selected 154 levels use 603 codepoints (361 CJK) — the smallest
font of the family; solution paths average 2.5 moves (max 9 in the selected set); the largest
starting position carries 43 stones.

## The two-dimensional cursor on three keys

The hardest interface problem. A Go board is a grid, the device has UP / DOWN / OK. The chosen
semantics, uniform across every puzzle level:

- **Short UP / DOWN** move the cursor a row (visually up/down).
- **Long UP / DOWN** move it a column (left/right). The BSP reports long presses for every key;
  `main.c` maps them, `main/wq_session.c` consumes them only in solving stages.
- **OK** places a stone (or confirms a quiz answer / removes a dead stone / ends the endgame).
- **Long OK** steps back: solving → brief → level list.

The cursor skips nothing and wraps at nothing: it stops at the edges and ignores illegal drops
(no penalty — matching the web game, where an illegal click simply does not play). On entry it
starts at the first letter-marked point of the level (the instruction's "play at A" point), or
the board centre.

## Deliberate differences from the web version

- **Wrong moves reset the board** and cost one mistake — the web game bumps a React key and
  rebuilds the board; the device replays from the initial position. Judging itself is identical:
  the move must extend one of the scripted solution paths.
- **No opponent AI**: quiz and endgame levels need none; puzzle opponents are scripted inside the
  solution paths (the device plays the reply of the first still-matching path, the same
  branch-order semantics as the web move tree).
- **Chinese only**, dark navy/gold theme straight from the web CSS (`#1a1d2e` / `#f5c451`), with
  a traditional wood-toned board drawn from widgets rather than an image.

## Verification log

`tools/validate.sh` runs, among the family's shared gate:

- `test_wq_engine` — rule unit cases (capture, suicide, snapback, simple ko) plus a **full
  replay of all 134 solution paths / 280 moves** through the C engine;
- `test_wq_session` — **plays all 154 levels to the end** via their solution paths, plus
  wrong-move and wrong-answer penalty cases;
- `test_wq_content` — every generated table row inside its declared bounds;
- `test_wq_wrap` — every instruction and question wraps into the layout buffer at 13 chars/line;
- `test_wq_progress` — star packing, unlock chain, checksum rejection;
- `gen_content.py --check` / `gen_font.py --check` — generated tables and fonts cannot drift
  from `levels.txt` or the interface strings.

Device results are recorded here as they happen.
