// tests/test_wq_volume.c —— 音量档位表与缩放算术。
//
// 钉住两句话：默认档位存在档位表里、缩放是 base * level / 100 的整数截断。
// 本应用只有一路音效（基准 58，与 rtttl_player 出厂值一致），所以「关档归零」
// 与「档位循环」是这里最要紧的行为。
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "wq_volume.h"

static void test_steps_and_default(void)
{
    // 档位表：关、20、40、60、80、100；默认档必须真的在表里。
    assert(wq_volume_steps[0] == WQ_VOLUME_OFF);
    assert(wq_volume_steps[WQ_VOLUME_STEP_COUNT - 1] == WQ_VOLUME_MAX);
    bool default_in_table = false;
    for (int i = 0; i < WQ_VOLUME_STEP_COUNT; i++) {
        if (wq_volume_steps[i] == WQ_VOLUME_DEFAULT) default_in_table = true;
    }
    assert(default_in_table);
    puts("ok  档位表含关与满档，默认档在表内");
}

static void test_scale_arithmetic(void)
{
    // 整数截断：58 x 80% = 46.4 -> 46。
    assert(wq_volume_scale(WQ_VOLUME_BASE_SFX, WQ_VOLUME_DEFAULT) == 46);
    assert(wq_volume_scale(WQ_VOLUME_BASE_SFX, WQ_VOLUME_MAX) == WQ_VOLUME_BASE_SFX);
    assert(wq_volume_scale(WQ_VOLUME_BASE_SFX, WQ_VOLUME_OFF) == 0);
    // 任意 base 在 0 档都归零。
    for (int base = 0; base <= 100; base++) {
        assert(wq_volume_scale((uint8_t)base, WQ_VOLUME_OFF) == 0);
    }
    puts("ok  缩放算术：58 x 80% = 46，0 档全归零");
}

static void test_cycle_wraps_to_off(void)
{
    // 从默认档向上走两步到顶，再走一步回关 —— 循环而非卡死。
    uint8_t level = WQ_VOLUME_DEFAULT;
    assert(level == 80);
    level = wq_volume_next(level);
    assert(level == WQ_VOLUME_MAX);
    level = wq_volume_next(level);
    assert(level == WQ_VOLUME_OFF);
    level = wq_volume_next(level);
    assert(level == 20);

    // 不在表里的脏值（旧版本存档）回到关。
    assert(wq_volume_next(55) == WQ_VOLUME_OFF);
    puts("ok  档位循环到顶回关，脏值兜底");
}

static void test_text(void)
{
    char text[16];
    assert(wq_volume_text(WQ_VOLUME_OFF, text, sizeof(text)) == strlen("关"));
    assert(strcmp(text, "关") == 0);
    assert(wq_volume_text(80, text, sizeof(text)) == (uint16_t)strlen("80%"));
    assert(strcmp(text, "80%") == 0);
    assert(wq_volume_text(80, text, 2) == 0); // 容量不足：整体失败
    assert(text[0] == '\0');
    puts("ok  档位文本：关 / 80%，容量不足整体失败");
}

int main(void)
{
    test_steps_and_default();
    test_scale_arithmetic();
    test_cycle_wraps_to_off();
    test_text();
    puts("test_wq_volume: PASS");
    return 0;
}
