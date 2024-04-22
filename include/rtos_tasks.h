#ifndef RTOS_TASKS_H
#define RTOS_TASKS_H

// #include <FreeRTOS.h>
#include "user_interface.h"
#include "sound.h"

// FreeRTOS delay intervals
#define RTOS_MILLISECOND_INTERVAL 1 / portTICK_PERIOD_MS      // 1 millisecond
#define RTOS_SECOND_INTERVAL 1000 * RTOS_MILLISECOND_INTERVAL // 1 second
#define RTOS_MINUTE_INTERVAL 60 * RTOS_SECOND_INTERVAL        // 1 minute
#define RTOS_HOUR_INTERVAL 60 * RTOS_MINUTE_INTERVAL          // 1 hour

#define STATE_CALLBACK_INTERVAL 1 * RTOS_SECOND_INTERVAL         // 1 second
#define LVGL_CALLBACK_INTERVAL 1 * RTOS_MILLISECOND_INTERVAL     // 5 miliseconds
#define TIME_CALLBACK_INTERVAL 1 * RTOS_SECOND_INTERVAL          // 1 second
#define DIMMING_CALLBACK_INTERVAL 1 * RTOS_SECOND_INTERVAL       // 1 second
#define STATUS_CALLBACK_INTERVAL 1 * RTOS_SECOND_INTERVAL        // 3 seconds
#define WEATHER_CALLBACK_INTERVAL 1 * RTOS_SECOND_INTERVAL       // 1 second
#define FIRMWARE_UPDATE_CALLBACK_INTERVAL 1 * RTOS_HOUR_INTERVAL // 1 hour (but the task only functions after midnight)
#define SOUND_CALLBACK_INTERVAL 1 * RTOS_MILLISECOND_INTERVAL    // 1 second

// FreeRTOS stack sizes
// Note: too much total stack will cause memory errors
// in the HTTPClient calls, specifically "Failed to allocate buf"
#define RTOS_STACK_UNIT 1024
#define RTOS_APP_STATE_STACK_SIZE 7000   // this is high due to the firmware update, can be reduced to 5000 if that is refactored
#define RTOS_LVGL_STACK_SIZE 8000        // heap is allocated in lv_conf.h
#define RTOS_UPDATE_TIME_STACK_SIZE 3700 // usage logged at 3144
#define RTOS_DIMMING_STACK_SIZE 3000     // 3000 seems to be the minimum
#define RTOS_SOUND_STACK_SIZE 4 * RTOS_STACK_UNIT
#define RTOS_UPDATE_STATUS_STACK_SIZE 4 * RTOS_STACK_UNIT
#define RTOS_UPDATE_WEATHER_STACK_SIZE 6000
#define RTOS_UPDATE_NETWORKS_STACK_SIZE 5000
#define RTOS_FIRMWARE_UPDATE_STACK_SIZE 8000
#define RTOS_DIAGNOSTICS_STACK_SIZE 3000 // 3000 seems to be the minimum

// FreeRTOS priorites
#define RTOS_APP_STATE_PRIORITY tskIDLE_PRIORITY
#define RTOS_LVGL_PRIORITY tskIDLE_PRIORITY + 2
#define RTOS_UPDATE_TIME_PRIORITY tskIDLE_PRIORITY
#define RTOS_DIMMING_PRIORITY tskIDLE_PRIORITY
#define RTOS_UPDATE_STATUS_PRIORITY tskIDLE_PRIORITY
#define RTOS_UPDATE_WEATHER_PRIORITY tskIDLE_PRIORITY
#define RTOS_UPDATE_NETWORKS_PRIORITY tskIDLE_PRIORITY
#define RTOS_FIRMWARE_UPDATE_PRIORITY tskIDLE_PRIORITY
#define RTOS_DIAGNOSTICS_PRIORITY tskIDLE_PRIORITY
#define RTOS_SOUND_PRIORITY tskIDLE_PRIORITY + 1

// Weather countdown amounts
#define WEATHER_COUNTDOWN_SECONDS_LONG 20 * 60  // 20 minutes (GetSecondsUntilNext10MinuteMark used instead)
#define WEATHER_COUNTDOWN_SECONDS_MEDIUM 5 * 60 // 5 minute
#define WEATHER_COUNTDOWN_SECONDS_SHORT 2 * 60  // 2 minute

#define RTOS_MEMORY_SAMPLE_INTERVAL 10 // seconds
#define RTOS_LOW_STACK_THRESHOLD 500   // bytes
#define RTOS_HIGH_STACK_THRESHOLD 5000 // bytes

// use mutex to insure nothing writes to LVGL during the render
#define lvglMutex(x)                                                    \
    do                                                                  \
    {                                                                   \
        if (xSemaphoreTake(xLVGLMutexHandle, (TickType_t)10) == pdTRUE) \
        {                                                               \
            {x};                                                        \
            xSemaphoreGive(xLVGLMutexHandle);                           \
        }                                                               \
    } while (0);

// Callbacks
namespace RTOSTasks
{
    void setup();
    void logStackUsage(time_t *lastRun, const char *tag);

    // timer callbacks
    void timeCallback(void *p);
    void dimmingCallback(void *p);
    void lvglCallback(void *p);
    void statusBarCallback(void *p);
    void weatherCallback(void *p);
    void checkFirmwareUpdateCallback(void *p);
    void soundCallback(void *p);

    // add hoc async tasks
    void startStateMachineAsync();
    void loadNetworksTask(void *p);
    void loadNetworksAsync();
    void connectToWiFiTask(void *p);
    void connectToWiFiAsync();
    void runDiagnosticsAsync();
    void runDiagnosticsTask(void *p);
    void stopDiagnosticsTask();

}

#endif