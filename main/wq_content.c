// 由 tools/weiqi/gen_content.py 从 tools/weiqi/levels.txt 生成。
// 请勿手改；改关卡源文件后重跑生成器（validate.sh 会用 --check 拦住过期的表）。

#include "wq_content.h"

#include <stddef.h>  /* NULL */

static const uint8_t level_000_stones[] = { 56, 1 };
static const uint8_t level_000_mark_points[] = { 55, 57, 65, 47 };
static const char *const level_000_glyphs[] = { "×", "×", "×", "×" };
static const uint8_t level_000_path_0[] = { 55 };
static const uint8_t level_000_path_1[] = { 57 };
static const uint8_t level_000_path_2[] = { 65 };
static const uint8_t level_000_path_3[] = { 47 };
static const wq_path_t level_000_correct[] = { { 1, level_000_path_0 }, { 1, level_000_path_1 }, { 1, level_000_path_2 }, { 1, level_000_path_3 } };

static const uint8_t level_001_stones[] = { 56, 1, 55, 2, 65, 2, 47, 2 };
static const uint8_t level_001_mark_points[] = { 57 };
static const char *const level_001_glyphs[] = { "×" };
static const uint8_t level_001_path_0[] = { 57 };
static const wq_path_t level_001_correct[] = { { 1, level_001_path_0 } };

static const uint8_t level_002_stones[] = { 56, 1, 47, 1, 48, 1, 55, 2, 46, 2, 65, 2, 38, 2, 57, 2, 39, 2 };
static const uint8_t level_002_mark_points[] = { 49 };
static const char *const level_002_glyphs[] = { "×" };
static const uint8_t level_002_path_0[] = { 49 };
static const wq_path_t level_002_correct[] = { { 1, level_002_path_0 } };

static const uint8_t level_003_stones[] = { 38, 1, 40, 1, 48, 1, 50, 1, 58, 1, 67, 1, 7, 1, 15, 1, 17, 1, 25, 1, 31, 2, 39, 2, 41, 2, 51, 2, 59, 2 };
static const uint8_t level_003_mark_points[] = { 8, 16, 49, 40, 50 };
static const char *const level_003_glyphs[] = { "A", "B", "C", "▲", "▲" };
static const uint8_t level_003_path_0[] = { 49 };
static const wq_path_t level_003_correct[] = { { 1, level_003_path_0 } };

static const uint8_t level_004_stones[] = { 49, 1, 50, 1, 56, 1, 57, 1, 60, 1, 67, 1, 68, 1, 40, 2, 41, 2, 47, 2, 48, 2, 51, 2, 58, 2 };
static const uint8_t level_004_path_0[] = { 59 };
static const wq_path_t level_004_correct[] = { { 1, level_004_path_0 } };

static const uint8_t level_005_stones[] = { 37, 1, 47, 1, 54, 1, 55, 1, 65, 1, 66, 1, 67, 1, 74, 1, 76, 1, 56, 2, 57, 2, 58, 2, 63, 2, 64, 2, 68, 2, 73, 2, 77, 2 };
static const uint8_t level_005_path_0[] = { 75 };
static const wq_path_t level_005_correct[] = { { 1, level_005_path_0 } };

static const uint8_t level_006_stones[] = { 74, 1, 65, 1, 56, 1, 57, 1, 58, 1, 59, 1, 60, 1, 69, 1, 78, 1, 20, 2, 12, 2, 22, 2, 30, 2, 75, 2, 66, 2, 67, 2, 68, 2, 77, 2 };
static const uint8_t level_006_mark_points[] = { 21, 76 };
static const char *const level_006_glyphs[] = { "A", "B" };
static const uint8_t level_006_path_0[] = { 76 };
static const wq_path_t level_006_correct[] = { { 1, level_006_path_0 } };

static const uint8_t level_007_stones[] = { 54, 1, 55, 1, 56, 1, 57, 1, 66, 1, 75, 1, 63, 2, 64, 2, 65, 2, 74, 2 };
static const uint8_t level_007_path_0[] = { 72, 73, 72 };
static const uint8_t level_007_path_1[] = { 73, 72, 73 };
static const wq_path_t level_007_correct[] = { { 3, level_007_path_0 }, { 3, level_007_path_1 } };

static const uint8_t level_008_stones[] = { 54, 1, 55, 1, 56, 1, 57, 1, 58, 1, 67, 1, 76, 1, 6, 1, 15, 1, 24, 1, 33, 1, 42, 1, 43, 1, 44, 1, 63, 2, 64, 2, 65, 2, 66, 2, 75, 2, 73, 2, 7, 2, 16, 2, 25, 2, 34, 2, 35, 2 };
static const uint8_t level_008_path_0[] = { 17, 26, 8 };
static const wq_path_t level_008_correct[] = { { 3, level_008_path_0 } };

static const uint8_t level_009_stones[] = { 54, 1, 55, 1, 56, 1, 57, 1, 58, 1, 67, 1, 76, 1, 6, 1, 15, 1, 24, 1, 33, 1, 43, 1, 44, 1, 63, 2, 64, 2, 65, 2, 66, 2, 75, 2, 73, 2, 7, 2, 16, 2, 25, 2, 17, 2, 35, 2 };
static const uint8_t level_009_mark_points[] = { 8, 26 };
static const char *const level_009_glyphs[] = { "A", "B" };
static const uint8_t level_009_path_0[] = { 34, 26, 8 };
static const wq_path_t level_009_correct[] = { { 3, level_009_path_0 } };

static const uint8_t level_010_stones[] = { 13, 1, 31, 1, 23, 1, 20, 2, 12, 2, 22, 2, 30, 2 };
static const uint8_t level_010_mark_points[] = { 22 };
static const char *const level_010_glyphs[] = { "▲" };
static const uint8_t level_010_path_0[] = { 21 };
static const wq_path_t level_010_correct[] = { { 1, level_010_path_0 } };

static const uint8_t level_011_stones[] = { 45, 1, 46, 1, 47, 1, 56, 1, 66, 1, 74, 1, 75, 1, 54, 2, 55, 2, 63, 2, 65, 2, 73, 2 };
static const uint8_t level_011_path_0[] = { 64, 57, 72 };
static const wq_path_t level_011_correct[] = { { 3, level_011_path_0 } };

static const uint8_t level_012_stones[] = { 22, 1, 31, 1, 40, 1, 48, 1, 58, 1, 67, 1, 68, 1, 32, 2, 38, 2, 39, 2, 41, 2, 49, 2, 51, 2, 56, 2, 57, 2, 59, 2 };
static const uint8_t level_012_path_0[] = { 50, 47, 49 };
static const wq_path_t level_012_correct[] = { { 3, level_012_path_0 } };

static const uint8_t level_013_stones[] = { 23, 1, 32, 1, 42, 1, 52, 1, 60, 1, 68, 1, 69, 1, 31, 2, 41, 2, 49, 2, 51, 2, 59, 2, 67, 2 };
static const uint8_t level_013_path_0[] = { 50, 58, 40 };
static const wq_path_t level_013_correct[] = { { 3, level_013_path_0 } };

static const uint8_t level_014_stones[] = { 19, 1, 20, 1, 29, 1, 38, 1, 47, 1, 55, 1, 63, 1, 65, 1, 73, 1, 1, 2, 10, 2, 18, 2, 28, 2, 36, 2, 37, 2, 46, 2, 54, 2 };
static const uint8_t level_014_mark_points[] = { 54, 36, 46, 37, 28 };
static const char *const level_014_glyphs[] = { "1", "▲", "▲", "▲", "▲" };
static const uint8_t level_014_path_0[] = { 9, 0, 45, 27, 9 };
static const wq_path_t level_014_correct[] = { { 5, level_014_path_0 } };

static const uint8_t level_015_stones[] = { 77, 1, 68, 1, 78, 1, 60, 1, 70, 1, 61, 1, 62, 1, 76, 2, 67, 2, 58, 2, 59, 2, 51, 2, 52, 2, 53, 2 };
static const char *const level_015_options[] = { "3", "4", "5" };

static const uint8_t level_016_stones[] = { 75, 1, 66, 1, 57, 1, 58, 1, 50, 1, 51, 1, 52, 1, 53, 1, 76, 2, 67, 2, 68, 2, 59, 2, 60, 2, 79, 2, 61, 2, 62, 2 };
static const char *const level_016_options[] = { "6", "7", "8" };

static const uint8_t level_017_stones[] = { 75, 1, 66, 1, 57, 1, 48, 1, 76, 1, 49, 1, 41, 1, 51, 1, 42, 1, 52, 1, 53, 1, 67, 2, 58, 2, 77, 2, 59, 2, 50, 2, 60, 2, 79, 2, 61, 2, 62, 2 };
static const char *const level_017_options[] = { "5", "6", "7" };

static const uint8_t level_018_stones[] = { 77, 1, 68, 1, 59, 1, 51, 1, 70, 1, 52, 1, 53, 1, 76, 2, 67, 2, 58, 2, 40, 2, 50, 2, 42, 2, 43, 2, 44, 2 };
static const char *const level_018_options[] = { "7", "8", "9" };

static const uint8_t level_019_stones[] = { 76, 1, 67, 1, 59, 1, 40, 1, 50, 1, 42, 1, 43, 1, 44, 1, 77, 2, 68, 2, 60, 2, 51, 2, 70, 2, 52, 2, 53, 2 };
static const char *const level_019_options[] = { "7", "8", "9" };

static const uint8_t level_020_stones[] = { 76, 1, 67, 1, 58, 1, 59, 1, 60, 1, 79, 1, 61, 1, 62, 1, 75, 2, 66, 2, 57, 2, 48, 2, 49, 2, 50, 2, 51, 2, 52, 2, 53, 2 };
static const char *const level_020_options[] = { "6", "7", "8" };

static const uint8_t level_021_stones[] = { 76, 1, 67, 1, 58, 1, 59, 1, 60, 1, 70, 1, 52, 1, 53, 1, 75, 2, 66, 2, 57, 2, 48, 2, 49, 2, 50, 2, 51, 2, 43, 2, 44, 2 };
static const char *const level_021_options[] = { "8", "9", "10" };

static const uint8_t level_022_stones[] = { 73, 1, 64, 1, 55, 1, 56, 1, 57, 1, 58, 1, 50, 1, 51, 1, 52, 1, 62, 1, 53, 1, 74, 2, 65, 2, 66, 2, 67, 2, 59, 2, 60, 2, 79, 2, 61, 2, 71, 2 };
static const char *const level_022_options[] = { "7", "8", "9" };

static const uint8_t level_023_stones[] = { 74, 1, 65, 1, 56, 1, 47, 1, 38, 1, 39, 1, 40, 1, 41, 1, 42, 1, 43, 1, 44, 1, 75, 2, 66, 2, 57, 2, 48, 2, 49, 2, 50, 2, 69, 2, 51, 2, 52, 2, 53, 2 };
static const char *const level_023_options[] = { "12", "14", "15" };

static const uint8_t level_024_stones[] = { 75, 1, 66, 1, 57, 1, 58, 1, 59, 1, 60, 1, 61, 1, 62, 1, 74, 2, 65, 2, 56, 2, 47, 2, 48, 2, 49, 2, 50, 2, 51, 2, 52, 2, 53, 2 };
static const char *const level_024_options[] = { "8", "10", "12" };

static const uint8_t level_025_stones[] = { 77, 1, 68, 1, 59, 1, 60, 1, 51, 1, 70, 1, 52, 1, 53, 1, 76, 2, 67, 2, 58, 2, 40, 2, 50, 2, 42, 2, 61, 2, 43, 2, 44, 2 };
static const char *const level_025_options[] = { "6", "7", "8" };

static const uint8_t level_026_stones[] = { 74, 1, 65, 1, 56, 1, 47, 1, 48, 1, 67, 1, 49, 1, 68, 1, 50, 1, 51, 1, 52, 1, 53, 1, 75, 2, 66, 2, 57, 2, 58, 2, 59, 2, 69, 2, 60, 2, 61, 2, 62, 2 };
static const char *const level_026_options[] = { "7", "9", "11" };

static const uint8_t level_027_stones[] = { 5, 1, 14, 1, 15, 1, 16, 1, 33, 1, 34, 1, 38, 1, 39, 1, 43, 1, 44, 1, 46, 1, 48, 1, 49, 1, 51, 1, 52, 1, 54, 1, 56, 1, 58, 1, 59, 1, 60, 1, 4, 2, 7, 2, 13, 2, 17, 2, 19, 2, 20, 2, 22, 2, 23, 2, 24, 2, 25, 2, 26, 2, 27, 2, 29, 2, 30, 2, 32, 2, 35, 2, 36, 2, 37, 2, 40, 2, 41, 2, 42, 2, 45, 2, 50, 2 };

static const uint8_t level_028_stones[] = { 5, 1, 14, 1, 15, 1, 16, 1, 33, 1, 34, 1, 38, 1, 39, 1, 43, 1, 44, 1, 46, 1, 48, 1, 49, 1, 51, 1, 52, 1, 54, 1, 56, 1, 58, 1, 59, 1, 60, 1, 4, 2, 7, 2, 13, 2, 17, 2, 19, 2, 20, 2, 22, 2, 23, 2, 24, 2, 25, 2, 26, 2, 27, 2, 29, 2, 30, 2, 32, 2, 35, 2, 36, 2, 37, 2, 40, 2, 41, 2, 42, 2, 45, 2, 50, 2 };
static const uint8_t level_028_targets[] = { 5, 14, 15, 16 };

static const uint8_t level_029_stones[] = { 33, 1, 34, 1, 38, 1, 39, 1, 43, 1, 44, 1, 46, 1, 48, 1, 49, 1, 51, 1, 52, 1, 54, 1, 56, 1, 58, 1, 59, 1, 60, 1, 4, 2, 7, 2, 13, 2, 17, 2, 19, 2, 20, 2, 22, 2, 23, 2, 24, 2, 25, 2, 26, 2, 27, 2, 29, 2, 30, 2, 32, 2, 35, 2, 36, 2, 37, 2, 40, 2, 41, 2, 42, 2, 45, 2, 50, 2 };

static const uint8_t level_030_stones[] = { 40, 1, 30, 2, 39, 2 };
static const char *const level_030_options[] = { "3", "4", "6" };

static const uint8_t level_031_stones[] = { 22, 1, 23, 1, 24, 1, 31, 1, 13, 2, 14, 2, 15, 2, 16, 2, 34, 2, 39, 2, 40, 2 };
static const char *const level_031_options[] = { "4", "5", "6" };

static const uint8_t level_032_stones[] = { 22, 1, 16, 1, 33, 1, 42, 1, 70, 1, 79, 1, 51, 1, 38, 1, 47, 1, 56, 1, 66, 1, 21, 2, 31, 2, 29, 2, 14, 2, 15, 2, 24, 2, 61, 2, 62, 2, 69, 2, 71, 2 };
static const char *const level_032_options[] = { "3", "5", "6" };

static const uint8_t level_033_stones[] = { 57, 1, 48, 1, 38, 1, 29, 1, 21, 1, 40, 1, 31, 1, 64, 2, 56, 2, 47, 2, 66, 2, 39, 2, 49, 2 };
static const char *const level_033_options[] = { "是", "否" };

static const uint8_t level_034_stones[] = { 56, 1, 38, 1, 48, 1, 30, 1, 58, 1, 49, 1, 65, 2, 47, 2, 66, 2, 57, 2, 50, 2 };
static const char *const level_034_options[] = { "0", "1", "2" };

static const uint8_t level_035_stones[] = { 58, 1, 67, 1, 75, 1, 59, 2, 68, 2, 76, 2 };
static const uint8_t level_035_mark_points[] = { 76 };
static const char *const level_035_glyphs[] = { "▲" };
static const uint8_t level_035_path_0[] = { 77 };
static const wq_path_t level_035_correct[] = { { 1, level_035_path_0 } };

static const uint8_t level_036_stones[] = { 30, 1, 39, 1, 46, 1, 47, 1, 49, 1, 50, 1, 40, 2, 48, 2, 55, 2, 56, 2, 58, 2, 59, 2 };
static const uint8_t level_036_path_0[] = { 57 };
static const wq_path_t level_036_correct[] = { { 1, level_036_path_0 } };

static const uint8_t level_037_stones[] = { 52, 1, 65, 1, 68, 1, 69, 1, 75, 1, 76, 1, 79, 1, 23, 2, 38, 2, 49, 2, 66, 2, 67, 2, 74, 2 };
static const uint8_t level_037_path_0[] = { 77 };
static const wq_path_t level_037_correct[] = { { 1, level_037_path_0 } };

static const uint8_t level_038_stones[] = { 49, 1, 50, 1, 56, 1, 57, 1, 60, 1, 67, 1, 68, 1, 40, 2, 41, 2, 47, 2, 48, 2, 51, 2, 58, 2 };
static const uint8_t level_038_path_0[] = { 59 };
static const wq_path_t level_038_correct[] = { { 1, level_038_path_0 } };

static const uint8_t level_039_stones[] = { 49, 1, 50, 1, 55, 1, 56, 1, 57, 1, 59, 1, 63, 1, 65, 1, 68, 1, 72, 1, 73, 1, 39, 2, 45, 2, 46, 2, 48, 2, 54, 2, 58, 2, 66, 2, 67, 2, 74, 2, 75, 2 };
static const uint8_t level_039_path_0[] = { 64 };
static const wq_path_t level_039_correct[] = { { 1, level_039_path_0 } };

static const uint8_t level_040_stones[] = { 22, 1, 30, 1, 40, 1, 59, 1, 21, 2, 29, 2, 39, 2, 48, 2 };
static const uint8_t level_040_path_0[] = { 31 };
static const wq_path_t level_040_correct[] = { { 1, level_040_path_0 } };

static const uint8_t level_041_stones[] = { 48, 1, 56, 1, 58, 1, 59, 1, 65, 1, 24, 2, 46, 2, 47, 2, 49, 2, 57, 2, 66, 2 };
static const uint8_t level_041_path_0[] = { 39 };
static const wq_path_t level_041_correct[] = { { 1, level_041_path_0 } };

static const uint8_t level_042_stones[] = { 20, 1, 29, 1, 37, 1, 39, 1, 46, 1, 48, 1, 56, 1, 30, 2, 38, 2, 40, 2, 49, 2, 57, 2, 66, 2 };
static const uint8_t level_042_path_0[] = { 47 };
static const wq_path_t level_042_correct[] = { { 1, level_042_path_0 } };

static const uint8_t level_043_stones[] = { 21, 1, 30, 1, 47, 1, 48, 1, 37, 2, 38, 2, 40, 2 };
static const uint8_t level_043_mark_points[] = { 39 };
static const char *const level_043_glyphs[] = { "×" };
static const uint8_t level_043_path_0[] = { 39 };
static const wq_path_t level_043_correct[] = { { 1, level_043_path_0 } };

static const uint8_t level_044_stones[] = { 12, 1, 29, 1, 30, 1, 41, 1, 43, 1, 59, 1, 22, 2, 23, 2, 24, 2, 31, 2, 39, 2, 48, 2 };
static const uint8_t level_044_path_0[] = { 40 };
static const wq_path_t level_044_correct[] = { { 1, level_044_path_0 } };

static const uint8_t level_045_stones[] = { 23, 1, 31, 1, 33, 1, 40, 1, 42, 1, 49, 1, 51, 1, 59, 1, 32, 2, 50, 2 };
static const char *const level_045_options[] = { "是", "否" };

static const uint8_t level_046_stones[] = { 12, 1, 21, 1, 31, 1, 38, 1, 40, 1, 48, 1, 50, 1, 58, 1, 22, 2, 30, 2, 32, 2, 39, 2, 41, 2, 47, 2, 51, 2 };
static const char *const level_046_options[] = { "是", "否" };

static const uint8_t level_047_stones[] = { 22, 1, 41, 1, 46, 1, 48, 1, 56, 1, 38, 1, 29, 2, 33, 2, 37, 2, 39, 2, 47, 2 };
static const char *const level_047_options[] = { "是", "否" };

static const uint8_t level_048_stones[] = { 63, 1, 64, 1, 65, 1, 75, 1, 66, 1, 54, 2, 73, 2, 55, 2, 56, 2, 57, 2, 76, 2, 67, 2, 58, 2 };
static const char *const level_048_options[] = { "是", "否" };

static const uint8_t level_049_stones[] = { 54, 1, 55, 1, 56, 1, 57, 1, 58, 1, 67, 1, 76, 1, 64, 2, 65, 2, 66, 2, 73, 2, 75, 2 };
static const uint8_t level_049_path_0[] = { 63 };
static const wq_path_t level_049_correct[] = { { 1, level_049_path_0 } };

static const uint8_t level_050_stones[] = { 28, 1, 46, 1, 20, 2, 37, 2 };
static const uint8_t level_050_mark_points[] = { 36, 38, 37 };
static const char *const level_050_glyphs[] = { "A", "B", "▲" };
static const uint8_t level_050_path_0[] = { 38 };
static const wq_path_t level_050_correct[] = { { 1, level_050_path_0 } };

static const uint8_t level_051_stones[] = { 39, 1, 40, 1, 42, 1, 47, 1, 50, 1, 59, 1, 29, 2, 32, 2, 38, 2, 41, 2, 48, 2, 49, 2 };
static const uint8_t level_051_mark_points[] = { 48, 49 };
static const char *const level_051_glyphs[] = { "▲", "▲" };
static const uint8_t level_051_path_0[] = { 57 };
static const wq_path_t level_051_correct[] = { { 1, level_051_path_0 } };

static const uint8_t level_052_stones[] = { 40, 1, 41, 1, 48, 1, 51, 1, 60, 1, 65, 1, 69, 1, 75, 1, 76, 1, 77, 1, 29, 2, 38, 2, 47, 2, 49, 2, 50, 2, 56, 2, 59, 2, 66, 2, 67, 2, 68, 2 };
static const uint8_t level_052_path_0[] = { 57 };
static const wq_path_t level_052_correct[] = { { 1, level_052_path_0 } };

static const uint8_t level_053_stones[] = { 20, 1, 67, 1, 68, 1, 75, 1, 60, 2, 76, 2, 77, 2 };
static const char *const level_053_options[] = { "能", "不能" };

static const uint8_t level_054_stones[] = { 48, 1, 49, 1, 50, 1, 56, 1, 60, 1, 61, 1, 64, 1, 70, 1, 74, 1, 20, 2, 24, 2, 57, 2, 58, 2, 59, 2, 65, 2, 67, 2, 69, 2 };
static const uint8_t level_054_mark_points[] = { 74 };
static const char *const level_054_glyphs[] = { "1" };
static const uint8_t level_054_path_0[] = { 75 };
static const wq_path_t level_054_correct[] = { { 1, level_054_path_0 } };

static const uint8_t level_055_stones[] = { 49, 1, 50, 1, 51, 1, 58, 1, 61, 1, 71, 1, 57, 2, 59, 2, 60, 2, 65, 2, 67, 2, 70, 2 };
static const uint8_t level_055_mark_points[] = { 70, 60, 59 };
static const char *const level_055_glyphs[] = { "▲", "▲", "▲" };
static const uint8_t level_055_path_0[] = { 69 };
static const wq_path_t level_055_correct[] = { { 1, level_055_path_0 } };

static const uint8_t level_056_stones[] = { 24, 1, 30, 1, 33, 1, 39, 1, 42, 1, 48, 1, 51, 1, 31, 2, 32, 2, 50, 2, 59, 2, 60, 2, 61, 2 };
static const uint8_t level_056_path_0[] = { 49 };
static const uint8_t level_056_path_1[] = { 41 };
static const uint8_t level_056_path_2[] = { 40 };
static const wq_path_t level_056_correct[] = { { 1, level_056_path_0 }, { 1, level_056_path_1 }, { 1, level_056_path_2 } };

static const uint8_t level_057_stones[] = { 30, 1, 49, 1, 57, 1, 59, 1, 68, 1, 69, 1, 41, 2, 50, 2, 60, 2, 70, 2, 78, 2 };
static const uint8_t level_057_path_0[] = { 52 };
static const wq_path_t level_057_correct[] = { { 1, level_057_path_0 } };

static const uint8_t level_058_stones[] = { 22, 1, 33, 1, 42, 1, 49, 1, 50, 1, 41, 2, 48, 2, 51, 2, 59, 2 };
static const uint8_t level_058_mark_points[] = { 50, 49 };
static const char *const level_058_glyphs[] = { "▲", "▲" };
static const uint8_t level_058_path_0[] = { 40, 58, 67, 57, 56, 66, 75, 65, 64 };
static const uint8_t level_058_path_1[] = { 40, 58, 67, 57, 56, 66, 65 };
static const wq_path_t level_058_correct[] = { { 9, level_058_path_0 }, { 7, level_058_path_1 } };

static const uint8_t level_059_stones[] = { 31, 1, 32, 1, 37, 1, 38, 1, 39, 1, 42, 1, 47, 1, 51, 1, 67, 1, 68, 1, 40, 2, 41, 2, 45, 2, 46, 2, 48, 2, 50, 2, 56, 2, 58, 2, 64, 2, 66, 2 };
static const uint8_t level_059_mark_points[] = { 50, 41, 40 };
static const char *const level_059_glyphs[] = { "▲", "▲", "▲" };
static const uint8_t level_059_path_0[] = { 59 };
static const wq_path_t level_059_correct[] = { { 1, level_059_path_0 } };

static const uint8_t level_060_stones[] = { 47, 1, 50, 1, 55, 1, 57, 1, 58, 1, 68, 1, 77, 1, 63, 2, 65, 2, 66, 2, 67, 2, 73, 2, 76, 2 };
static const uint8_t level_060_path_0[] = { 64 };
static const wq_path_t level_060_correct[] = { { 1, level_060_path_0 } };

static const uint8_t level_061_stones[] = { 32, 1, 38, 1, 39, 1, 40, 1, 47, 1, 50, 1, 51, 1, 55, 1, 56, 1, 61, 1, 64, 1, 70, 1, 48, 2, 49, 2, 57, 2, 59, 2, 60, 2, 65, 2, 69, 2, 74, 2, 75, 2, 77, 2, 78, 2 };
static const uint8_t level_061_path_0[] = { 67 };
static const wq_path_t level_061_correct[] = { { 1, level_061_path_0 } };

static const uint8_t level_062_stones[] = { 22, 1, 33, 1, 45, 1, 46, 1, 51, 1, 56, 1, 64, 1, 65, 1, 73, 1, 30, 2, 37, 2, 38, 2, 48, 2, 54, 2, 57, 2, 63, 2, 66, 2, 72, 2 };
static const char *const level_062_options[] = { "能", "不能" };

static const uint8_t level_063_stones[] = { 24, 1, 28, 1, 29, 1, 38, 1, 47, 1, 51, 1, 54, 1, 56, 1, 60, 1, 64, 1, 73, 1, 18, 2, 19, 2, 20, 2, 21, 2, 27, 2, 37, 2, 46, 2, 55, 2, 58, 2, 65, 2, 66, 2 };
static const uint8_t level_063_mark_points[] = { 55, 46, 37 };
static const char *const level_063_glyphs[] = { "▲", "▲", "▲" };
static const uint8_t level_063_path_0[] = { 36 };
static const wq_path_t level_063_correct[] = { { 1, level_063_path_0 } };

static const uint8_t level_064_stones[] = { 24, 1, 28, 1, 48, 1, 58, 1, 59, 1, 60, 1, 41, 2, 49, 2, 50, 2, 56, 2, 57, 2 };
static const uint8_t level_064_mark_points[] = { 48 };
static const char *const level_064_glyphs[] = { "▲" };
static const uint8_t level_064_path_0[] = { 38, 39, 30 };
static const wq_path_t level_064_correct[] = { { 3, level_064_path_0 } };

static const uint8_t level_065_stones[] = { 10, 1, 21, 1, 22, 1, 25, 1, 28, 1, 29, 1, 40, 1, 42, 1, 47, 1, 48, 1, 50, 1, 60, 1, 68, 1, 69, 1, 36, 2, 37, 2, 46, 2, 49, 2, 54, 2, 55, 2, 56, 2, 57, 2, 59, 2, 66, 2, 67, 2, 73, 2, 75, 2 };
static const char *const level_065_options[] = { "5", "6", "7" };

static const uint8_t level_066_stones[] = { 45, 1, 46, 1, 47, 1, 48, 1, 64, 1, 66, 1, 67, 1, 76, 1, 36, 2, 37, 2, 38, 2, 39, 2, 40, 2, 49, 2, 58, 2, 60, 2, 68, 2, 77, 2 };
static const uint8_t level_066_path_0[] = { 57 };
static const wq_path_t level_066_correct[] = { { 1, level_066_path_0 } };

static const uint8_t level_067_stones[] = { 25, 1, 33, 1, 42, 1, 52, 1, 61, 1, 34, 2, 43, 2, 51, 2, 60, 2, 70, 2 };
static const uint8_t level_067_mark_points[] = { 61, 52, 43, 34 };
static const char *const level_067_glyphs[] = { "▲", "▲", "▲", "▲" };
static const uint8_t level_067_path_0[] = { 62, 44, 53 };
static const uint8_t level_067_path_1[] = { 53, 35, 62 };
static const wq_path_t level_067_correct[] = { { 3, level_067_path_0 }, { 3, level_067_path_1 } };

static const uint8_t level_068_stones[] = { 48, 1, 49, 1, 56, 1, 59, 1, 68, 1, 50, 2, 51, 2, 58, 2, 60, 2, 69, 2 };
static const uint8_t level_068_path_0[] = { 67 };
static const wq_path_t level_068_correct[] = { { 1, level_068_path_0 } };

static const uint8_t level_069_stones[] = { 30, 1, 49, 1, 55, 1, 56, 1, 57, 1, 63, 1, 66, 1, 73, 1, 41, 2, 45, 2, 46, 2, 47, 2, 48, 2, 51, 2, 54, 2, 58, 2, 60, 2, 67, 2, 69, 2 };
static const uint8_t level_069_path_0[] = { 40 };
static const wq_path_t level_069_correct[] = { { 1, level_069_path_0 } };

static const uint8_t level_070_stones[] = { 29, 1, 47, 1, 48, 1, 55, 1, 58, 1, 64, 1, 67, 1, 76, 1, 40, 2, 43, 2, 49, 2, 56, 2, 57, 2, 59, 2, 65, 2, 68, 2, 77, 2 };
static const uint8_t level_070_path_0[] = { 74 };
static const wq_path_t level_070_correct[] = { { 1, level_070_path_0 } };

static const uint8_t level_071_stones[] = { 12, 1, 13, 1, 20, 1, 23, 1, 31, 1, 39, 1, 14, 2, 21, 2, 22, 2, 24, 2, 42, 2 };
static const uint8_t level_071_mark_points[] = { 30, 32, 22, 21 };
static const char *const level_071_glyphs[] = { "A", "B", "▲", "▲" };
static const uint8_t level_071_path_0[] = { 32 };
static const wq_path_t level_071_correct[] = { { 1, level_071_path_0 } };

static const uint8_t level_072_stones[] = { 48, 1, 49, 1, 51, 1, 56, 1, 59, 1, 65, 1, 66, 1, 68, 1, 74, 1, 37, 2, 47, 2, 55, 2, 57, 2, 58, 2, 64, 2, 67, 2, 76, 2 };
static const uint8_t level_072_mark_points[] = { 66 };
static const char *const level_072_glyphs[] = { "1" };
static const uint8_t level_072_path_0[] = { 73 };
static const wq_path_t level_072_correct[] = { { 1, level_072_path_0 } };

static const uint8_t level_073_stones[] = { 45, 1, 54, 1, 63, 1, 65, 1, 72, 1, 73, 1, 37, 2, 46, 2, 55, 2, 64, 2, 70, 2, 74, 2, 75, 2 };
static const uint8_t level_073_mark_points[] = { 75, 74 };
static const char *const level_073_glyphs[] = { "▲", "▲" };
static const uint8_t level_073_path_0[] = { 66, 76, 68 };
static const wq_path_t level_073_correct[] = { { 3, level_073_path_0 } };

static const uint8_t level_074_stones[] = { 52, 1, 57, 1, 58, 1, 59, 1, 61, 1, 65, 1, 69, 1, 70, 1, 48, 2, 49, 2, 50, 2, 51, 2, 56, 2, 60, 2, 68, 2 };
static const uint8_t level_074_mark_points[] = { 57, 58, 59 };
static const char *const level_074_glyphs[] = { "▲", "▲", "▲" };
static const uint8_t level_074_path_0[] = { 66 };
static const wq_path_t level_074_correct[] = { { 1, level_074_path_0 } };

static const uint8_t level_075_stones[] = { 11, 1, 28, 1, 38, 1, 40, 1, 46, 1, 56, 1, 57, 1, 58, 1, 47, 2, 48, 2, 55, 2, 59, 2, 60, 2, 64, 2, 65, 2, 67, 2 };
static const uint8_t level_075_mark_points[] = { 40, 48, 47, 49, 39 };
static const char *const level_075_glyphs[] = { "1", "□", "□", "A", "B" };
static const uint8_t level_075_path_0[] = { 49 };
static const wq_path_t level_075_correct[] = { { 1, level_075_path_0 } };

static const uint8_t level_076_stones[] = { 39, 1, 40, 1, 47, 1, 50, 1, 56, 1, 59, 1, 29, 2, 38, 2, 46, 2, 48, 2, 49, 2 };
static const char *const level_076_options[] = { "能", "不能" };

static const uint8_t level_077_stones[] = { 31, 1, 41, 1, 50, 1, 58, 1, 40, 2, 49, 2, 56, 2 };
static const uint8_t level_077_mark_points[] = { 40, 49, 39, 48 };
static const char *const level_077_glyphs[] = { "▲", "▲", "A", "B" };
static const uint8_t level_077_path_0[] = { 48 };
static const wq_path_t level_077_correct[] = { { 1, level_077_path_0 } };

static const uint8_t level_078_stones[] = { 19, 1, 20, 1, 22, 1, 28, 1, 38, 1, 48, 1, 55, 1, 57, 1, 65, 1, 29, 2, 30, 2, 32, 2, 39, 2, 49, 2, 58, 2, 66, 2, 67, 2 };
static const uint8_t level_078_path_0[] = { 47 };
static const wq_path_t level_078_correct[] = { { 1, level_078_path_0 } };

static const uint8_t level_079_stones[] = { 39, 1, 47, 1, 51, 1, 57, 1, 58, 1, 23, 2, 48, 2, 49, 2, 60, 2, 61, 2 };
static const uint8_t level_079_mark_points[] = { 49, 48 };
static const char *const level_079_glyphs[] = { "▲", "▲" };
static const uint8_t level_079_path_0[] = { 41 };
static const wq_path_t level_079_correct[] = { { 1, level_079_path_0 } };

static const uint8_t level_080_stones[] = { 39, 1, 40, 1, 47, 1, 49, 1, 56, 1, 65, 1, 22, 2, 30, 2, 33, 2, 37, 2, 38, 2, 48, 2, 51, 2, 57, 2, 58, 2 };
static const uint8_t level_080_path_0[] = { 59, 67, 68 };
static const wq_path_t level_080_correct[] = { { 3, level_080_path_0 } };

static const uint8_t level_081_stones[] = { 9, 1, 10, 1, 11, 1, 12, 1, 18, 1, 28, 1, 29, 1, 19, 2, 20, 2, 21, 2, 22, 2, 27, 2, 36, 2, 40, 2, 48, 2, 56, 2, 64, 2 };
static const uint8_t level_081_mark_points[] = { 27, 36 };
static const char *const level_081_glyphs[] = { "▲", "▲" };
static const uint8_t level_081_path_0[] = { 46 };
static const wq_path_t level_081_correct[] = { { 1, level_081_path_0 } };

static const uint8_t level_082_stones[] = { 33, 1, 39, 1, 40, 1, 46, 1, 49, 1, 55, 1, 56, 1, 57, 1, 67, 1, 75, 1, 29, 2, 31, 2, 37, 2, 38, 2, 47, 2, 48, 2, 58, 2, 59, 2, 68, 2 };
static const uint8_t level_082_path_0[] = { 41 };
static const wq_path_t level_082_correct[] = { { 1, level_082_path_0 } };

static const uint8_t level_083_stones[] = { 20, 1, 28, 1, 30, 1, 38, 1, 46, 1, 48, 1, 57, 1, 65, 1, 39, 2, 40, 2, 49, 2, 58, 2, 64, 2, 66, 2 };
static const uint8_t level_083_path_0[] = { 56 };
static const wq_path_t level_083_correct[] = { { 1, level_083_path_0 } };

static const uint8_t level_084_stones[] = { 21, 1, 28, 1, 29, 1, 31, 1, 37, 1, 47, 1, 56, 1, 58, 1, 22, 2, 23, 2, 30, 2, 33, 2, 38, 2, 39, 2, 46, 2, 48, 2, 51, 2, 60, 2 };
static const uint8_t level_084_path_0[] = { 40, 49, 50 };
static const wq_path_t level_084_correct[] = { { 3, level_084_path_0 } };

static const uint8_t level_085_stones[] = { 47, 1, 56, 1, 59, 1, 65, 1, 67, 1, 38, 2, 39, 2, 48, 2, 57, 2, 66, 2 };
static const uint8_t level_085_mark_points[] = { 67, 65, 59, 56, 47 };
static const char *const level_085_glyphs[] = { "▲", "▲", "▲", "▲", "▲" };
static const uint8_t level_085_path_0[] = { 75 };
static const wq_path_t level_085_correct[] = { { 1, level_085_path_0 } };

static const uint8_t level_086_stones[] = { 37, 1, 38, 1, 48, 1, 49, 1, 51, 1, 58, 1, 66, 1, 19, 2, 29, 2, 31, 2, 46, 2, 47, 2, 56, 2, 57, 2, 64, 2 };
static const uint8_t level_086_mark_points[] = { 66, 58, 51, 49, 48, 38, 37 };
static const char *const level_086_glyphs[] = { "▲", "▲", "▲", "▲", "▲", "▲", "▲" };
static const uint8_t level_086_path_0[] = { 39 };
static const wq_path_t level_086_correct[] = { { 1, level_086_path_0 } };

static const uint8_t level_087_stones[] = { 39, 1, 40, 1, 47, 1, 49, 1, 56, 1, 57, 1, 64, 1, 66, 1, 67, 1, 74, 1, 21, 2, 29, 2, 32, 2, 38, 2, 41, 2, 46, 2, 50, 2, 58, 2, 59, 2, 68, 2 };
static const char *const level_087_options[] = { "真眼", "假眼" };

static const uint8_t level_088_stones[] = { 28, 1, 29, 1, 30, 1, 31, 1, 32, 1, 37, 1, 42, 1, 51, 1, 55, 1, 59, 1, 64, 1, 65, 1, 69, 1, 75, 1, 38, 2, 39, 2, 40, 2, 47, 2, 49, 2, 50, 2, 56, 2, 57, 2, 67, 2, 68, 2 };
static const char *const level_088_options[] = { "0", "1", "2" };

static const uint8_t level_089_stones[] = { 27, 1, 28, 1, 29, 1, 37, 1, 39, 1, 48, 1, 56, 1, 58, 1, 64, 1, 10, 2, 20, 2, 21, 2, 30, 2, 38, 2, 45, 2, 46, 2, 47, 2 };
static const uint8_t level_089_mark_points[] = { 27, 28, 29, 37, 38, 45, 46, 47 };
static const char *const level_089_glyphs[] = { "▲", "▲", "▲", "▲", "▲", "▲", "▲", "▲" };
static const uint8_t level_089_path_0[] = { 18, 55, 19 };
static const uint8_t level_089_path_1[] = { 19, 55, 18 };
static const wq_path_t level_089_correct[] = { { 3, level_089_path_0 }, { 3, level_089_path_1 } };

static const uint8_t level_090_stones[] = { 43, 1, 49, 1, 50, 1, 51, 1, 57, 1, 58, 1, 61, 1, 62, 1, 63, 1, 64, 1, 65, 1, 69, 1, 77, 1, 38, 2, 40, 2, 41, 2, 48, 2, 54, 2, 55, 2, 56, 2, 59, 2, 60, 2, 66, 2, 67, 2, 68, 2 };
static const uint8_t level_090_path_0[] = { 70 };
static const wq_path_t level_090_correct[] = { { 1, level_090_path_0 } };

static const uint8_t level_091_stones[] = { 30, 1, 39, 1, 47, 1, 49, 1, 50, 1, 56, 1, 59, 1, 64, 1, 68, 1, 73, 1, 77, 1, 40, 2, 41, 2, 42, 2, 48, 2, 51, 2, 57, 2, 60, 2, 65, 2, 66, 2, 67, 2, 69, 2, 74, 2, 78, 2 };
static const uint8_t level_091_mark_points[] = { 49, 50, 59, 68, 77 };
static const char *const level_091_glyphs[] = { "▲", "▲", "▲", "▲", "▲" };
static const uint8_t level_091_path_0[] = { 76 };
static const wq_path_t level_091_correct[] = { { 1, level_091_path_0 } };

static const uint8_t level_092_stones[] = { 62, 1, 69, 1, 71, 1, 78, 1, 79, 1, 50, 2, 51, 2, 52, 2, 53, 2, 59, 2, 68, 2, 77, 2 };
static const uint8_t level_092_path_0[] = { 61 };
static const wq_path_t level_092_correct[] = { { 1, level_092_path_0 } };

static const uint8_t level_093_stones[] = { 40, 1, 41, 1, 43, 1, 46, 1, 47, 1, 48, 1, 51, 1, 55, 1, 60, 1, 64, 1, 69, 1, 77, 1, 78, 1, 49, 2, 50, 2, 56, 2, 57, 2, 59, 2, 65, 2, 68, 2, 74, 2 };
static const uint8_t level_093_path_0[] = { 67 };
static const wq_path_t level_093_correct[] = { { 1, level_093_path_0 } };

static const uint8_t level_094_stones[] = { 19, 1, 20, 1, 27, 1, 29, 1, 38, 1, 39, 1, 40, 1, 49, 1, 56, 1, 57, 1, 59, 1, 66, 1, 28, 2, 37, 2, 45, 2, 47, 2, 48, 2, 54, 2, 55, 2, 65, 2, 73, 2, 74, 2 };
static const uint8_t level_094_path_0[] = { 63 };
static const wq_path_t level_094_correct[] = { { 1, level_094_path_0 } };

static const uint8_t level_095_stones[] = { 40, 1, 48, 1, 50, 1, 52, 1, 54, 1, 55, 1, 57, 1, 58, 1, 60, 1, 61, 1, 64, 1, 65, 1, 72, 1, 74, 1, 42, 2, 47, 2, 51, 2, 56, 2, 59, 2, 66, 2, 67, 2, 68, 2 };
static const uint8_t level_095_mark_points[] = { 48, 57, 58 };
static const char *const level_095_glyphs[] = { "▲", "▲", "▲" };
static const uint8_t level_095_path_0[] = { 39, 49, 31 };
static const wq_path_t level_095_correct[] = { { 3, level_095_path_0 } };

static const uint8_t level_096_stones[] = { 28, 1, 29, 1, 38, 1, 47, 1, 56, 1, 58, 1, 66, 1, 74, 1, 37, 2, 46, 2, 55, 2, 63, 2, 65, 2 };
static const uint8_t level_096_path_0[] = { 73 };
static const wq_path_t level_096_correct[] = { { 1, level_096_path_0 } };

static const uint8_t level_097_stones[] = { 11, 1, 30, 1, 38, 1, 56, 1, 39, 2, 48, 2, 57, 2, 60, 2 };
static const uint8_t level_097_mark_points[] = { 48 };
static const char *const level_097_glyphs[] = { "1" };
static const uint8_t level_097_path_0[] = { 47 };
static const wq_path_t level_097_correct[] = { { 1, level_097_path_0 } };

static const uint8_t level_098_stones[] = { 36, 1, 45, 1, 54, 1, 37, 1, 55, 1, 47, 1, 56, 1, 65, 1, 74, 1, 27, 2, 63, 2, 28, 2, 38, 2, 30, 2, 48, 2, 57, 2, 66, 2, 75, 2 };
static const uint8_t level_098_mark_points[] = { 73, 64 };
static const char *const level_098_glyphs[] = { "A", "B" };
static const uint8_t level_098_path_0[] = { 73 };
static const wq_path_t level_098_correct[] = { { 1, level_098_path_0 } };

static const uint8_t level_099_stones[] = { 10, 1, 11, 1, 12, 1, 13, 1, 14, 1, 19, 1, 29, 1, 30, 1, 39, 1, 46, 1, 47, 1, 48, 1, 20, 2, 21, 2, 22, 2, 27, 2, 28, 2, 31, 2, 37, 2, 38, 2, 45, 2, 50, 2, 55, 2, 56, 2, 57, 2, 59, 2 };
static const uint8_t level_099_mark_points[] = { 27, 28, 37, 38 };
static const char *const level_099_glyphs[] = { "▲", "▲", "▲", "▲" };
static const uint8_t level_099_path_0[] = { 18 };
static const wq_path_t level_099_correct[] = { { 1, level_099_path_0 } };

static const uint8_t level_100_stones[] = { 43, 1, 46, 1, 49, 1, 55, 1, 56, 1, 57, 1, 61, 1, 65, 1, 67, 1, 75, 1, 29, 2, 37, 2, 47, 2, 48, 2, 58, 2, 59, 2, 68, 2 };
static const uint8_t level_100_path_0[] = { 41, 40, 31, 39, 38 };
static const wq_path_t level_100_correct[] = { { 5, level_100_path_0 } };

static const uint8_t level_101_stones[] = { 19, 1, 20, 1, 21, 1, 31, 1, 37, 1, 40, 1, 47, 1, 49, 1, 57, 1, 66, 1, 28, 2, 29, 2, 30, 2, 39, 2, 46, 2, 48, 2, 56, 2, 58, 2, 64, 2, 67, 2 };
static const uint8_t level_101_path_0[] = { 27 };
static const wq_path_t level_101_correct[] = { { 1, level_101_path_0 } };

static const uint8_t level_102_stones[] = { 55, 1, 57, 1, 64, 1, 66, 1, 68, 1, 74, 1, 20, 2, 45, 2, 46, 2, 47, 2, 54, 2, 56, 2, 65, 2 };
static const uint8_t level_102_path_0[] = { 73, 72, 63 };
static const wq_path_t level_102_correct[] = { { 3, level_102_path_0 } };

static const uint8_t level_103_stones[] = { 20, 1, 29, 1, 37, 1, 38, 1, 27, 2, 28, 2, 46, 2, 47, 2, 48, 2, 58, 2 };
static const uint8_t level_103_path_0[] = { 36 };
static const wq_path_t level_103_correct[] = { { 1, level_103_path_0 } };

static const uint8_t level_104_stones[] = { 48, 1 };
static const uint8_t level_104_mark_points[] = { 29, 31, 33 };
static const char *const level_104_glyphs[] = { "A", "B", "C" };
static const uint8_t level_104_path_0[] = { 29 };
static const wq_path_t level_104_correct[] = { { 1, level_104_path_0 } };

static const uint8_t level_105_stones[] = { 48, 1, 47, 2, 58, 2 };
static const uint8_t level_105_mark_points[] = { 48 };
static const char *const level_105_glyphs[] = { "1" };
static const uint8_t level_105_path_0[] = { 57 };
static const wq_path_t level_105_correct[] = { { 1, level_105_path_0 } };

static const uint8_t level_106_stones[] = { 39, 1, 47, 1, 49, 1, 56, 1, 58, 1, 65, 1, 66, 1, 67, 1, 74, 1, 76, 1, 21, 2, 29, 2, 31, 2, 38, 2, 40, 2, 41, 2, 46, 2, 50, 2, 55, 2, 59, 2, 64, 2, 68, 2 };
static const uint8_t level_106_path_0[] = { 48 };
static const wq_path_t level_106_correct[] = { { 1, level_106_path_0 } };

static const uint8_t level_107_stones[] = { 18, 1, 19, 1, 20, 1, 30, 1, 37, 1, 39, 1, 48, 1, 56, 1, 58, 1, 67, 1, 76, 1, 9, 2, 10, 2, 11, 2, 21, 2, 22, 2, 31, 2, 40, 2, 49, 2, 50, 2, 57, 2, 59, 2, 66, 2, 68, 2 };
static const uint8_t level_107_mark_points[] = { 49 };
static const char *const level_107_glyphs[] = { "1" };
static const uint8_t level_107_path_0[] = { 65 };
static const uint8_t level_107_path_1[] = { 75 };
static const uint8_t level_107_path_2[] = { 74 };
static const wq_path_t level_107_correct[] = { { 1, level_107_path_0 }, { 1, level_107_path_1 }, { 1, level_107_path_2 } };

static const uint8_t level_108_stones[] = { 15, 1, 24, 1, 27, 1, 28, 1, 29, 1, 33, 1, 38, 1, 41, 1, 42, 1, 43, 1, 47, 1, 48, 1, 49, 1, 50, 1, 55, 1, 56, 1, 36, 2, 37, 2, 45, 2, 51, 2, 52, 2, 57, 2, 58, 2, 59, 2, 63, 2, 64, 2, 65, 2, 70, 2 };
static const char *const level_108_options[] = { "4", "7", "8" };

static const uint8_t level_109_stones[] = { 28, 1, 46, 1, 47, 1, 48, 1, 50, 1, 58, 1, 67, 1, 75, 1, 76, 1, 55, 2, 56, 2, 57, 2, 64, 2, 66, 2, 73, 2 };
static const uint8_t level_109_path_0[] = { 74, 54, 63 };
static const wq_path_t level_109_correct[] = { { 3, level_109_path_0 } };

static const uint8_t level_110_stones[] = { 36, 1, 37, 1, 38, 1, 45, 1, 48, 1, 49, 1, 54, 1, 58, 1, 65, 1, 67, 1, 76, 1, 46, 2, 55, 2, 57, 2, 63, 2, 64, 2, 66, 2 };
static const uint8_t level_110_path_0[] = { 74, 47, 56 };
static const wq_path_t level_110_correct[] = { { 3, level_110_path_0 } };

static const uint8_t level_111_stones[] = { 19, 1, 20, 1, 27, 1, 30, 1, 31, 1, 40, 1, 49, 1, 58, 1, 64, 1, 65, 1, 66, 1, 28, 2, 29, 2, 38, 2, 39, 2, 45, 2, 46, 2, 48, 2, 56, 2, 57, 2 };
static const uint8_t level_111_path_0[] = { 36 };
static const wq_path_t level_111_correct[] = { { 1, level_111_path_0 } };

static const uint8_t level_112_stones[] = { 28, 1, 36, 1, 46, 1, 47, 1, 57, 1, 58, 1, 59, 1, 63, 1, 64, 1, 68, 1, 45, 2, 54, 2, 55, 2, 56, 2, 65, 2, 66, 2, 67, 2, 73, 2 };
static const uint8_t level_112_path_0[] = { 76, 72, 75 };
static const wq_path_t level_112_correct[] = { { 3, level_112_path_0 } };

static const uint8_t level_113_stones[] = { 38, 1, 48, 1, 54, 1, 55, 1, 56, 1, 66, 1, 67, 1, 76, 1, 57, 2, 58, 2, 59, 2, 63, 2, 64, 2, 65, 2, 68, 2, 73, 2 };
static const uint8_t level_113_mark_points[] = { 63, 64, 65, 73 };
static const char *const level_113_glyphs[] = { "▲", "▲", "▲", "▲" };
static const uint8_t level_113_path_0[] = { 74 };
static const wq_path_t level_113_correct[] = { { 1, level_113_path_0 } };

static const uint8_t level_114_stones[] = { 29, 1, 48, 1, 56, 1, 57, 2 };
static const uint8_t level_114_mark_points[] = { 56 };
static const char *const level_114_glyphs[] = { "1" };
static const uint8_t level_114_path_0[] = { 58 };
static const wq_path_t level_114_correct[] = { { 1, level_114_path_0 } };

static const uint8_t level_115_stones[] = { 39, 1, 57, 1, 47, 2, 49, 2 };
static const uint8_t level_115_mark_points[] = { 38, 48, 56, 49 };
static const char *const level_115_glyphs[] = { "A", "B", "C", "▲" };
static const uint8_t level_115_path_0[] = { 48 };
static const wq_path_t level_115_correct[] = { { 1, level_115_path_0 } };

static const uint8_t level_116_stones[] = { 21, 1, 29, 1, 38, 1, 47, 1, 48, 1, 56, 1, 20, 2, 30, 2, 39, 2, 49, 2, 57, 2 };
static const char *const level_116_options[] = { "强形", "弱形" };

static const uint8_t level_117_stones[] = { 21, 1, 28, 1, 37, 1, 39, 1, 40, 1, 49, 1, 54, 1, 57, 1, 65, 1, 66, 1, 67, 1, 73, 1, 74, 1, 76, 1, 42, 2, 45, 2, 46, 2, 47, 2, 48, 2, 56, 2, 58, 2, 59, 2, 64, 2, 68, 2, 77, 2 };
static const uint8_t level_117_path_0[] = { 63, 55, 36, 72, 63 };
static const uint8_t level_117_path_1[] = { 63, 55, 38, 72, 63 };
static const wq_path_t level_117_correct[] = { { 5, level_117_path_0 }, { 5, level_117_path_1 } };

static const uint8_t level_118_stones[] = { 21, 1, 22, 1, 29, 1, 38, 1, 48, 1, 50, 1, 57, 1, 11, 2, 20, 2, 28, 2, 30, 2, 39, 2 };
static const uint8_t level_118_path_0[] = { 47, 37, 46 };
static const wq_path_t level_118_correct[] = { { 3, level_118_path_0 } };

static const uint8_t level_119_stones[] = { 37, 1, 38, 1, 46, 1, 48, 1, 57, 1, 64, 1, 66, 1, 69, 1, 73, 1, 78, 1, 39, 2, 40, 2, 47, 2, 56, 2, 65, 2, 67, 2, 74, 2, 75, 2 };
static const uint8_t level_119_path_0[] = { 76, 77, 55, 76, 58 };
static const wq_path_t level_119_correct[] = { { 5, level_119_path_0 } };

static const uint8_t level_120_stones[] = { 49, 1, 48, 1, 47, 1, 63, 1, 72, 1, 73, 1, 65, 1, 66, 1, 76, 1, 77, 1, 68, 1, 59, 1, 29, 1, 41, 1, 28, 1, 30, 1, 10, 1, 58, 2, 67, 2, 54, 2, 55, 2, 46, 2, 37, 2, 64, 2, 56, 2, 57, 2, 38, 2 };
static const uint8_t level_120_path_0[] = { 75 };
static const wq_path_t level_120_correct[] = { { 1, level_120_path_0 } };

static const uint8_t level_121_stones[] = { 48, 1, 58, 1, 61, 1, 46, 2, 56, 2, 57, 2 };
static const uint8_t level_121_mark_points[] = { 61, 28, 49, 67 };
static const char *const level_121_glyphs[] = { "1", "A", "B", "C" };
static const uint8_t level_121_path_0[] = { 49 };
static const wq_path_t level_121_correct[] = { { 1, level_121_path_0 } };

static const uint8_t level_122_stones[] = { 39, 1, 57, 2 };
static const uint8_t level_122_mark_points[] = { 39, 49, 50 };
static const char *const level_122_glyphs[] = { "1", "A", "B" };
static const uint8_t level_122_path_0[] = { 50 };
static const wq_path_t level_122_correct[] = { { 1, level_122_path_0 } };

static const uint8_t level_123_stones[] = { 55, 1, 64, 1, 47, 1, 56, 1, 74, 1, 48, 1, 58, 1, 59, 1, 68, 1, 77, 1, 65, 2, 57, 2, 66, 2, 49, 2, 50, 2, 51, 2, 60, 2, 69, 2 };
static const uint8_t level_123_mark_points[] = { 73, 75, 76 };
static const char *const level_123_glyphs[] = { "A", "B", "C" };
static const uint8_t level_123_path_0[] = { 76, 73, 78 };
static const wq_path_t level_123_correct[] = { { 3, level_123_path_0 } };

static const uint8_t level_124_stones[] = { 20, 1, 22, 1, 31, 1, 38, 1, 39, 1, 47, 1, 32, 2, 33, 2, 40, 2, 48, 2, 56, 2, 66, 2 };
static const char *const level_124_options[] = { "好的回应", "脱先" };

static const uint8_t level_125_stones[] = { 19, 1, 20, 1, 29, 1, 37, 1, 47, 1, 48, 1, 56, 1, 58, 1, 66, 1, 67, 1, 28, 2, 38, 2, 39, 2, 40, 2, 42, 2, 49, 2, 59, 2, 68, 2 };
static const char *const level_125_options[] = { "加强", "脱先" };

static const uint8_t level_126_stones[] = { 10, 1, 20, 1, 21, 1, 22, 1, 24, 1, 27, 1, 28, 1, 32, 1, 39, 1, 40, 1, 42, 1, 45, 1, 46, 1, 51, 1, 60, 1, 67, 1, 69, 1, 77, 1, 78, 1, 29, 2, 30, 2, 37, 2, 38, 2, 41, 2, 47, 2, 48, 2, 49, 2, 50, 2, 54, 2, 55, 2, 56, 2, 59, 2, 63, 2, 65, 2, 68, 2, 73, 2, 74, 2, 75, 2 };
static const uint8_t level_126_mark_points[] = { 31, 36, 76 };
static const char *const level_126_glyphs[] = { "A", "B", "C" };
static const uint8_t level_126_path_0[] = { 76 };
static const wq_path_t level_126_correct[] = { { 1, level_126_path_0 } };

static const uint8_t level_127_stones[] = { 54, 1, 55, 1, 56, 1, 64, 1, 66, 1, 67, 1, 68, 1, 73, 1, 28, 2, 46, 2, 47, 2, 51, 2, 57, 2, 58, 2, 59, 2, 69, 2, 77, 2, 78, 2 };
static const uint8_t level_127_path_0[] = { 75 };
static const wq_path_t level_127_correct[] = { { 1, level_127_path_0 } };

static const uint8_t level_128_stones[] = { 27, 1, 28, 1, 29, 1, 38, 1, 39, 1, 41, 1, 49, 1, 54, 1, 57, 1, 59, 1, 61, 1, 66, 1, 74, 1, 75, 1, 36, 2, 37, 2, 46, 2, 47, 2, 48, 2, 56, 2, 58, 2, 64, 2, 65, 2 };
static const uint8_t level_128_path_0[] = { 73, 67, 63 };
static const wq_path_t level_128_correct[] = { { 3, level_128_path_0 } };

static const uint8_t level_129_stones[] = { 54, 1, 74, 1, 65, 1, 56, 1, 47, 1, 46, 1, 63, 2, 45, 2, 36, 2, 37, 2, 38, 2, 48, 2, 57, 2, 66, 2, 40, 2 };
static const uint8_t level_129_path_0[] = { 64 };
static const wq_path_t level_129_correct[] = { { 1, level_129_path_0 } };

static const uint8_t level_130_stones[] = { 20, 1, 28, 1, 29, 1, 72, 1, 63, 1, 54, 1, 45, 1, 36, 1, 27, 1, 21, 1, 31, 1, 32, 1, 77, 1, 68, 1, 59, 1, 58, 1, 57, 1, 51, 1, 39, 2, 30, 2, 48, 2, 74, 2, 66, 2, 67, 2, 64, 2, 55, 2, 46, 2, 56, 2, 37, 2, 38, 2 };
static const uint8_t level_130_path_0[] = { 76 };
static const wq_path_t level_130_correct[] = { { 1, level_130_path_0 } };

static const uint8_t level_131_stones[] = { 27, 1, 28, 1, 38, 1, 48, 1, 57, 1, 66, 1, 68, 1, 30, 1, 73, 2, 65, 2, 56, 2, 55, 2, 47, 2, 45, 2, 37, 2 };
static const uint8_t level_131_path_0[] = { 63, 36, 54 };
static const wq_path_t level_131_correct[] = { { 3, level_131_path_0 } };

static const uint8_t level_132_stones[] = { 57, 1, 48, 1, 39, 1, 65, 1, 74, 1, 73, 1, 29, 1, 19, 1, 11, 1, 64, 2, 55, 2, 45, 2, 37, 2, 28, 2, 47, 2 };
static const char *const level_132_options[] = { "活棋", "死棋", "取决于谁先落子" };

static const uint8_t level_133_stones[] = { 56, 1, 48, 1, 58, 1, 47, 1, 45, 1, 57, 2, 66, 2, 49, 2, 50, 2, 60, 2, 61, 2 };
static const uint8_t level_133_path_0[] = { 67 };
static const wq_path_t level_133_correct[] = { { 1, level_133_path_0 } };

static const uint8_t level_134_stones[] = { 47, 1, 38, 1, 39, 1, 40, 1, 41, 1, 78, 1, 69, 1, 60, 1, 51, 1, 33, 1, 20, 1, 57, 1, 56, 2, 65, 2, 46, 2, 37, 2, 55, 2, 48, 2, 49, 2, 50, 2, 59, 2, 68, 2, 77, 2, 28, 2 };
static const uint8_t level_134_path_0[] = { 67 };
static const wq_path_t level_134_correct[] = { { 1, level_134_path_0 } };

static const uint8_t level_135_stones[] = { 54, 1, 45, 1, 37, 1, 38, 1, 39, 1, 49, 1, 58, 1, 67, 1, 36, 2, 27, 2, 19, 2, 46, 2, 47, 2, 48, 2, 40, 2, 31, 2, 12, 2, 50, 2, 59, 2, 68, 2, 33, 2, 65, 2, 70, 2 };
static const uint8_t level_135_path_0[] = { 56, 57, 66 };
static const wq_path_t level_135_correct[] = { { 3, level_135_path_0 } };

static const uint8_t level_136_stones[] = { 45, 1, 37, 1, 38, 1, 47, 1, 48, 1, 58, 1, 68, 1, 69, 1, 36, 2, 28, 2, 18, 2, 29, 2, 39, 2, 49, 2, 59, 2, 60, 2, 61, 2, 41, 2, 30, 2 };
static const uint8_t level_136_path_0[] = { 57, 67, 56, 46, 55 };
static const uint8_t level_136_path_1[] = { 57, 67, 56, 46, 54 };
static const wq_path_t level_136_correct[] = { { 5, level_136_path_0 }, { 5, level_136_path_1 } };

static const uint8_t level_137_stones[] = { 65, 1, 56, 1, 47, 1, 66, 1, 37, 1, 29, 1, 67, 2, 57, 2, 58, 2, 69, 2, 48, 2, 39, 2, 38, 2, 28, 2, 32, 2 };
static const uint8_t level_137_mark_points[] = { 28 };
static const char *const level_137_glyphs[] = { "1" };
static const uint8_t level_137_path_0[] = { 19 };
static const wq_path_t level_137_correct[] = { { 1, level_137_path_0 } };

static const uint8_t level_138_stones[] = { 47, 1, 60, 1, 58, 2 };
static const uint8_t level_138_mark_points[] = { 58, 60, 55, 56, 46, 38, 65, 66, 64, 57, 28 };
static const char *const level_138_glyphs[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11" };
static const uint8_t level_138_path_0[] = { 55, 56, 46, 38, 65, 66, 64, 57, 28 };
static const wq_path_t level_138_correct[] = { { 9, level_138_path_0 } };

static const uint8_t level_139_stones[] = { 47, 1, 49, 1, 57, 2, 58, 2 };
static const uint8_t level_139_mark_points[] = { 57, 48, 56, 59 };
static const char *const level_139_glyphs[] = { "1", "A", "B", "C" };
static const uint8_t level_139_path_0[] = { 56 };
static const uint8_t level_139_path_1[] = { 48 };
static const wq_path_t level_139_correct[] = { { 1, level_139_path_0 }, { 1, level_139_path_1 } };

static const uint8_t level_140_stones[] = { 30, 1, 31, 1, 33, 1, 73, 1, 65, 1, 56, 1, 47, 1, 37, 1, 28, 1, 29, 1, 60, 2, 52, 2, 50, 2, 64, 2, 55, 2, 46, 2, 36, 2, 27, 2, 19, 2, 20, 2, 21, 2, 3, 2, 38, 2, 39, 2, 48, 2, 58, 2 };
static const uint8_t level_140_path_0[] = { 45, 54, 63 };
static const wq_path_t level_140_correct[] = { { 3, level_140_path_0 } };

static const uint8_t level_141_stones[] = { 65, 1, 56, 1, 48, 1, 39, 1, 58, 1, 57, 2, 66, 2, 47, 2, 49, 2, 40, 2, 31, 2 };
static const uint8_t level_141_path_0[] = { 38, 30, 21 };
static const wq_path_t level_141_correct[] = { { 3, level_141_path_0 } };

static const uint8_t level_142_stones[] = { 73, 1, 64, 1, 55, 1, 46, 1, 37, 1, 38, 1, 30, 1, 21, 1, 48, 1, 49, 1, 50, 1, 12, 1, 5, 1, 57, 2, 47, 2, 56, 2, 65, 2, 59, 2, 60, 2, 39, 2, 40, 2, 32, 2, 29, 2, 28, 2, 11, 2, 25, 2, 2, 2, 53, 2 };
static const uint8_t level_142_path_0[] = { 58, 67, 66, 75, 74, 66, 68 };
static const wq_path_t level_142_correct[] = { { 7, level_142_path_0 } };

static const uint8_t level_143_stones[] = { 67, 1, 68, 1, 61, 1, 57, 1, 48, 1, 47, 1, 37, 1, 29, 1, 27, 1, 44, 1, 12, 1, 10, 1, 45, 2, 46, 2, 55, 2, 64, 2, 63, 2, 66, 2, 56, 2, 74, 2, 58, 2, 49, 2, 40, 2, 36, 2, 33, 2 };
static const uint8_t level_143_path_0[] = { 38, 39, 30, 38, 20, 28, 19 };
static const wq_path_t level_143_correct[] = { { 7, level_143_path_0 } };

static const uint8_t level_144_stones[] = { 57, 1, 58, 1, 59, 1, 52, 1, 47, 1, 46, 1, 19, 1, 20, 1, 21, 1, 30, 1, 14, 1, 55, 2, 56, 2, 66, 2, 67, 2, 48, 2, 39, 2, 29, 2, 28, 2, 31, 2, 40, 2, 33, 2, 26, 2 };
static const uint8_t level_144_path_0[] = { 36, 27, 38 };
static const wq_path_t level_144_correct[] = { { 3, level_144_path_0 } };

static const uint8_t level_145_stones[] = { 45, 1, 46, 1, 56, 1, 65, 1, 29, 1, 10, 1, 72, 2, 63, 2, 54, 2, 58, 2, 67, 2, 76, 2, 40, 2, 61, 2 };
static const uint8_t level_145_path_0[] = { 74 };
static const wq_path_t level_145_correct[] = { { 1, level_145_path_0 } };

static const uint8_t level_146_stones[] = { 58, 1, 57, 1, 56, 1, 55, 1, 19, 1, 29, 1, 31, 1, 22, 1, 20, 1, 3, 1, 68, 2, 59, 2, 50, 2, 41, 2, 48, 2, 38, 2, 46, 2, 37, 2, 28, 2, 24, 2 };
static const uint8_t level_146_path_0[] = { 39, 40, 30, 49, 47 };
static const wq_path_t level_146_correct[] = { { 5, level_146_path_0 } };

static const uint8_t level_147_stones[] = { 56, 1, 65, 1, 73, 1, 66, 1, 76, 1, 69, 1, 60, 1, 33, 1, 50, 1, 63, 2, 64, 2, 55, 2, 46, 2, 47, 2, 57, 2, 58, 2, 59, 2, 39, 2, 20, 2 };
static const uint8_t level_147_path_0[] = { 77, 68, 67, 78, 75, 74, 72 };
static const wq_path_t level_147_correct[] = { { 7, level_147_path_0 } };

static const uint8_t level_148_stones[] = { 70, 1, 61, 1, 52, 1, 42, 1, 34, 1, 59, 1, 50, 1, 49, 1, 48, 1, 66, 1, 65, 1, 56, 1, 78, 1, 64, 2, 55, 2, 47, 2, 39, 2, 37, 2, 40, 2, 41, 2, 51, 2, 60, 2, 69, 2, 68, 2 };
static const uint8_t level_148_path_0[] = { 57, 58, 67 };
static const uint8_t level_148_path_1[] = { 67, 57, 76, 75, 73 };
static const wq_path_t level_148_correct[] = { { 3, level_148_path_0 }, { 5, level_148_path_1 } };

static const uint8_t level_149_stones[] = { 63, 1, 54, 1, 46, 1, 66, 1, 67, 1, 58, 1, 59, 1, 69, 1, 48, 1, 39, 1, 28, 1, 55, 2, 56, 2, 57, 2, 65, 2, 70, 2, 60, 2, 50, 2, 49, 2, 52, 2, 32, 2 };
static const uint8_t level_149_path_0[] = { 75 };
static const wq_path_t level_149_correct[] = { { 1, level_149_path_0 } };

static const uint8_t level_150_stones[] = { 63, 1, 54, 1, 45, 1, 46, 1, 47, 1, 57, 1, 58, 1, 67, 1, 72, 2, 64, 2, 55, 2, 56, 2, 66, 2, 38, 2, 37, 2, 36, 2, 48, 2, 49, 2, 50, 2, 69, 2, 52, 2, 30, 2, 18, 2 };
static const uint8_t level_150_path_0[] = { 74, 73, 75 };
static const wq_path_t level_150_correct[] = { { 3, level_150_path_0 } };

static const uint8_t level_151_stones[] = { 56, 1, 55, 1, 48, 1, 37, 1, 29, 1, 66, 1, 67, 1, 68, 1, 60, 1, 21, 1, 12, 1, 52, 1, 63, 2, 64, 2, 65, 2, 39, 2, 49, 2, 57, 2, 58, 2, 31, 2, 42, 2 };
static const uint8_t level_151_path_0[] = { 46, 47, 38, 45, 54, 46, 28 };
static const wq_path_t level_151_correct[] = { { 7, level_151_path_0 } };

static const uint8_t level_152_stones[] = { 48, 1, 47, 1, 56, 1, 65, 1, 67, 1, 77, 1, 69, 1, 37, 1, 28, 1, 29, 1, 60, 1, 51, 1, 33, 1, 11, 1, 73, 2, 64, 2, 55, 2, 46, 2, 38, 2, 39, 2, 40, 2, 49, 2, 59, 2, 68, 2, 22, 2, 14, 2 };
static const uint8_t level_152_path_0[] = { 66, 58, 74 };
static const wq_path_t level_152_correct[] = { { 3, level_152_path_0 } };

static const uint8_t level_153_stones[] = { 73, 1, 64, 1, 55, 1, 47, 1, 48, 1, 49, 1, 59, 1, 60, 1, 70, 1, 78, 1, 52, 1, 31, 1, 46, 2, 37, 2, 38, 2, 69, 2, 68, 2, 58, 2, 57, 2, 56, 2, 65, 2, 74, 2, 75, 2, 76, 2, 20, 2 };
static const uint8_t level_153_path_0[] = { 67, 66, 79 };
static const wq_path_t level_153_correct[] = { { 3, level_153_path_0 } };

const wq_level_t wq_levels[WQ_LEVEL_COUNT] = {
    {
        .title = "围棋游戏",
        .instruction = "棋子相邻的空点叫做『气』。请填上黑子的一个气。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_000_stones,
        .stone_count = 1,
        .mark_points = level_000_mark_points,
        .mark_glyphs = level_000_glyphs,
        .mark_count = 4,
        .correct = level_000_correct,
        .correct_count = 4,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "围棋游戏",
        .instruction = "当一个棋子所有的气都被对方棋子占满，它就被吃掉了。请填上黑子的最后一口气把它吃掉。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_001_stones,
        .stone_count = 4,
        .mark_points = level_001_mark_points,
        .mark_glyphs = level_001_glyphs,
        .mark_count = 1,
        .correct = level_001_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "围棋游戏",
        .instruction = "这条黑链只剩一气了，这叫做『打吃』（atari）。请吃掉这条被打吃的黑链。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_002_stones,
        .stone_count = 9,
        .mark_points = level_002_mark_points,
        .mark_glyphs = level_002_glyphs,
        .mark_count = 1,
        .correct = level_002_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "自杀",
        .instruction = "白先。下在 A 或 B 是『自杀』（白没有气），不允许。但下在 C 是允许的，因为能吃掉标▲的黑子从而给自己造出气。请吃掉标▲的黑子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_003_stones,
        .stone_count = 15,
        .mark_points = level_003_mark_points,
        .mark_glyphs = level_003_glyphs,
        .mark_count = 5,
        .correct = level_003_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "自杀",
        .instruction = "白先。双方都被打吃。没有气的着法不允许，除非能吃掉对方。请吃掉一颗或更多黑子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_004_stones,
        .stone_count = 13,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_004_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "自杀",
        .instruction = "白先。双方都被打吃。没有气的着法不允许，除非能吃掉对方。请吃掉一颗或更多黑子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_005_stones,
        .stone_count = 17,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_005_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "眼",
        .instruction = "A 点被白子包围，这叫『眼』。黑不能下在 A（自吃）。B 点也是眼，但黑可以下在 B 并吃掉白子。请吃掉这些白子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_006_stones,
        .stone_count = 18,
        .mark_points = level_006_mark_points,
        .mark_glyphs = level_006_glyphs,
        .mark_count = 2,
        .correct = level_006_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "眼",
        .instruction = "白棋有一个由两个空点组成的大眼，但白棋并不安全。黑先，逐一填眼吃掉白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_007_stones,
        .stone_count = 10,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_007_correct,
        .correct_count = 2,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "眼",
        .instruction = "白棋有两块棋。一块有两只眼，另一块只有一个大眼。两眼的那块是活的，永远吃不掉。黑先，吃掉那块可以吃的白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_008_stones,
        .stone_count = 25,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_008_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "眼",
        .instruction = "一块白棋有两只『真眼』。另一块在 A 处有真眼、在 B 处是『假眼』。假眼不安全，可以被攻破。黑先，从假眼入手吃掉这块白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_009_stones,
        .stone_count = 24,
        .mark_points = level_009_mark_points,
        .mark_glyphs = level_009_glyphs,
        .mark_count = 2,
        .correct = level_009_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "劫",
        .instruction = "为了避免无限互相提子，有一条特殊规则叫『劫规』：禁止立即提回同样的形状。黑可以吃掉标▲的白子，但白不能立刻提回。白必须先在别处下一手。请吃掉标▲的白子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_010_stones,
        .stone_count = 7,
        .mark_points = level_010_mark_points,
        .mark_glyphs = level_010_glyphs,
        .mark_count = 1,
        .correct = level_010_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "劫",
        .instruction = "利用劫规吃掉这块白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_011_stones,
        .stone_count = 12,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_011_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "劫",
        .instruction = "请把你的黑子连接起来。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_012_stones,
        .stone_count = 16,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_012_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "劫",
        .instruction = "利用劫规吃掉这两颗白子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_013_stones,
        .stone_count = 13,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_013_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "劫",
        .instruction = "白刚走了 1 吃掉一颗黑子。要绕过劫规，请为黑棋找一个白必须应的地方下子，这叫做『劫材』。然后黑就能吃掉标▲的白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_014_stones,
        .stone_count = 17,
        .mark_points = level_014_mark_points,
        .mark_glyphs = level_014_glyphs,
        .mark_count = 5,
        .correct = level_014_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "如果你用棋子包围了棋盘的一部分，这部分就称为你的'领地'。领地中的每个空交叉点都为你计一分。分数可以通过领地和提子来获得。游戏结束时，得分最多者获胜。角部的领地有多少分？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_015_stones,
        .stone_count = 14,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "如果你用棋子包围了棋盘的一部分，这部分就称为你的'领地'。领地中的每个空交叉点都为你计一分。分数可以通过领地和提子来获得。游戏结束时，得分最多者获胜。角部的领地有多少分？",
        .options = level_015_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "角部的领地有多少分？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_016_stones,
        .stone_count = 16,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "角部的领地有多少分？",
        .options = level_016_options,
        .option_count = 3,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "角部的领地有多少分？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_017_stones,
        .stone_count = 20,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "角部的领地有多少分？",
        .options = level_017_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "角部的领地有多少分？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_018_stones,
        .stone_count = 15,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "角部的领地有多少分？",
        .options = level_018_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "角部的领地有多少分？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_019_stones,
        .stone_count = 15,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "角部的领地有多少分？",
        .options = level_019_options,
        .option_count = 3,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "角部的领地有多少分？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_020_stones,
        .stone_count = 17,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "角部的领地有多少分？",
        .options = level_020_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "角部的领地有多少分？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_021_stones,
        .stone_count = 17,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "角部的领地有多少分？",
        .options = level_021_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "角部的领地有多少分？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_022_stones,
        .stone_count = 20,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "角部的领地有多少分？",
        .options = level_022_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "角部的领地有多少分？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_023_stones,
        .stone_count = 21,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "角部的领地有多少分？",
        .options = level_023_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "角部的领地有多少分？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_024_stones,
        .stone_count = 18,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "角部的领地有多少分？",
        .options = level_024_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "对手在你的领地里的棋子如果缺少两个眼，就会被吃掉。这些被吃的棋子称为'死子'。在游戏结束时，死子作为俘虏被从棋盘上提走，留下一个空的领地交叉点。因此，一个死子相当于两分：一分是俘虏，一分是领地。角部的领地有多少分？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_025_stones,
        .stone_count = 17,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "对手在你的领地里的棋子如果缺少两个眼，就会被吃掉。这些被吃的棋子称为'死子'。在游戏结束时，死子作为俘虏被从棋盘上提走，留下一个空的领地交叉点。因此，一个死子相当于两分：一分是俘虏，一分是领地。角部的领地有多少分？",
        .options = level_025_options,
        .option_count = 3,
        .answer = 2,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "角部的领地有多少分？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_026_stones,
        .stone_count = 21,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "角部的领地有多少分？",
        .options = level_026_options,
        .option_count = 3,
        .answer = 2,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对局结束",
        .instruction = "轮到你落子时，你并非必须在棋盘上放置棋子。你可以选择停一手。当双方都认为没有更好的着法时，通过双方连续停一手来结束这局棋。本局已经结束。请点击“停一手”来结束对局。",
        .kind = WQ_KIND_END_PASS,
        .player = 1,
        .stones = level_027_stones,
        .stone_count = 43,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对局结束",
        .instruction = "双方都停一手后，会进入“提子阶段”，此时你可以从棋局中移除明显已死的棋子。请点击并移除那些死掉的黑棋棋子。",
        .kind = WQ_KIND_END_REMOVE,
        .player = 1,
        .stones = level_028_stones,
        .stone_count = 43,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = level_028_targets,
        .target_count = 4,
    },
    {
        .title = "对局结束",
        .instruction = "移除死子后，计算黑白双方领地的大小。黑棋领地有24目。白棋领地有18目，加上被吃的4颗死子，共计22目。因此，黑棋赢得了本局。请点击“完成”来结束对局。",
        .kind = WQ_KIND_END_FINISH,
        .player = 1,
        .stones = level_029_stones,
        .stone_count = 39,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "气",
        .instruction = "计算黑棋棋串的气数。",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_030_stones,
        .stone_count = 3,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "计算黑棋棋串的气数。",
        .options = level_030_options,
        .option_count = 3,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "气",
        .instruction = "计算黑棋棋串的气数。",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_031_stones,
        .stone_count = 11,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "计算黑棋棋串的气数。",
        .options = level_031_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "棋串",
        .instruction = "计算白棋棋串的数量。",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_032_stones,
        .stone_count = 21,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "计算白棋棋串的数量。",
        .options = level_032_options,
        .option_count = 3,
        .answer = 2,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "打吃",
        .instruction = "标记的棋串是否处于打吃状态？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_033_stones,
        .stone_count = 13,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "标记的棋串是否处于打吃状态？",
        .options = level_033_options,
        .option_count = 2,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "计算打吃",
        .instruction = "有多少个白棋棋串处于打吃状态？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_034_stones,
        .stone_count = 11,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "有多少个白棋棋串处于打吃状态？",
        .options = level_034_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "提子",
        .instruction = "黑先。吃掉被标记的白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_035_stones,
        .stone_count = 6,
        .mark_points = level_035_mark_points,
        .mark_glyphs = level_035_glyphs,
        .mark_count = 1,
        .correct = level_035_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "吃掉棋串",
        .instruction = "黑先。吃掉一个或多个白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_036_stones,
        .stone_count = 12,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_036_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "吃掉棋串",
        .instruction = "白先。吃掉一个或多个黑棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_037_stones,
        .stone_count = 13,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_037_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "双方打吃",
        .instruction = "白先。吃掉一个或多个黑棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_038_stones,
        .stone_count = 13,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_038_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "双方打吃",
        .instruction = "白先。吃掉一个或多个黑棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_039_stones,
        .stone_count = 21,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_039_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "寻找逃跑",
        .instruction = "黑先。解救处于打吃的棋串。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_040_stones,
        .stone_count = 8,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_040_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "寻找逃跑",
        .instruction = "黑先。解救处于打吃的棋串。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_041_stones,
        .stone_count = 11,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_041_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "创造开口",
        .instruction = "白先。通过制造一个突破口来解救被打吃的棋串。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_042_stones,
        .stone_count = 13,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_042_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "连接",
        .instruction = "棋子可以通过形成棋串来互相帮助。棋串比单颗棋子更难被吃。你可以通过连接你的棋子来形成棋串。连接白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_043_stones,
        .stone_count = 7,
        .mark_points = level_043_mark_points,
        .mark_glyphs = level_043_glyphs,
        .mark_count = 1,
        .correct = level_043_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "切断",
        .instruction = "黑先。切断白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_044_stones,
        .stone_count = 12,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_044_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "自杀",
        .instruction = "白先。白棋能在A点落子吗？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_045_stones,
        .stone_count = 10,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "白先。白棋能在A点落子吗？",
        .options = level_045_options,
        .option_count = 2,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "自杀",
        .instruction = "白先。白棋能在A点落子吗？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_046_stones,
        .stone_count = 15,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "白先。白棋能在A点落子吗？",
        .options = level_046_options,
        .option_count = 2,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "劫",
        .instruction = "黑棋用1号棋子吃掉了标记为三角形的白棋。如果白棋提回后，棋盘局面与黑棋下1号棋子前完全相同，则此提回不被允许。白棋是否能立即提回1号棋子？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_047_stones,
        .stone_count = 11,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "黑棋用1号棋子吃掉了标记为三角形的白棋。如果白棋提回后，棋盘局面与黑棋下1号棋子前完全相同，则此提回不被允许。白棋是否能立即提回1号棋子？",
        .options = level_047_options,
        .option_count = 2,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "活棋",
        .instruction = "黑棋棋块是活棋吗？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_048_stones,
        .stone_count = 13,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "黑棋棋块是活棋吗？",
        .options = level_048_options,
        .option_count = 2,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "两眼",
        .instruction = "白先。做出两只眼。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_049_stones,
        .stone_count = 12,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_049_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "打吃至边",
        .instruction = "黑先。将带标记的白棋驱向棋盘边缘，可以更容易地吃掉它。选择落子点A或B，将带标记的白棋推向边缘。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_050_stones,
        .stone_count = 4,
        .mark_points = level_050_mark_points,
        .mark_glyphs = level_050_glyphs,
        .mark_count = 3,
        .correct = level_050_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "打吃棋子",
        .instruction = "黑先。将带标记的白棋驱向己方棋子，有助于吃掉这些棋子。对带标记的白棋进行打吃。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_051_stones,
        .stone_count = 12,
        .mark_points = level_051_mark_points,
        .mark_glyphs = level_051_glyphs,
        .mark_count = 2,
        .correct = level_051_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "打吃并切断",
        .instruction = "黑先。阻止白棋连接，并吃掉一颗或多颗白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_052_stones,
        .stone_count = 20,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_052_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "可逃跑",
        .instruction = "白先。白棋能否救出被标记的棋串？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_053_stones,
        .stone_count = 7,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "白先。白棋能否救出被标记的棋串？",
        .options = level_053_options,
        .option_count = 2,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "制造劫",
        .instruction = "白先。黑棋已下1。制造劫争。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_054_stones,
        .stone_count = 17,
        .mark_points = level_054_mark_points,
        .mark_glyphs = level_054_glyphs,
        .mark_count = 1,
        .correct = level_054_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "下双打吃",
        .instruction = "黑先。对带标记的白棋进行双打吃。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_055_stones,
        .stone_count = 12,
        .mark_points = level_055_mark_points,
        .mark_glyphs = level_055_glyphs,
        .mark_count = 3,
        .correct = level_055_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "连接形状",
        .instruction = "白先。确保黑棋无法再切断白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_056_stones,
        .stone_count = 13,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_056_correct,
        .correct_count = 3,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "虎口连接",
        .instruction = "白先。用虎口连接白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_057_stones,
        .stone_count = 11,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_057_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "征子",
        .instruction = "白先。用征子吃掉带标记的黑棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_058_stones,
        .stone_count = 9,
        .mark_points = level_058_mark_points,
        .mark_glyphs = level_058_glyphs,
        .mark_count = 2,
        .correct = level_058_correct,
        .correct_count = 2,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "气不够",
        .instruction = "黑先。利用白棋气不够吃掉带标记的白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_059_stones,
        .stone_count = 20,
        .mark_points = level_059_mark_points,
        .mark_glyphs = level_059_glyphs,
        .mark_count = 3,
        .correct = level_059_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "假眼",
        .instruction = "白先。阻止黑棋将白棋的眼做成假眼。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_060_stones,
        .stone_count = 13,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_060_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "大眼",
        .instruction = "白先。做成两个眼，使白棋块活棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_061_stones,
        .stone_count = 23,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_061_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "棋块活棋",
        .instruction = "黑棋的这个棋块活了吗？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_062_stones,
        .stone_count = 18,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "黑棋的这个棋块活了吗？",
        .options = level_062_options,
        .option_count = 2,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "倒扑",
        .instruction = "黑先。吃掉被标记的棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_063_stones,
        .stone_count = 22,
        .mark_points = level_063_mark_points,
        .mark_glyphs = level_063_glyphs,
        .mark_count = 3,
        .correct = level_063_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "罩",
        .instruction = "白先。用罩的方式吃掉被标记的棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_064_stones,
        .stone_count = 11,
        .mark_points = level_064_mark_points,
        .mark_glyphs = level_064_glyphs,
        .mark_count = 1,
        .correct = level_064_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "领地",
        .instruction = "白棋的地盘有多少目？注意：一个死子算两目。",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_065_stones,
        .stone_count = 27,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "白棋的地盘有多少目？注意：一个死子算两目。",
        .options = level_065_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "封锁领地",
        .instruction = "黑先。通过一手棋封闭黑棋领地。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_066_stones,
        .stone_count = 18,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_066_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "被标记的两个棋串都有两口气。白棋可以通过减少黑棋串的气来吃掉它。如果轮到黑棋走，黑棋也可以做同样的事情。这被称为'对杀'。如果双方气数相同，先落子的一方将赢得对杀。白先。赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_067_stones,
        .stone_count = 10,
        .mark_points = level_067_mark_points,
        .mark_glyphs = level_067_glyphs,
        .mark_count = 4,
        .correct = level_067_correct,
        .correct_count = 2,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "正确方向",
        .instruction = "黑先。通过正确方向的打吃来吃掉白棋串。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_068_stones,
        .stone_count = 10,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_068_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "正确方向",
        .instruction = "白先。通过正确方向的打吃来吃掉黑棋串。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_069_stones,
        .stone_count = 19,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_069_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "提子",
        .instruction = "黑先。在不使自己处于打吃状态的情况下吃掉白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_070_stones,
        .stone_count = 17,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_070_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "逃跑",
        .instruction = "白先。选择落子于A或B点，使被标记的棋子逃脱？",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_071_stones,
        .stone_count = 11,
        .mark_points = level_071_mark_points,
        .mark_glyphs = level_071_glyphs,
        .mark_count = 4,
        .correct = level_071_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "气数",
        .instruction = "白先。黑棋用第1手填塞了自己的气。惩罚这一着。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_072_stones,
        .stone_count = 17,
        .mark_points = level_072_mark_points,
        .mark_glyphs = level_072_glyphs,
        .mark_count = 1,
        .correct = level_072_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "一路",
        .instruction = "黑先。提掉第一线被标记的棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_073_stones,
        .stone_count = 13,
        .mark_points = level_073_mark_points,
        .mark_glyphs = level_073_glyphs,
        .mark_count = 2,
        .correct = level_073_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "打吃",
        .instruction = "你可以吃掉被标记的黑棋棋子，但你需要正确开始，在正确的一侧打吃。在落子前，试着计算后续着法。白先。吃掉被标记的黑棋棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_074_stones,
        .stone_count = 15,
        .mark_points = level_074_mark_points,
        .mark_glyphs = level_074_glyphs,
        .mark_count = 3,
        .correct = level_074_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "逃脱罗网",
        .instruction = "白先。黑棋意图用1号着法通过罩吃掉被标记的棋子。白棋可以尝试在A或B点落子逃跑。在这种情况下，其中一点是成功的。从这个罩中逃脱。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_075_stones,
        .stone_count = 16,
        .mark_points = level_075_mark_points,
        .mark_glyphs = level_075_glyphs,
        .mark_count = 5,
        .correct = level_075_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "计算逃脱",
        .instruction = "白先。标记的棋子能逃跑吗？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_076_stones,
        .stone_count = 11,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "白先。标记的棋子能逃跑吗？",
        .options = level_076_options,
        .option_count = 2,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "征子",
        .instruction = "有时你可以通过从正确的一侧开始来避免征子不利。黑棋可以选择在A或B点落子。通过选择正确的一侧，用征子吃掉被标记的棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_077_stones,
        .stone_count = 7,
        .mark_points = level_077_mark_points,
        .mark_glyphs = level_077_glyphs,
        .mark_count = 4,
        .correct = level_077_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "双打吃",
        .instruction = "白先。下出一步好的双打吃。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_078_stones,
        .stone_count = 17,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_078_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "罩",
        .instruction = "黑先。用罩吃掉被标记的棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_079_stones,
        .stone_count = 10,
        .mark_points = level_079_mark_points,
        .mark_glyphs = level_079_glyphs,
        .mark_count = 2,
        .correct = level_079_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "追击",
        .instruction = "黑先。通过追击吃掉棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_080_stones,
        .stone_count = 15,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_080_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "提子1",
        .instruction = "黑先。吃掉被标记的棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_081_stones,
        .stone_count = 17,
        .mark_points = level_081_mark_points,
        .mark_glyphs = level_081_glyphs,
        .mark_count = 2,
        .correct = level_081_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "提子2",
        .instruction = "白先。吃掉一或多颗黑棋棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_082_stones,
        .stone_count = 19,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_082_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "提子3",
        .instruction = "白先。吃掉一或多颗黑棋棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_083_stones,
        .stone_count = 14,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_083_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "提子4",
        .instruction = "黑先。吃掉一或多颗白棋棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_084_stones,
        .stone_count = 18,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_084_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "连接",
        .instruction = "黑先。连接被标记的棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_085_stones,
        .stone_count = 10,
        .mark_points = level_085_mark_points,
        .mark_glyphs = level_085_glyphs,
        .mark_count = 5,
        .correct = level_085_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "切断",
        .instruction = "白先。切断被标记的棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_086_stones,
        .stone_count = 15,
        .mark_points = level_086_mark_points,
        .mark_glyphs = level_086_glyphs,
        .mark_count = 7,
        .correct = level_086_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "眼",
        .instruction = "A是真眼还是假眼？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_087_stones,
        .stone_count = 20,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "A是真眼还是假眼？",
        .options = level_087_options,
        .option_count = 2,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "数眼",
        .instruction = "白棋棋块有几个真眼？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_088_stones,
        .stone_count = 24,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "白棋棋块有几个真眼？",
        .options = level_088_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "白先。请赢得标记棋块之间的对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_089_stones,
        .stone_count = 17,
        .mark_points = level_089_mark_points,
        .mark_glyphs = level_089_glyphs,
        .mark_count = 8,
        .correct = level_089_correct,
        .correct_count = 2,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "白先。请攻击正确的棋串并赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_090_stones,
        .stone_count = 25,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_090_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "制造双活",
        .instruction = "黑先。请下成双活并救出标记的棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_091_stones,
        .stone_count = 24,
        .mark_points = level_091_mark_points,
        .mark_glyphs = level_091_glyphs,
        .mark_count = 5,
        .correct = level_091_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "生死",
        .instruction = "白先。请阻止黑棋做出第二个眼，并吃掉黑棋块。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_092_stones,
        .stone_count = 12,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_092_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "生死",
        .instruction = "白先。请先做成一只眼，使白棋块活棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_093_stones,
        .stone_count = 21,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_093_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "生死",
        .instruction = "黑先。请吃掉白棋块。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_094_stones,
        .stone_count = 22,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_094_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "连续打吃",
        .instruction = "白先。请打吃并吃掉标记的棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_095_stones,
        .stone_count = 22,
        .mark_points = level_095_mark_points,
        .mark_glyphs = level_095_glyphs,
        .mark_count = 3,
        .correct = level_095_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "劫",
        .instruction = "白先。请制造一个劫。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_096_stones,
        .stone_count = 13,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_096_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "挡",
        .instruction = "黑先。白棋已落子1。挡住白棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_097_stones,
        .stone_count = 8,
        .mark_points = level_097_mark_points,
        .mark_glyphs = level_097_glyphs,
        .mark_count = 1,
        .correct = level_097_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "双活",
        .instruction = "黑棋有两只眼和6目（5目领地加1个提子）。然而，白棋可以通过在A点落子形成双活来取消这些目数。黑棋无法吃掉角上的两颗白子：如果黑棋在B点应，会让自己的棋子陷入打吃。白先，形成双活。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_098_stones,
        .stone_count = 18,
        .mark_points = level_098_mark_points,
        .mark_glyphs = level_098_glyphs,
        .mark_count = 2,
        .correct = level_098_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "追杀",
        .instruction = "黑先。追击标记的棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_099_stones,
        .stone_count = 26,
        .mark_points = level_099_mark_points,
        .mark_glyphs = level_099_glyphs,
        .mark_count = 4,
        .correct = level_099_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "罩",
        .instruction = "白先。用罩尽可能多地吃子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_100_stones,
        .stone_count = 17,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_100_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "提子 2",
        .instruction = "黑先。尽可能多地吃子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_101_stones,
        .stone_count = 20,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_101_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "扑 2",
        .instruction = "白先。用扑吃子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_102_stones,
        .stone_count = 13,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_102_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "连接",
        .instruction = "白先。连接白棋。选择最佳连接方式。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_103_stones,
        .stone_count = 10,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_103_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "角部 1",
        .instruction = "黑先。选择最佳角部封锁（缔角），A、B或C。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_104_stones,
        .stone_count = 1,
        .mark_points = level_104_mark_points,
        .mark_glyphs = level_104_glyphs,
        .mark_count = 3,
        .correct = level_104_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "防守 2",
        .instruction = "白先。黑棋走了1。防守白棋的领地。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_105_stones,
        .stone_count = 3,
        .mark_points = level_105_mark_points,
        .mark_glyphs = level_105_glyphs,
        .mark_count = 1,
        .correct = level_105_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "眼1",
        .instruction = "白先。通过扑入制造假眼。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_106_stones,
        .stone_count = 22,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_106_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "收官1",
        .instruction = "黑先。白棋已下第1手。防守黑棋的弱点。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_107_stones,
        .stone_count = 24,
        .mark_points = level_107_mark_points,
        .mark_glyphs = level_107_glyphs,
        .mark_count = 1,
        .correct = level_107_correct,
        .correct_count = 3,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "收官3",
        .instruction = "下在A点的价值是多少？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_108_stones,
        .stone_count = 28,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "下在A点的价值是多少？",
        .options = level_108_options,
        .option_count = 3,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "死活",
        .instruction = "白先。按正确的顺序做出两只眼。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_109_stones,
        .stone_count = 15,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_109_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "死活",
        .instruction = "白先。阻止形成3点眼位，使白棋的棋块活棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_110_stones,
        .stone_count = 17,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_110_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "死活",
        .instruction = "黑先。吃掉白棋的棋块。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_111_stones,
        .stone_count = 20,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_111_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "死活",
        .instruction = "黑先。吃掉白棋的棋块。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_112_stones,
        .stone_count = 18,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_112_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "劫",
        .instruction = "黑先。尝试用劫争吃掉标记的棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_113_stones,
        .stone_count = 16,
        .mark_points = level_113_mark_points,
        .mark_glyphs = level_113_glyphs,
        .mark_count = 4,
        .correct = level_113_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "行棋步法",
        .instruction = "白先。对黑1的弯曲，下出好的应手（延伸）。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_114_stones,
        .stone_count = 4,
        .mark_points = level_114_mark_points,
        .mark_glyphs = level_114_glyphs,
        .mark_count = 1,
        .correct = level_114_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "行棋步法",
        .instruction = "黑先。针对白棋标记的着法，选择最佳防守：A、B或C？",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_115_stones,
        .stone_count = 4,
        .mark_points = level_115_mark_points,
        .mark_glyphs = level_115_glyphs,
        .mark_count = 4,
        .correct = level_115_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "棋形",
        .instruction = "白棋的棋块是强形还是弱形？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_116_stones,
        .stone_count = 11,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "白棋的棋块是强形还是弱形？",
        .options = level_116_options,
        .option_count = 2,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "黑先。以有眼对无眼，赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_117_stones,
        .stone_count = 25,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_117_correct,
        .correct_count = 2,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "提子",
        .instruction = "白先。尽可能多吃掉棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_118_stones,
        .stone_count = 12,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_118_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "提子",
        .instruction = "黑先。尽可能多吃掉棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_119_stones,
        .stone_count = 18,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_119_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "提子",
        .instruction = "白先。在倒扑中尽可能多吃掉棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_120_stones,
        .stone_count = 27,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_120_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "定式",
        .instruction = "白先。在黑棋1之后，选择最佳着法：A、B或C。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_121_stones,
        .stone_count = 6,
        .mark_points = level_121_mark_points,
        .mark_glyphs = level_121_glyphs,
        .mark_count = 4,
        .correct = level_121_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "行棋方向",
        .instruction = "白先。在黑棋1之后选择最佳后续着法，A或B。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_122_stones,
        .stone_count = 2,
        .mark_points = level_122_mark_points,
        .mark_glyphs = level_122_glyphs,
        .mark_count = 3,
        .correct = level_122_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "双活",
        .instruction = "如果你想赢得对杀，你必须阻止对手制造双活。所以如果有可能形成双活，你应该小心应对。如果白棋在B位落子，黑棋可以在A位制造双活。为防止这种情况发生，白棋应在C位落子。白先。阻止双活并赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_123_stones,
        .stone_count = 18,
        .mark_points = level_123_mark_points,
        .mark_glyphs = level_123_glyphs,
        .mark_count = 3,
        .correct = level_123_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "技巧",
        .instruction = "白先。黑棋1之后，在A点落子是否是好的回应，还是脱先更好？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_124_stones,
        .stone_count = 12,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "白先。黑棋1之后，在A点落子是否是好的回应，还是脱先更好？",
        .options = level_124_options,
        .option_count = 2,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "技巧",
        .instruction = "黑先。在A点落子能加强黑棋棋块吗，还是脱先更好？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_125_stones,
        .stone_count = 18,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "黑先。在A点落子能加强黑棋棋块吗，还是脱先更好？",
        .options = level_125_options,
        .option_count = 2,
        .answer = 1,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "收官",
        .instruction = "黑先。选择最大的着法，A、B或C。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_126_stones,
        .stone_count = 38,
        .mark_points = level_126_mark_points,
        .mark_glyphs = level_126_glyphs,
        .mark_count = 3,
        .correct = level_126_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "假眼",
        .instruction = "白先。利用气的不足来制造一个假眼。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_127_stones,
        .stone_count = 18,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_127_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "死活",
        .instruction = "白先。通过下先手来使棋块活棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_128_stones,
        .stone_count = 23,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_128_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "死活",
        .instruction = "黑先。利用劫让黑棋棋块活棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_129_stones,
        .stone_count = 15,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_129_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "死活",
        .instruction = "黑先。吃掉白棋棋块；利用假眼。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_130_stones,
        .stone_count = 30,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_130_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "死活",
        .instruction = "黑先。吃掉白棋棋块。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_131_stones,
        .stone_count = 15,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_131_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "死活",
        .instruction = "白棋棋块的状态是什么？死棋、活棋，还是取决于谁先落子？",
        .kind = WQ_KIND_CHOICE,
        .player = 1,
        .stones = level_132_stones,
        .stone_count = 15,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = NULL,
        .correct_count = 0,
        .question = "白棋棋块的状态是什么？死棋、活棋，还是取决于谁先落子？",
        .options = level_132_options,
        .option_count = 3,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "黑先。通过增加气数或防止损失气数来赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_133_stones,
        .stone_count = 11,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_133_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "黑先。赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_134_stones,
        .stone_count = 24,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_134_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "黑先。赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_135_stones,
        .stone_count = 23,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_135_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "准备打吃",
        .instruction = "白先。经过准备性打吃后提子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_136_stones,
        .stone_count = 19,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_136_correct,
        .correct_count = 2,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "连接与切断",
        .instruction = "黑先。应对这个切断。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_137_stones,
        .stone_count = 15,
        .mark_points = level_137_mark_points,
        .mark_glyphs = level_137_glyphs,
        .mark_count = 1,
        .correct = level_137_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "定式",
        .instruction = "白棋在1下挂，黑棋在2下夹。白棋可以跳向中腹或在3跳入角部。在这个定式中，黑棋将白棋的1和3分断。用白棋下这个定式，从3开始。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_138_stones,
        .stone_count = 3,
        .mark_points = level_138_mark_points,
        .mark_glyphs = level_138_glyphs,
        .mark_count = 11,
        .correct = level_138_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "定式",
        .instruction = "黑先。选择白棋1之后A、B或C中最佳的应答。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_139_stones,
        .stone_count = 4,
        .mark_points = level_139_mark_points,
        .mark_glyphs = level_139_glyphs,
        .mark_count = 4,
        .correct = level_139_correct,
        .correct_count = 2,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "技巧",
        .instruction = "黑先。下劫争以获利。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_140_stones,
        .stone_count = 26,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_140_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "手筋",
        .instruction = "白先。尽可能多地吃掉黑棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_141_stones,
        .stone_count = 11,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_141_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "手筋",
        .instruction = "黑先。尽可能多地提掉白棋棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_142_stones,
        .stone_count = 28,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_142_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "手筋",
        .instruction = "白先。尽可能多地吃掉黑棋。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_143_stones,
        .stone_count = 25,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_143_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "手筋",
        .instruction = "黑先。走出最佳连接。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_144_stones,
        .stone_count = 23,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_144_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "手筋",
        .instruction = "白先。走出最佳连接。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_145_stones,
        .stone_count = 14,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_145_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "手筋",
        .instruction = "黑先。走出最佳连接。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_146_stones,
        .stone_count = 20,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_146_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "手筋",
        .instruction = "白先。切断黑棋棋子。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_147_stones,
        .stone_count = 19,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_147_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "白先。赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_148_stones,
        .stone_count = 24,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_148_correct,
        .correct_count = 2,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "白先。赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_149_stones,
        .stone_count = 21,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_149_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "黑先。赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_150_stones,
        .stone_count = 23,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_150_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "白先。赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_151_stones,
        .stone_count = 21,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_151_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "白先。赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 2,
        .stones = level_152_stones,
        .stone_count = 26,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_152_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
    {
        .title = "对杀",
        .instruction = "黑先。赢得对杀。",
        .kind = WQ_KIND_PUZZLE,
        .player = 1,
        .stones = level_153_stones,
        .stone_count = 25,
        .mark_points = NULL,
        .mark_glyphs = NULL,
        .mark_count = 0,
        .correct = level_153_correct,
        .correct_count = 1,
        .question = "",
        .options = NULL,
        .option_count = 0,
        .answer = 0,
        .targets = NULL,
        .target_count = 0,
    },
};

const wq_chapter_t wq_chapters[WQ_CHAPTER_COUNT] = {
    { "青铜 · 入门启蒙", 0, 30 },
    { "白银 · 气与提子", 30, 20 },
    { "黄金 · 吃子手筋", 50, 24 },
    { "铂金 · 死活初步", 74, 24 },
    { "钻石 · 眼位棋形", 98, 20 },
    { "星耀 · 劫与收官", 118, 20 },
    { "王者 · 高阶战术", 138, 16 },
};
