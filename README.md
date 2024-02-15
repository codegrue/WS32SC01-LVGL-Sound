![alt text](https://raw.githubusercontent.com/codegrue/WS32SC01-LVGL-Sound/main/images/sample.png)

This sample demonstrates how to run LVGL on the
Panlee WT32SC01 Plus development board. It includes a label, a counter, and
a button to increment the value.

![alt text](https://raw.githubusercontent.com/codegrue/WS32SC01-LVGL-Sound/main/images/board.png)

Board:
https://www.aliexpress.us/item/3256804081022016.html?spm=a2g0o.order_detail.order_detail_item.3.5074f19cbai5dc&gatewayAdapt=glo2usa


Manufacturer:
https://wireless-tag.en.alibaba.com/

None of the included samples did a good job at packaging a runnable
demo, so I created this one in PlatformIO (VSCode) to provide
an out of the box runnable demo. Hope it is useful.

Notes:
- It uses LovyanGFX to buffer the drawing and dump to the screen
- lv_conf.h only has two changes: 
        - enabled LV_TICK_CUSTOM 
        - activated LV_FONT_MONTSERRAT_24
        - enabled LV_USE_LOG and set the level to LV_LOG_LEVEL_ERROR
- it uses a custom "WT32SC01" in the "Boards" folder because this doesn't exist in the PlatformIO library
- graphics.h encapselates the boilerplate code for LovyanGFX and LVGL
- user_interface.h encapselates the UI functions
- main.cpp is clean with just the normal setup() and loop() functions
