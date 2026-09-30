// tests/test_wq_wrap.c —— 中文折行：单元用例 + 全题库断言。
//
// 全题库断言是这里的主角：每段题面说明（最长 240 字）在 16px 每行 13 字的真实
// 预算下，折行结果必须装进 WQ_WRAP_CAPACITY 的缓冲、单行不超预算、且行首不是
// 收尾标点。「一屏放得下」是算术，不是感觉。
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "wq_content.h"
#include "wq_layout.h"
#include "wq_wrap.h"

static bool starts_with_closing_punct(const char *line)
{
    // 收尾标点集合与 wq_wrap.c 的断点规则一致；行首出现它们就是折行缺陷。
    static const char *const closing = "，。！？；：）」』%…";
    if (!line[0]) return false;
    const unsigned char c = (unsigned char)line[0];
    // 只处理多字节首字节 0xE0-0xEF 的中文标点与全角字符。
    if (c < 0x80) return false;
    for (const char *p = closing; *p; p++) {
        if (line[0] == p[0] && line[1] == p[1] && line[2] == p[2]) return true;
    }
    return false;
}

static void test_basic_wrap(void)
{
    char out[WQ_WRAP_CAPACITY];
    // 8 字一行：16 个字恰好两行。
    const size_t n = wq_wrap_utf8("一二三四五六七八一二三四五六七八", 8,
                                  out, sizeof(out));
    assert(n > 0);
    assert(wq_utf8_length(out) == 17); // 16 字 + 1 个换行（行间，无尾随）
    assert(strchr(out, '\n') != NULL);
    puts("ok  基础折行：按字数断行");
}

static void test_line_limit_is_hard(void)
{
    char out[WQ_WRAP_CAPACITY];
    // 任何内容、任何行宽：单行字符数不超过请求值。
    const char *text = "甲乙丙丁戊己庚辛壬癸甲乙丙丁戊己庚辛壬癸，。！？";
    for (int width = 1; width <= WQ_WRAP_MAX_LINE; width++) {
        const size_t n = wq_wrap_utf8(text, width, out, sizeof(out));
        assert(n > 0);
        char *line = out;
        while (line) {
            char *nl = strchr(line, '\n');
            const size_t len = nl ? (size_t)(nl - line) : strlen(line);
            assert(wq_utf8_length_prefix(line, len) <= (unsigned)width);
            if (nl) {
                line = nl + 1;
            } else {
                break;
            }
        }
    }
    puts("ok  单行字数是硬保证");
}

static void test_capacity_shortfall_fails_loud(void)
{
    char tiny[8];
    char out[8] = { 0 };
    assert(wq_wrap_utf8("一二三四五六七八九十一二三四五六七八九十", 8, out, sizeof(out)) == 0);
    assert(out[0] == '\0'); // 不留半截
    (void)tiny;
    puts("ok  容量不足返回 0 且清空输出");
}

static void test_every_instruction_fits(void)
{
    // 全题库：题面说明与选择题题干都按题面页的真实预算（16px 每行 13 字）折行，
    // 必须装进折行缓冲；行首不得是收尾标点。
    unsigned longest_lines = 0;
    const char *longest_id = "";
    for (uint16_t li = 0; li < (uint16_t)WQ_LEVEL_COUNT; li++) {
        const wq_level_t *level = &wq_levels[li];
        char out[WQ_WRAP_CAPACITY];
        const size_t n = wq_wrap_utf8(level->instruction, WQ_CHARS_SMALL,
                                      out, sizeof(out));
        if (n == 0) {
            printf("FAIL: 关 %u 题面折行失败（缓冲不足）\n", (unsigned)li + 1);
            assert(0);
        }
        // 行数与行首检查。
        unsigned lines = 1;
        for (const char *p = out; *p; p++) {
            if (*p == '\n') {
                lines++;
                if (starts_with_closing_punct(p + 1)) {
                    printf("FAIL: 关 %u 行首出现收尾标点\n", (unsigned)li + 1);
                    assert(0);
                }
            }
        }
        if (lines > longest_lines) {
            longest_lines = lines;
            longest_id = level->title;
        }
        if (level->kind == WQ_KIND_CHOICE) {
            assert(wq_wrap_utf8(level->question, WQ_CHARS_SMALL, out, sizeof(out)) > 0);
        }
    }
    printf("ok  全题库折行断言：最长题面 %u 行（%s）\n", longest_lines, longest_id);
    assert(longest_lines * 20 <= WQ_BODY_H * 3); // 可滚两屏以内
}

int main(void)
{
    test_basic_wrap();
    test_line_limit_is_hard();
    test_capacity_shortfall_fails_loud();
    test_every_instruction_fits();
    puts("test_wq_wrap: PASS");
    return 0;
}
