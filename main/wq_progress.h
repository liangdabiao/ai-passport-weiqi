// main/wq_progress.h —— 跨局存档：每关星级与最近进度。
//
// 内容（关卡、棋面、题干）是固定的，值得留下来的只有「闯到哪了、各关拿了几星」。
// 这一版存档做两件事：
//
//   1. 每关星级 0..3（0 = 未通关）。真机反馈：全部解锁、不做锁定 —— 想练
//      哪关就进哪关，星级只做记录不做门槛。
//   2. 记录最近进入的关卡，标题页「继续闯关」直接跳过去。
//
// 存档格式刻意严格：魔数 + 版本 + 校验和，任何一项不符就整体拒绝并回到空档，
// 而不是试图「修一修接着用」。NVS 掉电写坏是真实存在的，宁可丢一次星级，
// 也不要把半截数据当成事实读进来 —— 取舍与拒绝路径都有宿主测试。
//
// 星级按 2bit 打包：WQ_LEVEL_COUNT 关 <= 40 字节，整份存档几十字节，
// 一次 NVS 写入毫无压力。不依赖 ESP-IDF 与 LVGL；NVS 读写由 main/wq_store.c 承担。
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "wq_content.h"

#define WQ_PROGRESS_MAGIC 0x57485131u   // "WQH1" —— WQ(围棋) 起头，避开 QPQ/DDJ
#define WQ_PROGRESS_VERSION 1u

// 每关 2bit 星级需要的字节数。
#define WQ_STARS_BYTES ((WQ_LEVEL_COUNT + 3u) / 4u)

// 头部：魔数 4 + 版本 2 + 预留 2 + 最近关卡 2 = 10 字节；
// 随后是星级位图 WQ_STARS_BYTES 字节；结尾是校验和 4 字节。
#define WQ_PROGRESS_HEADER_SIZE 10u
#define WQ_PROGRESS_BLOB_SIZE (WQ_PROGRESS_HEADER_SIZE + WQ_STARS_BYTES + 4u)

typedef enum {
    WQ_PROGRESS_OK = 0,
    WQ_PROGRESS_ERR_NULL,
    WQ_PROGRESS_ERR_LENGTH,
    WQ_PROGRESS_ERR_MAGIC,
    WQ_PROGRESS_ERR_VERSION,
    WQ_PROGRESS_ERR_CHECKSUM,
} wq_progress_status_t;

typedef struct {
    uint16_t last_level;                  // 最近进入的关卡（全局下标），空档为 0
    uint8_t stars[WQ_STARS_BYTES];        // 每关 2bit：0..3，0 = 未通关
} wq_progress_t;

// 清空成一份空档（不是「不合法」，是合法的零值）。
void wq_progress_reset(wq_progress_t *progress);

// 读写某关星级。越界关卡一律当作 0 / 忽略。
uint8_t wq_progress_stars(const wq_progress_t *progress, uint16_t level);
void wq_progress_set_stars(wq_progress_t *progress, uint16_t level, uint8_t stars);

// 只升不降：取已有星级与本次的较大者。返回是否发生了变化。
bool wq_progress_record_result(wq_progress_t *progress, uint16_t level, uint8_t stars);

// 汇总：已通关数与总星数（标题页成绩行、世界地图用）。
uint16_t wq_progress_cleared_count(const wq_progress_t *progress);
uint32_t wq_progress_total_stars(const wq_progress_t *progress);

// 序列化。返回写入字节数；容量不足返回 0（不写半截数据）。
uint32_t wq_progress_serialize(const wq_progress_t *progress,
                               uint8_t *out, uint32_t capacity);

// 反序列化。任何一项校验不过都返回对应错误，并且**不改动** progress：
// 调用方应当先 reset 再读，读到垃圾时保留空档。
wq_progress_status_t wq_progress_deserialize(wq_progress_t *progress,
                                             const uint8_t *data, uint32_t length);

const char *wq_progress_status_name(wq_progress_status_t status);
