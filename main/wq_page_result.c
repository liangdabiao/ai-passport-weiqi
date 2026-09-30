// main/wq_page_result.c —— 结算页：星级、得分、错误数，以及「下一关」。
//
// 星级与网页版一致：0 错 3 星、1 错 2 星、2 错及以上 1 星；每星 100 分。
// 章末关在这里宣告「章节通关」，下一关的确认键把用户带进下一章（若有）。
#include "wq_app.h"

#include <stdio.h>
#include <string.h>

#include "wq_content.h"
#include "wq_ui.h"

// 版式：大字 42..80 / 星级 92..130 / 说明 150..170 / 提示在底栏。
#define RESULT_HEADLINE_Y 42
#define RESULT_HEADLINE_H 40
#define RESULT_STARS_Y    96
#define RESULT_STARS_H    38
#define RESULT_NOTE_Y     150
#define RESULT_NOTE_H     20
_Static_assert(RESULT_NOTE_Y + RESULT_NOTE_H <= WQ_BODY_H, "说明行超出正文区");

static lv_obj_t *s_hint;
static lv_obj_t *s_stars;

lv_obj_t *wq_page_result_enter(void)
{
    const wq_session_t *session = wq_app_session();
    s_hint = NULL;
    s_stars = NULL;

    lv_obj_t *card = NULL;
    lv_obj_t *screen = wq_page_create(&card);
    if (!card) return screen;

    wq_topbar_t bar = wq_topbar_create(card, "", &wq_font_16);
    const wq_level_t *level = wq_session_level(session);
    wq_topbar_set_left(&bar, level ? level->title : "");
    s_hint = wq_hint_create(card, "");
    lv_obj_t *body = wq_body_create(card);

    lv_obj_t *headline = wq_headline_create(body, WQ_BODY_X, RESULT_HEADLINE_Y,
                                             WQ_BODY_W, RESULT_HEADLINE_H,
                                             WQ_C_GOLD);
    lv_label_set_text(headline, "过关");

    s_stars = wq_headline_create(body, WQ_BODY_X, RESULT_STARS_Y, WQ_BODY_W,
                                 RESULT_STARS_H, WQ_C_GOLD_D);

    lv_obj_t *note = wq_note_create(body, WQ_BODY_X, RESULT_NOTE_Y, WQ_BODY_W, "",
                                    WQ_C_MUTED);

    const uint8_t stars = wq_session_result_stars(session);
    char stars_text[16];
    snprintf(stars_text, sizeof(stars_text), "%.*s%.*s",
             stars, "★★★", 3 - stars, "☆☆☆");
    lv_label_set_text(s_stars, stars_text);

    char note_text[64];
    const wq_chapter_t *chapter = &wq_chapters[session->chapter];
    const bool chapter_end =
        session->level + 1 >= (uint16_t)(chapter->first + chapter->count);
    if (session->wrong_count > 0) {
        snprintf(note_text, sizeof(note_text), "+%d 分 · 走错 %u 次%s",
                 stars * WQ_POINTS_PER_STAR, (unsigned)session->wrong_count,
                 chapter_end ? " · 章节通关！" : "");
    } else {
        snprintf(note_text, sizeof(note_text), "+%d 分 · 一次走错都没有%s",
                 stars * WQ_POINTS_PER_STAR,
                 chapter_end ? " · 章节通关！" : "");
    }
    lv_label_set_text(note, note_text);

    if (s_hint) {
        lv_label_set_text(s_hint, wq_session_has_next(session)
                                      ? "确定 下一关 · 长按 返回列表"
                                      : "确定 回到世界地图");
    }
    return screen;
}

void wq_page_result_leave(void)
{
    s_hint = NULL;
    s_stars = NULL;
}

void wq_page_result_key(wq_key_t key)
{
    wq_session_t *session = wq_app_session();

    switch (key) {
        case WQ_KEY_OK: {
            const wq_action_t action = wq_session_key(session, WQ_KEY_OK);
            if (action == WQ_ACT_ENTERED) {
                wq_app_goto_play();
            } else if (action == WQ_ACT_LEFT) {
                wq_app_goto_world();
            }
            return;
        }

        case WQ_KEY_BACK:
            session->stage = WQ_STAGE_LEVELS;
            wq_app_goto_levels();
            return;

        default:
            return;
    }
}
