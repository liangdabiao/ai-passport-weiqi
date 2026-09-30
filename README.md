<p align="right">
  <a href="README.zh_CN.md">简体中文</a> · <strong>English</strong>
</p>

# Weiqi Quest — the Go ladder on a three-key handheld

An offline Go (weiqi) puzzle ladder for a three-button handheld: **154 levels across 7 chapters**,
from the first liberty to capturing races, endgame procedure and ko fights. Every board, every
solution path and every quiz question lives inside the device: **no network, no card, no phone**.

The levels are adapted from the web game *Go Quest Ladder*, which was itself extracted
from the LearningHub tutorial on online-go.com — a fork of that game supplied the level data, and
the on-device version keeps its chapter ladder and star ratings.

| Title | World map | Playing | Result |
| --- | --- | --- | --- |
| A large title, three entries — Continue, Volume, Reset record — and a progress line. | Seven chapters from Bronze to King, each with its cleared count. | A 9x9 board with a gold cursor; instructions and candidates above it. | Stars, points and the mistake count; "next level" one press away. |

## How a run goes

| Page | What is on screen | The three keys |
| --- | --- | --- |
| **Title** | A large title, three entries — Continue, Volume, Reset record — and a line such as "cleared 12/154 · ★30" | UP/DOWN to choose, OK to enter. On Volume, OK cycles six steps (off, then 20% up to 100%). Reset record takes **two presses of OK** |
| **World map** | Seven chapters, all open; the selected chapter shows its progress in the hint bar | UP/DOWN to choose, OK to enter a chapter, long-press OK to return |
| **Level list** | Five rows per screen: number, short title (the web game's " · x/N" suffix is stripped), stars earned | UP/DOWN to move, OK to enter any level, long-press OK to return to the map |
| **Brief** | The level's instruction (scrollable), or the board plus question for quiz levels | UP/DOWN to scroll, OK to start, long-press OK to return |
| **Playing** | A 9x9 board, a gold cursor, a status line | Short UP/DOWN move a row, double-click UP/DOWN moves a column, OK places (or confirms / removes dead stones), long-OK goes back to the brief |
| **Result** | Three stars at best, points (100 per star), mistakes | OK for the next level, long-OK back to the list |

Judging matches the web game: a move must extend one of the level's scripted solution paths; a
legal move that fits no path costs one mistake and resets the board. Zero mistakes earn three
stars, one mistake earns two, anything worse earns one. The full Go rules (liberties, captures,
suicide, simple ko) run on the device.

## What is inside

- **154 levels**: 119 board puzzles, 32 quiz questions and 3 endgame-teaching levels, grouped into
  Bronze → Silver → Gold → Platinum → Diamond → Star → King. Every 19x19 position from the web
  game was cropped into a 9x9 window by its bounding box, and every solution path was re-validated
  under the full rules on the cropped board — 94% of the original positions fit.
- **A pure-logic core**: the rules engine, the progression state machine, the progress store and
  the text wrapper compile on the host, so `tools/validate.sh` plays **every level to the end**
  and replays every solution path before anything is flashed.
- **No audio assets**: effects are square-wave RTTTL synthesized on the fly. The web game's 2.8 MB
  background music was deliberately dropped.
- **A 603-codepoint font subset** in three sizes (16/24/32 px), generated from Noto Sans CJK SC
  by `tools/weiqi/gen_font.py`.

## Build

This is an [ESP-IDF](https://github.com/espressif/esp-idf) 5.5.3 project for the FoloToy AI
Passport board (ESP32-C3, 240x320 ST7789, three-key ADC input).

```bash
idf.py build            # firmware
idf.py flash monitor    # onto the device
./tools/validate.sh     # repository gate: docs, generated tables, host tests, firmware
```

## Documentation

- [`docs/README.md`](docs/README.md) — documentation index and the conventions every page follows.
- [`docs/reference/liangdabiao/weiqi-quest/README.md`](docs/reference/liangdabiao/weiqi-quest/README.md)
  — the full application record: the 9x9 cropping rule, the level pipeline, the two-dimensional
  cursor on three keys, the deliberate differences from the web version, and the verification log.
- [`AGENTS.md`](AGENTS.md) — repository rules for contributors and agents.
- [`assets/README.md`](assets/README.md) — the fonts this game ships, with sources and licences.

## Origins and licences

- Level data derives from the LearningHub tutorial of [online-go.com](https://online-go.com),
  extracted by the AGPL-3.0 web game the level pipeline reads; the extraction and its provenance
  are documented in `tools/weiqi/levels.txt` and the application record. **The level content is
  therefore distributed under AGPL-3.0**; the surrounding firmware keeps the repository's MIT
  licence (see [`LICENSE`](LICENSE)).
- This repository is the fourth sibling of the family: the **Three Character Classic kids game**
  (`ai-passport`), the **Daodejing daily reader** (`daodejing-daily`), the **Qiaopi quiz**
  (`qiaopi-quiz`) and now the **Weiqi quest** — one set of repository conventions, one toolchain,
  one verification gate.
