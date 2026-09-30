idf_component_register(
    SRCS "main.c"
         # 应用与页面
         "wq_app.c"
         "wq_page_title.c"
         "wq_page_world.c"
         "wq_page_levels.c"
         "wq_page_play.c"
         "wq_page_result.c"
         "wq_ui.c"
         # 纯逻辑：与 ESP-IDF/LVGL 解耦，宿主测试直接编译这些文件
         "wq_session.c"
         "wq_engine.c"
         "wq_progress.c"
         "wq_content.c"
         "wq_wrap.c"
         "wq_volume.c"
         # 服务
         "wq_store.c"
         "wq_sfx.c"
         # 音效合成（RTTTL，不依赖任何音频素材）。本应用没有 BGM 也没有配音，
         # I2S 出口只有这一个写入者，不存在侨批「两个写入者交错写 DMA」的问题。
         "rtttl_player.c"
    INCLUDE_DIRS "."
    # 本应用只用 BSP、NVS 与定时器。基线 demo 的蓝牙/Wi-Fi/网络组件不再被引用；
    # 基线 demo 的源码仍留在 main/ 里作参考，只是不参与本应用的构建。
    REQUIRES bsp esp_event esp_hw_support esp_timer nvs_flash
)

# 中文字库由 tools/weiqi/gen_font.py 生成到 assets/fonts/，按官方推荐方式作为
# main 组件的额外源文件编译进来。只用这一条路径，不要再把同一个 .c 同时加进
# SRCS，也不要被别的 .c 直接 include。
target_sources(${COMPONENT_LIB} PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/../assets/fonts/wq_font_16.c"
    "${CMAKE_CURRENT_LIST_DIR}/../assets/fonts/wq_font_24.c"
    "${CMAKE_CURRENT_LIST_DIR}/../assets/fonts/wq_font_32.c"
)
