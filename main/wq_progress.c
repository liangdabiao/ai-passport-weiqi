// main/wq_progress.c —— 见 wq_progress.h。
// 不依赖 ESP-IDF 与 LVGL，宿主测试直接编译它。
#include "wq_progress.h"

#include <stddef.h>

static void write_u16(uint8_t *at, uint16_t value)
{
    at[0] = (uint8_t)(value & 0xFFu);
    at[1] = (uint8_t)((value >> 8) & 0xFFu);
}

static uint16_t read_u16(const uint8_t *at)
{
    return (uint16_t)((uint16_t)at[0] | ((uint16_t)at[1] << 8));
}

static void write_u32(uint8_t *at, uint32_t value)
{
    at[0] = (uint8_t)(value & 0xFFu);
    at[1] = (uint8_t)((value >> 8) & 0xFFu);
    at[2] = (uint8_t)((value >> 16) & 0xFFu);
    at[3] = (uint8_t)((value >> 24) & 0xFFu);
}

static uint32_t read_u32(const uint8_t *at)
{
    return (uint32_t)at[0] | ((uint32_t)at[1] << 8) |
           ((uint32_t)at[2] << 16) | ((uint32_t)at[3] << 24);
}

// Fletcher-32：与 qiaopi / 道德经日课同一套校验。要的不是密码学强度，
// 是「半截写入」这类错误的确定性检出。
static uint32_t checksum_of(const uint8_t *data, uint32_t length)
{
    uint32_t low = 0xFFFFu;
    uint32_t high = 0xFFFFu;
    for (uint32_t i = 0; i < length; i++) {
        low = (low + data[i]) % 65535u;
        high = (high + low) % 65535u;
    }
    return (high << 16) | low;
}

void wq_progress_reset(wq_progress_t *progress)
{
    if (!progress) return;
    for (size_t i = 0; i < sizeof(*progress); i++) ((uint8_t *)progress)[i] = 0;
}

uint8_t wq_progress_stars(const wq_progress_t *progress, uint16_t level)
{
    if (!progress || level >= (uint16_t)WQ_LEVEL_COUNT) return 0;
    const uint16_t bit = (uint16_t)(level * 2u);
    return (uint8_t)((progress->stars[bit >> 3] >> (bit & 7)) & 3u);
}

void wq_progress_set_stars(wq_progress_t *progress, uint16_t level, uint8_t stars)
{
    if (!progress || level >= (uint16_t)WQ_LEVEL_COUNT) return;
    if (stars > 3) stars = 3;
    const uint16_t bit = (uint16_t)(level * 2u);
    const uint8_t mask = (uint8_t)(3u << (bit & 7));
    progress->stars[bit >> 3] =
        (uint8_t)((progress->stars[bit >> 3] & (uint8_t)~mask) |
                  (uint8_t)(stars << (bit & 7)));
}

bool wq_progress_record_result(wq_progress_t *progress, uint16_t level, uint8_t stars)
{
    if (!progress || level >= (uint16_t)WQ_LEVEL_COUNT) return false;
    const uint8_t existing = wq_progress_stars(progress, level);
    if (stars <= existing) return false;
    wq_progress_set_stars(progress, level, stars);
    return true;
}

bool wq_progress_unlocked(const wq_progress_t *progress, uint16_t level)
{
    if (level == 0) return true;
    if (level >= (uint16_t)WQ_LEVEL_COUNT) return false;
    return wq_progress_stars(progress, (uint16_t)(level - 1u)) > 0;
}

uint16_t wq_progress_cleared_count(const wq_progress_t *progress)
{
    if (!progress) return 0;
    uint16_t count = 0;
    for (uint16_t level = 0; level < (uint16_t)WQ_LEVEL_COUNT; level++) {
        if (wq_progress_stars(progress, level) > 0) count++;
    }
    return count;
}

uint32_t wq_progress_total_stars(const wq_progress_t *progress)
{
    if (!progress) return 0;
    uint32_t total = 0;
    for (uint16_t level = 0; level < (uint16_t)WQ_LEVEL_COUNT; level++) {
        total += wq_progress_stars(progress, level);
    }
    return total;
}

uint32_t wq_progress_serialize(const wq_progress_t *progress,
                               uint8_t *out, uint32_t capacity)
{
    if (!progress || !out) return 0;
    if (capacity < WQ_PROGRESS_BLOB_SIZE) return 0;

    uint8_t *at = out;
    write_u32(at, WQ_PROGRESS_MAGIC);
    write_u16(at + 4, (uint16_t)WQ_PROGRESS_VERSION);
    write_u16(at + 6, 0);                       // 预留，恒为 0
    write_u16(at + 8, progress->last_level);
    for (uint16_t i = 0; i < (uint16_t)WQ_STARS_BYTES; i++) {
        at[10 + i] = progress->stars[i];
    }
    const uint32_t body = WQ_PROGRESS_BLOB_SIZE - 4u;
    write_u32(at + body, checksum_of(out, body));
    return WQ_PROGRESS_BLOB_SIZE;
}

wq_progress_status_t wq_progress_deserialize(wq_progress_t *progress,
                                             const uint8_t *data, uint32_t length)
{
    if (!progress || !data) return WQ_PROGRESS_ERR_NULL;
    if (length != WQ_PROGRESS_BLOB_SIZE) return WQ_PROGRESS_ERR_LENGTH;
    if (read_u32(data) != WQ_PROGRESS_MAGIC) return WQ_PROGRESS_ERR_MAGIC;
    if (read_u16(data + 4) != (uint16_t)WQ_PROGRESS_VERSION) {
        return WQ_PROGRESS_ERR_VERSION;
    }
    const uint32_t body = WQ_PROGRESS_BLOB_SIZE - 4u;
    if (read_u32(data + body) != checksum_of(data, body)) {
        return WQ_PROGRESS_ERR_CHECKSUM;
    }

    // 全部校验通过后才写入调用方的结构体：失败路径绝不留下半截状态。
    wq_progress_t loaded;
    loaded.last_level = read_u16(data + 8);
    for (uint16_t i = 0; i < (uint16_t)WQ_STARS_BYTES; i++) {
        loaded.stars[i] = data[10 + i];
    }
    *progress = loaded;
    return WQ_PROGRESS_OK;
}

const char *wq_progress_status_name(wq_progress_status_t status)
{
    switch (status) {
        case WQ_PROGRESS_OK:           return "ok";
        case WQ_PROGRESS_ERR_NULL:     return "空指针";
        case WQ_PROGRESS_ERR_LENGTH:   return "长度不符";
        case WQ_PROGRESS_ERR_MAGIC:    return "魔数不符";
        case WQ_PROGRESS_ERR_VERSION:  return "版本不符";
        case WQ_PROGRESS_ERR_CHECKSUM: return "校验和不符";
        default:                       return "未知错误";
    }
}
