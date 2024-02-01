#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <Arduino.h>
#include <LVGL.h>

namespace UserInterface
{
    void setup();
    void increment_counter(lv_event_t *event);
    void play_sound(lv_event_t *event);
}

#endif