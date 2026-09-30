// tests/test_wq_content.c —— 生成的关卡 C 表的健全性。
//
// gen_content.py 已经在生成时校验过一遍；这里用 C 再查一遍「表与头文件声明
// 一致、下标全部在界内、字段按题型齐备」。它防的是两类事故：生成器改了但
// 头文件没跟上，以及有人在 C 里手改了生成物。
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "wq_engine.h"  /* WQ_COLOR_* 也来自这里 */

static void test_counts(void)
{
    assert(WQ_LEVEL_COUNT > 100);
    assert(WQ_CHAPTER_COUNT == 7);
    uint16_t total = 0;
    for (uint8_t ci = 0; ci < WQ_CHAPTER_COUNT; ci++) {
        total = (uint16_t)(total + wq_chapters[ci].count);
        // 章节区间不重叠且连续。
        if (ci > 0) {
            assert(wq_chapters[ci].first ==
                   (uint16_t)(wq_chapters[ci - 1].first + wq_chapters[ci - 1].count));
        }
    }
    assert(total == WQ_LEVEL_COUNT);
    puts("ok  章节分段连续且恰好覆盖全部关卡");
}

static void test_every_level_shape(void)
{
    unsigned by_kind[5] = { 0 };
    for (uint16_t li = 0; li < (uint16_t)WQ_LEVEL_COUNT; li++) {
        const wq_level_t *level = &wq_levels[li];
        assert(level->title[0] != '\0');
        assert(level->instruction[0] != '\0');
        assert(level->kind <= WQ_KIND_END_FINISH);
        by_kind[level->kind]++;

        // 棋子在界内且颜色合法。
        assert(level->stone_count <= WQ_STONES_MAX);
        for (uint8_t si = 0; si < level->stone_count; si++) {
            assert(level->stones[si * 2] < WQ_BOARD_POINTS);
            const uint8_t color = level->stones[si * 2 + 1];
            assert(color == WQ_COLOR_BLACK || color == WQ_COLOR_WHITE);
        }
        // 标记与字形一一对应。
        for (uint8_t mi = 0; mi < level->mark_count; mi++) {
            assert(level->mark_points[mi] < WQ_BOARD_POINTS);
            assert(level->mark_glyphs[mi][0] != '\0');
        }

        switch (level->kind) {
            case WQ_KIND_PUZZLE:
                assert(level->correct_count >= 1 && level->correct_count <= WQ_CORRECT_PATHS_MAX);
                assert(level->player == WQ_COLOR_BLACK || level->player == WQ_COLOR_WHITE);
                for (uint8_t pi = 0; pi < level->correct_count; pi++) {
                    assert(level->correct[pi].len >= 1);
                    assert(level->correct[pi].len <= WQ_CORRECT_MOVES_MAX);
                    for (uint8_t mi = 0; mi < level->correct[pi].len; mi++) {
                        assert(level->correct[pi].moves[mi] < WQ_BOARD_POINTS);
                    }
                }
                break;
            case WQ_KIND_CHOICE:
                assert(level->option_count >= 2 && level->option_count <= WQ_OPTIONS_MAX);
                assert(level->answer < level->option_count);
                for (uint8_t oi = 0; oi < level->option_count; oi++) {
                    assert(level->options[oi][0] != '\0');
                }
                break;
            case WQ_KIND_END_REMOVE:
                assert(level->target_count >= 1 && level->target_count <= WQ_REMOVAL_MAX);
                for (uint8_t ti = 0; ti < level->target_count; ti++) {
                    assert(level->targets[ti] < WQ_BOARD_POINTS);
                }
                break;
            case WQ_KIND_END_PASS:
            case WQ_KIND_END_FINISH:
                break;
            default:
                assert(0);
        }
    }
    assert(by_kind[WQ_KIND_PUZZLE] > 100);
    assert(by_kind[WQ_KIND_CHOICE] > 20);
    assert(by_kind[WQ_KIND_END_PASS] + by_kind[WQ_KIND_END_REMOVE] +
               by_kind[WQ_KIND_END_FINISH] ==
           3);
    printf("ok  全部 %u 关字段齐备（puzzle %u / choice %u / 终局 %u）\n",
           (unsigned)WQ_LEVEL_COUNT, by_kind[WQ_KIND_PUZZLE],
           by_kind[WQ_KIND_CHOICE],
           by_kind[WQ_KIND_END_PASS] + by_kind[WQ_KIND_END_REMOVE] +
               by_kind[WQ_KIND_END_FINISH]);
}

static void test_chapter_titles_are_content(void)
{
    // 章节名进入字库清单（content_characters），这里确认它们确实非空且带段位词。
    static const char *const RANKS[] = { "青铜", "白银", "黄金", "铂金", "钻石", "星耀", "王者" };
    for (uint8_t ci = 0; ci < WQ_CHAPTER_COUNT; ci++) {
        assert(strstr(wq_chapters[ci].title, RANKS[ci]) == wq_chapters[ci].title);
    }
    puts("ok  七章标题按青铜..王者排列");
}

int main(void)
{
    test_counts();
    test_every_level_shape();
    test_chapter_titles_are_content();
    puts("test_wq_content: PASS");
    return 0;
}
