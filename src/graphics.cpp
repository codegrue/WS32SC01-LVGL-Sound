#include "graphics.h"

extern lv_point_t g_touchCoordinate;

LGFX::LGFX(void)
{
    // Configure bus control settings.
    auto bus = _bus_instance.config(); // Get a structure for bus settings.
    bus.freq_write = 20000000;         // Transmit clock (up to 20MHz, rounded to the value obtained by dividing 80MHz by an integer)
    bus.pin_wr = 47;                   // Pin number connecting WR
    bus.pin_rd = -1;                   // Pin number connecting RD
    bus.pin_rs = 0;                    // Pin number connecting RS(D/C)
    bus.pin_d0 = 9;                    // 8 bit settings
    bus.pin_d1 = 46;
    bus.pin_d2 = 3;
    bus.pin_d3 = 8;
    bus.pin_d4 = 18;
    bus.pin_d5 = 17;
    bus.pin_d6 = 16;
    bus.pin_d7 = 15;
    _bus_instance.config(bus);              // Applies the set value to the bus.
    _panel_instance.setBus(&_bus_instance); // Set the bus on the panel.

    // Configure the display panel control.
    auto panel = _panel_instance.config(); // Gets the structure for display panel settings.
    panel.pin_cs = -1;                     // CS to be pulled low
    panel.pin_rst = 4;                     // RST is connected to the development board RST
    panel.pin_busy = -1;                   // Pin number to which BUSY is connected (-1 = disable)
    panel.panel_width = SCREEN_HEIGHT;     // actual displayable width
    panel.panel_height = SCREEN_WIDTH;     // actual visible height
    panel.offset_x = 0;                    // Panel offset amount in X direction
    panel.offset_y = 0;                    // Panel offset amount in Y direction
    panel.offset_rotation = 0;             // Rotation direction value offset 0~7 (4~7 is upside down)
    panel.dummy_read_pixel = 8;            // Number of bits for dummy read before pixel readout
    panel.dummy_read_bits = 1;             // Number of bits for dummy read before non-pixel data read
    panel.readable = true;                 // Set to true if data can be read
    panel.invert = true;                   // Set to true if the light/darkness of the panel is reversed
    panel.rgb_order = false;               // Set to true if the panel's red and blue are swapped
    panel.dlen_16bit = false;              // Set to true for panels that send data length in 16-bit units
    panel.bus_shared = true;               // If the bus is shared with the SD card, set to true (bus control with drawJpgFile etc.)
    _panel_instance.config(panel);

    // configure backlight
    auto backlight = _light_instance.config(); // Gets a structure for backlight settings.
    backlight.pin_bl = 45;                     // Pin number to which the backlight is connected
    backlight.invert = false;                  // true to reverse backlight brightness
    backlight.freq = 44100;                    // Backlight PWM frequency
    backlight.pwm_channel = 7;                 // The channel number of the PWM to be used.
    _light_instance.config(backlight);
    _panel_instance.setLight(&_light_instance);

    // configure touch panel
    auto touchCfg = touch_instance.config();
    touchCfg.x_min = 0;                 // Smallest X value (raw value) obtained from a touch screen
    touchCfg.x_max = SCREEN_HEIGHT - 1; // Maximum X value (raw value) obtained from a touchscreen
    touchCfg.y_min = 0;                 // Smallest Y value (raw value) obtained from a touchscreen
    touchCfg.y_max = SCREEN_WIDTH - 1;  // Maximum Y value (raw value) obtained from the touch screen
    touchCfg.pin_int = 7;               // Pin number to which INT is connected
    touchCfg.bus_shared = true;         // Set to true if you are using a common bus with the screen
    touchCfg.offset_rotation = 0;       // Adjustment when display and touch orientation do not match Set with a value of 0~7
    // For I2C connections
    touchCfg.i2c_port = 1;    // Select I2C to use (0 or 1)
    touchCfg.i2c_addr = 0x38; // I2C Device Address Number
    touchCfg.pin_sda = 6;     // Pin number to which the SDA is connected
    touchCfg.pin_scl = 5;     // Pin number to which the SCL is connected
    touchCfg.freq = 400000;   // Set the I2C Clock

    touch_instance.config(touchCfg);
    _panel_instance.touch(&touch_instance);

    setPanel(&_panel_instance); // Sets the panel to use.
}

LGFX lcd;

/*** Display callback to flush the buffer to screen ***/
void Graphics::display_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    lcd.startWrite();
    lcd.setAddrWindow(area->x1, area->y1, w, h);
    lcd.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
    lcd.endWrite();

    lv_disp_flush_ready(disp);
}

/*** Touchpad callback to read the touchpad ***/
void Graphics::touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    lgfx::touch_point_t tp;
    int touched = lcd.getTouch(&tp);

    if (touched == 1)
    {
        data->state = LV_INDEV_STATE_PR;

        int touch_x = tp.x;
        int touch_y = tp.y;

        /*Set the coordinates*/
        data->point.x = touch_x;
        data->point.y = touch_y;

        // store last touched coordinate for diagnostics
        g_touchCoordinate = data->point;

        // Print coordinates, for debugging
        // Serial.println("True  = (" + string(touch_x) + " | " + string(touch_y) + ")");
        // Serial.println("Calib = [" + string(calibrated_x) + " | " + string(calibrated_y) + "]");
        // Serial.println("-----");
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
}

void Graphics::LVGL_init()
{
    ESP_LOGI("", "_LVGL_init");

    lv_init();

    // set up the display buffer
    lv_disp_draw_buf_init(&draw_buf, buf, buf2, bufferSize);

    // Set up LVGL screen draw handler
    static lv_disp_drv_t disp_drv;               /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                 /*Basic initialization*/
    disp_drv.flush_cb = Graphics::display_flush; /*Set your driver function*/
    disp_drv.draw_buf = &draw_buf;               /*Assign the buffer to the display*/
    disp_drv.hor_res = SCREEN_WIDTH;             /*Set the horizontal resolution of the display*/
    disp_drv.ver_res = SCREEN_HEIGHT;            /*Set the vertical resolution of the display*/
    lv_disp_drv_register(&disp_drv);             /*Finally register the driver*/

    // Set up LVGL screen touch handler
    static lv_indev_drv_t indev_drv;             /*Descriptor of a input device driver*/
    lv_indev_drv_init(&indev_drv);               /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;      /*Touch pad is a pointer-like device*/
    indev_drv.read_cb = Graphics::touchpad_read; /*Set your driver function*/
    lv_indev_drv_register(&indev_drv);           /*Finally register the driver*/
}

void Graphics::lovyanGFX_init()
{
    ESP_LOGD("", "_lovyanGFX_init");

    lcd.init();
    lcd.setRotation(1);
}

void Graphics::set_brightness(int brightness)
{
    lcd.setBrightness(brightness);
}
