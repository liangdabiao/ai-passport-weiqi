// tests/test_wq_progress.c —— 星级存档：打包、只升不降、解锁、序列化往返。
//
// 存档拒绝路径（魔数 / 版本 / 长度 / 校验和）与序列化往返都必须是机器断言：
// 掉电写坏是真实场景，宁可回到空档也不能把半截数据当事实。
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "wq_progress.h"

static void test_pack_roundtrip(void)
{
    wq_progress_t progress;
    wq_progress_reset(&progress);
    wq_progress_set_stars(&progress, 0, 3);
    wq_progress_set_stars(&progress, 4, 1);
    wq_progress_set_stars(&progress, WQ_LEVEL_COUNT - 1, 2);
    assert(wq_progress_stars(&progress, 0) == 3);
    assert(wq_progress_stars(&progress, 1) == 0);
    assert(wq_progress_stars(&progress, 4) == 1);
    assert(wq_progress_stars(&progress, WQ_LEVEL_COUNT - 1) == 2);
    puts("ok  2bit 星级打包读写");
}

static void test_record_only_up(void)
{
    wq_progress_t progress;
    wq_progress_reset(&progress);
    assert(wq_progress_record_result(&progress, 3, 2));
    assert(!wq_progress_record_result(&progress, 3, 1)); // 更差：忽略
    assert(!wq_progress_record_result(&progress, 3, 2)); // 持平：无变化
    assert(wq_progress_record_result(&progress, 3, 3));
    assert(wq_progress_stars(&progress, 3) == 3);
    // 越界关卡不崩、不写。
    assert(!wq_progress_record_result(&progress, WQ_LEVEL_COUNT, 3));
    assert(wq_progress_stars(&progress, WQ_LEVEL_COUNT) == 0);
    puts("ok  星级只升不降，越界安全");
}

static void test_no_locks_anywhere(void)
{
    // 真机反馈：全部解锁，不做锁定。星级只是记录，不是门槛 ——
    // 这里钉住「任何关都可以直接进」这个决定。
    wq_progress_t progress;
    wq_progress_reset(&progress);
    assert(wq_progress_stars(&progress, 40) == 0);
    wq_progress_set_stars(&progress, 40, 2);
    assert(wq_progress_stars(&progress, 40) == 2);
    assert(wq_progress_stars(&progress, 41) == 0); // 后一关不依赖前一关
    puts("ok  无锁定：星级只是记录，关卡之间没有门槛");
}

static void test_summary_counts(void)
{
    wq_progress_t progress;
    wq_progress_reset(&progress);
    wq_progress_set_stars(&progress, 0, 3);
    wq_progress_set_stars(&progress, 1, 1);
    wq_progress_set_stars(&progress, 2, 2);
    assert(wq_progress_cleared_count(&progress) == 3);
    assert(wq_progress_total_stars(&progress) == 6);
    puts("ok  通关数与总星数汇总");
}

static void test_serialize_roundtrip(void)
{
    wq_progress_t progress;
    wq_progress_reset(&progress);
    progress.last_level = 77;
    wq_progress_set_stars(&progress, 5, 3);
    wq_progress_set_stars(&progress, 76, 2);
    wq_progress_set_stars(&progress, WQ_LEVEL_COUNT - 1, 1);

    uint8_t blob[WQ_PROGRESS_BLOB_SIZE];
    assert(wq_progress_serialize(&progress, blob, sizeof(blob)) == WQ_PROGRESS_BLOB_SIZE);

    wq_progress_t loaded;
    assert(wq_progress_deserialize(&loaded, blob, sizeof(blob)) == WQ_PROGRESS_OK);
    assert(loaded.last_level == 77);
    assert(wq_progress_stars(&loaded, 5) == 3);
    assert(wq_progress_stars(&loaded, 76) == 2);
    assert(wq_progress_stars(&loaded, WQ_LEVEL_COUNT - 1) == 1);
    puts("ok  序列化往返逐位一致");
}

static void test_reject_corrupted(void)
{
    wq_progress_t progress;
    wq_progress_reset(&progress);
    wq_progress_set_stars(&progress, 5, 3);
    uint8_t blob[WQ_PROGRESS_BLOB_SIZE];
    assert(wq_progress_serialize(&progress, blob, sizeof(blob)) == WQ_PROGRESS_BLOB_SIZE);

    // 容量不足：拒绝写出半截。
    assert(wq_progress_serialize(&progress, blob, sizeof(blob) - 1) == 0);

    // 长度 / 魔数 / 校验和三类坏档都必须整体拒绝，且不改动调用方结构体。
    wq_progress_t keeper;
    wq_progress_reset(&keeper);

    assert(wq_progress_deserialize(&keeper, blob, sizeof(blob) - 1) ==
           WQ_PROGRESS_ERR_LENGTH);

    uint8_t bad[WQ_PROGRESS_BLOB_SIZE];
    memcpy(bad, blob, sizeof(bad));
    bad[0] ^= 0xFF;
    assert(wq_progress_deserialize(&keeper, bad, sizeof(bad)) == WQ_PROGRESS_ERR_MAGIC);

    memcpy(bad, blob, sizeof(bad));
    bad[WQ_PROGRESS_BLOB_SIZE - 1] ^= 0x01; // 打坏校验和
    assert(wq_progress_deserialize(&keeper, bad, sizeof(bad)) ==
           WQ_PROGRESS_ERR_CHECKSUM);
    // 失败路径不留半截状态。
    assert(wq_progress_cleared_count(&keeper) == 0);
    puts("ok  坏档整体拒绝且不写半截状态");
}

int main(void)
{
    test_pack_roundtrip();
    test_record_only_up();
    test_no_locks_anywhere();
    test_summary_counts();
    test_serialize_roundtrip();
    test_reject_corrupted();
    puts("test_wq_progress: PASS");
    return 0;
}
