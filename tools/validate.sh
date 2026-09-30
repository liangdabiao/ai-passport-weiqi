#!/usr/bin/env bash
set -euo pipefail

mode="${1:---all}"
repo_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"

usage() {
    echo "Usage: $0 [--all|--static|--firmware]" >&2
}

run_static_checks() {
    local actionlint_bin
    local test_dir

    python3 tools/check_repo.py
    # 生成物与内容源必须同步：题库改了却忘了重新生成 C 表，在这里就失败。
    PYTHONDONTWRITEBYTECODE=1 python3 tools/weiqi/gen_content.py --check
    # 本应用没有音频资产（音效全靠 RTTTL 合成），没有 gen_audio 这一道。
    # 字库清单同理：新增界面文案或新增一道题后忘了重跑字库生成器，charset.txt
    # 就会与源文件脱节。这一步要 fontTools 才能逐个码点核对母字体覆盖，而 CI
    # 镜像不装 fontTools —— 缺依赖时明确跳过并说明，不假装通过。
    if python3 -c "import fontTools" >/dev/null 2>&1; then
        PYTHONDONTWRITEBYTECODE=1 python3 tools/weiqi/gen_font.py --check
    else
        echo "skip: tools/weiqi/gen_font.py --check（当前 python3 无 fontTools；字库清单同步未校验）" >&2
    fi

    actionlint_bin="${ACTIONLINT_BIN:-}"
    if [[ -z "${actionlint_bin}" ]]; then
        actionlint_bin="$(command -v actionlint || true)"
    fi
    if [[ -z "${actionlint_bin}" || ! -x "${actionlint_bin}" ]]; then
        actionlint_bin="$(./tools/install-actionlint.sh)"
    fi
    "${actionlint_bin}" -color .github/workflows/*.yml

    test_dir="$(mktemp -d /tmp/weiqi-host-tests.XXXXXX)"
    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror -Imain \
        tests/test_ui_pixel_math.c main/ui_pixel_math.c \
        -o "${test_dir}/test_ui_pixel_math"
    "${test_dir}/test_ui_pixel_math"
    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror -Imain \
        tests/test_demo_navigation.c main/demo_navigation.c \
        -o "${test_dir}/test_demo_navigation"
    "${test_dir}/test_demo_navigation"

    # 本应用的纯逻辑层：围棋规则引擎、关卡内容、闯关状态机、进度存档、
    # 音量档位与折行。它们刻意不依赖 ESP-IDF/LVGL，所以能在宿主机上直接跑。
    #
    # test_wq_engine 断言的是「C 引擎与 tools/weiqi/extract_levels.mjs 的校验器
    # 同一套规则」：气 / 提子 / 禁自杀 / 简单劫的单元用例 + 全题库正解路径重放。
    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror -Imain         tests/test_wq_engine.c main/wq_engine.c main/wq_content.c         -o "${test_dir}/test_wq_engine"
    "${test_dir}/test_wq_engine"

    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror -Imain         tests/test_wq_content.c main/wq_content.c         -o "${test_dir}/test_wq_content"
    "${test_dir}/test_wq_content"

    # 音量档位与缩放。它断言的是「基准值乘以默认档位」这一算术不被悄悄改动。
    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror -Imain         tests/test_wq_volume.c main/wq_volume.c         -o "${test_dir}/test_wq_volume"
    "${test_dir}/test_wq_volume"

    # test_wq_wrap 刻意连了 wq_content：它断言的是「真实题库里每段说明在真实
    # 每行字数预算下都折得进缓冲」，也就是「一屏放得下」这句话本身。
    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror -Imain         tests/test_wq_wrap.c main/wq_wrap.c main/wq_content.c         -o "${test_dir}/test_wq_wrap"
    "${test_dir}/test_wq_wrap"

    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror -Imain         tests/test_wq_session.c main/wq_session.c main/wq_engine.c main/wq_content.c         -o "${test_dir}/test_wq_session"
    "${test_dir}/test_wq_session"

    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror -Imain         tests/test_wq_progress.c main/wq_progress.c         -o "${test_dir}/test_wq_progress"
    "${test_dir}/test_wq_progress"

        tests/test_bsp_display_rounding.c components/bsp/src/bsp_display_rounding.c \
        -o "${test_dir}/test_bsp_display_rounding"
    "${test_dir}/test_bsp_display_rounding"
    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror -Icomponents/bsp/src \
        tests/test_bsp_es8311_sleep_check.c components/bsp/src/bsp_es8311_sleep_check.c \
        -o "${test_dir}/test_bsp_es8311_sleep_check"
    "${test_dir}/test_bsp_es8311_sleep_check"
    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror \
        -Itests/bsp_stubs -Icomponents/bsp/include \
        tests/test_bsp_button.c -o "${test_dir}/test_bsp_button"
    "${test_dir}/test_bsp_button"
    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror \
        -Itests/bsp_stubs -Icomponents/bsp/include \
        tests/test_bsp_lvgl_init.c components/bsp/src/bsp_display_rounding.c \
        -o "${test_dir}/test_bsp_lvgl_init"
    "${test_dir}/test_bsp_lvgl_init"
    "${CC:-cc}" -std=c11 -Wall -Wextra -Werror \
        -Itests/audio_stubs -Icomponents/bsp/include -Icomponents/bsp/src \
        tests/test_bsp_audio_recovery.c components/bsp/src/bsp_es8311_sleep_check.c \
        -o "${test_dir}/test_bsp_audio_recovery"
    "${test_dir}/test_bsp_audio_recovery"
    for demo in audio low_power ble wifi; do
        "${CC:-cc}" -std=c11 -Wall -Wextra -Werror \
            -ffunction-sections -fdata-sections -Itests/demo_stubs -Imain \
            "tests/test_demo_${demo}_runtime.c" -Wl,--gc-sections \
            -o "${test_dir}/test_demo_${demo}_runtime"
        "${test_dir}/test_demo_${demo}_runtime"
    done
    PYTHONDONTWRITEBYTECODE=1 python3 tests/test_deep_sleep_contract.py
    PYTHONDONTWRITEBYTECODE=1 python3 tests/test_check_repo.py
    PYTHONDONTWRITEBYTECODE=1 python3 tests/test_verify_firmware.py
    PYTHONDONTWRITEBYTECODE=1 python3 tests/test_archive_firmware.py
    PYTHONDONTWRITEBYTECODE=1 python3 tests/test_install_passport_skills.py
    rm -rf "${test_dir}"
    echo "Host tests: PASS"
}

run_firmware_checks() (
    local validation_build_dir

    if ! command -v idf.py >/dev/null 2>&1; then
        echo "ERROR: idf.py is not available; activate ESP-IDF 5.5.3 first." >&2
        return 1
    fi

    validation_build_dir="$(mktemp -d /tmp/weiqi-firmware.XXXXXX)"
    trap 'case "${validation_build_dir}" in /tmp/weiqi-firmware.*) rm -rf -- "${validation_build_dir}" ;; esac' EXIT

    SDKCONFIG_DEFAULTS="${repo_root}/sdkconfig.defaults" \
        idf.py -B "${validation_build_dir}" \
        -D "SDKCONFIG=${validation_build_dir}/sdkconfig" build
    idf.py -B "${validation_build_dir}" merge-bin \
        -o "${validation_build_dir}/FoloToy-AI-Passport-full.bin"
    python3 tools/verify_firmware.py "${validation_build_dir}"
    PYTHONDONTWRITEBYTECODE=1 python3 tools/archive_firmware.py create \
        "${validation_build_dir}" --archive-root "${repo_root}/build/firmware"
    mkdir -p "${repo_root}/build"
    install -m 0644 \
        "${validation_build_dir}/FoloToy-AI-Passport-full.bin" \
        "${repo_root}/build/FoloToy-AI-Passport-full.bin"
    echo "Firmware build: PASS"
)

cd "${repo_root}"
case "${mode}" in
    --all)
        run_static_checks
        run_firmware_checks
        ;;
    --static)
        run_static_checks
        ;;
    --firmware)
        run_firmware_checks
        ;;
    *)
        usage
        exit 2
        ;;
esac
