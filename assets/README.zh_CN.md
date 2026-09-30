<p align="right">
  <strong>简体中文</strong> · <a href="README.md">English</a>
</p>

# 资产

固件里代码之外的一切。本应用**只发布字体** —— 没有音频资产（音效是运行时合成的
RTTTL，见 `main/wq_sfx.c`），也没有位图图片（棋盘由控件直接绘制，见 `main/wq_ui.c`）。

| 文件 | 是什么 | 出处 |
| --- | --- | --- |
| [`fonts/charset.txt`](fonts/charset.txt) | 推导出来的字符清单：一段注释头 + 全部码点 | `tools/weiqi/gen_font.py` 生成；请勿手改 |
| [`fonts/wq_font_16.c`](fonts/wq_font_16.c) | 16px LVGL 字库子集 | 生成物；Noto Sans CJK SC，SIL OFL 1.1 |
| [`fonts/wq_font_24.c`](fonts/wq_font_24.c) | 24px LVGL 字库子集 | 生成物；Noto Sans CJK SC，SIL OFL 1.1 |
| [`fonts/wq_font_32.c`](fonts/wq_font_32.c) | 32px LVGL 字库子集 | 生成物；Noto Sans CJK SC，SIL OFL 1.1 |

## 清单是怎么推导的

`tools/weiqi/gen_font.py` 把三处来源并在一起，所以字库永远不会与关卡或界面文案脱节：
每一关的每个字（走 `tools/weiqi/content.py`，与 `gen_content.py` 同一个模块）、`main/`
下所有字符串字面量里的非 ASCII 字符（先剥注释）、以及固定基底（可打印 ASCII +
界面标点 + 星级星号与棋盘标记等符号）。转换之前每个码点都会对母字体的 cmap 核对
一次 —— 缺字形是构建期错误，不是设备上的一个空框。

`gen_font.py --check` 会重新推导清单、并解析已生成的 `.c`（读它的稀疏 cmap 表）核对
每个码点真的在字库里；`tools/validate.sh` 在静态门禁里跑它。

## 母字体

Noto Sans CJK SC Regular，SHA-256
`2c76254f6fc379fddfce0a7e84fb5385bb135d3e399294f6eeb6680d0365b74b`，
SIL Open Font License 1.1 —— 该许可允许子集化并随固件再分发。下载地址与转换命令
见 `tools/weiqi/gen_font.py`。

## 关卡内容

关卡数据本身由 `tools/weiqi/levels.txt`（事实源）经 `tools/weiqi/gen_content.py`
编译进固件。它的出处 —— 抽取自哪个 AGPL-3.0 网页游戏、9x9 裁剪规则 —— 记录在
应用档案 [`docs/reference/liangdabiao/weiqi-quest/README.zh_CN.md`](../docs/reference/liangdabiao/weiqi-quest/README.zh_CN.md)
与 `tools/weiqi/levels.txt` 的头部注释里。
