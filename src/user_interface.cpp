#include "user_interface.h"
#include "sound.h"

static int counter = 0;
lv_obj_t *counterLabel;

void _custom_lvgl_logger(const char *buf)
{
    ESP_LOGE("LVGL", "%S", buf);
}

void UserInterface::setup()
{
    ESP_LOGI("", "UserInterface::setup()");

    lv_log_register_print_cb(_custom_lvgl_logger);

    auto screen = lv_scr_act();
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x444444), LV_PART_MAIN);

    auto widgetPanel = lv_obj_create(screen);
    lv_obj_set_width(widgetPanel, 480);
    lv_obj_set_height(widgetPanel, 320);
    lv_obj_set_style_bg_opa(widgetPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_flex_flow(widgetPanel, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(widgetPanel, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);
    lv_obj_set_style_pad_left(widgetPanel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(widgetPanel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(widgetPanel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(widgetPanel, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(widgetPanel, LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t *titleLabel = lv_label_create(widgetPanel);
    lv_label_set_text(titleLabel, "Hello WT32SC01\nLVGL + Sound");
    lv_obj_set_style_text_font(titleLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(titleLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_flag(titleLabel, LV_OBJ_FLAG_EVENT_BUBBLE);

    counterLabel = lv_label_create(widgetPanel);
    lv_label_set_text(counterLabel, String(counter).c_str());
    lv_obj_set_style_text_font(counterLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(counterLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_add_flag(counterLabel, LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t *incrementButton = lv_btn_create(widgetPanel);
    lv_obj_add_event_cb(incrementButton, increment_counter, LV_EVENT_CLICKED, NULL);
    lv_obj_t *incrementButtonLabel = lv_label_create(incrementButton);
    lv_label_set_text(incrementButtonLabel, "Increment");
    lv_obj_set_style_text_font(incrementButtonLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(incrementButton, LV_OBJ_FLAG_EVENT_BUBBLE);

    lv_obj_t *playSoundButton = lv_btn_create(widgetPanel);
    lv_obj_add_event_cb(playSoundButton, play_sound, LV_EVENT_CLICKED, NULL);
    lv_obj_t *playSoundButtonLabel = lv_label_create(playSoundButton);
    lv_label_set_text(playSoundButtonLabel, "Play Sound");
    lv_obj_set_style_text_font(playSoundButtonLabel, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(playSoundButton, LV_OBJ_FLAG_EVENT_BUBBLE);
}

void UserInterface::increment_counter(lv_event_t *event)
{
    ESP_LOGI("", "increment_counter");

    counter++;
    lv_label_set_text(counterLabel, String(counter).c_str());
}

void UserInterface::play_sound(lv_event_t *event)
{
    ESP_LOGI("", "play_sound");

    Sound::play();
}