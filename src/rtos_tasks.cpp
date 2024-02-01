#include "rtos_tasks.h"

extern lv_point_t g_touchCoordinate;

// Create RTOS objects
// https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos_idf.html
TaskHandle_t tLVGLTimerHandle;
TaskHandle_t tSoundTimerHandle;

void RTOSTasks::setup()
{
    ESP_LOGI("", "RTOSTasks::setup");

    xTaskCreate(lvglCallback, "tLVGLTimer", RTOS_LVGL_STACK_SIZE, (void *)0, RTOS_LVGL_PRIORITY, &tLVGLTimerHandle);
    xTaskCreatePinnedToCore(soundCallback, "tSoundTimer", RTOS_SOUND_STACK_SIZE, (void *)0, RTOS_SOUND_PRIORITY, &tSoundTimerHandle, 0);
}

/*============================
     TASK SCHEDULER CALLBACKS
 *============================*/

// this gets called to give the LVGL
// graphics engine a chance to update the screen
void RTOSTasks::lvglCallback(void *p)
{
    while (1)
    {
        lv_timer_handler();

        vTaskDelay(LVGL_CALLBACK_INTERVAL);
    }
}

// this gets called to move audio into
// the I2S buffer for the speaker
void RTOSTasks::soundCallback(void *p)
{
    while (1)
    {
        Sound::loop();

        vTaskDelay(SOUND_CALLBACK_INTERVAL);
    }
}
