// LCD interface: MCU8080 8Bit
// LCD Driver: ST7796UI
// Touch Panel: Capacitive
// Touch Driver: FT6336U
// Touch Interface: I2C

#include <LovyanGFX.hpp>
#include <LVGL.h>

// screen values
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 320

// Calibration extents
#define TOUCH_X_MIN 10
#define TOUCH_X_MAX 470
#define TOUCH_Y_MIN 10
#define TOUCH_Y_MAX 310

class LGFX : public lgfx::LGFX_Device
{
    lgfx::Panel_ST7796 _panel_instance;
    lgfx::Bus_Parallel8 _bus_instance; // 8-bit parallel bus instance (ESP32 only)
    lgfx::Touch_FT5x06 touch_instance;
    lgfx::Light_PWM _light_instance;

public:
    LGFX(void);
};

namespace Graphics
{
    void LVGL_init();
    void lovyanGFX_init();
    void set_brightness(int brightness);
}
