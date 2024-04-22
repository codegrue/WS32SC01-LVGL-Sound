#include "main.h"

extern "C" void app_main(void)
{
	SerialHelpers::setupSerial();

	ESP_LOGI("", "setup");
	SerialHelpers::logHeapInfo("Startup");

	// setting up graphics systems
	Graphics::lovyanGFX_init();
	Graphics::LVGL_init();
	SerialHelpers::logHeapInfo("after Graphics::setup()");

	// setup support libraries
	UserInterface::setup();
	SerialHelpers::logHeapInfo("after UserInterface::setup()");

	// setup audio play
	Sound::setup();
	SerialHelpers::logHeapInfo("after Sound::setup()");

	// setup scheduled tasks
	RTOSTasks::setup();
	SerialHelpers::logHeapInfo("after RTOSTasks::setup()");
}

// void loop()
// {
// 	// RTOS calls tasks
// 	// nothing to do here
// }
