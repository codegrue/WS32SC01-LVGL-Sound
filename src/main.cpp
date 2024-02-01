#include "main.h"

void setup()
{
	Serial.begin(115200);
	delay(1000); // allow serial to start

	ESP_LOGI("", "setup");

	// setting up hardware systems
	Graphics::lovyanGFX_init();
	Graphics::LVGL_init();

	// setup support libraries
	UserInterface::setup();

	// setup audio play
	Sound::setup();

	// setup scheduled tasks
	RTOSTasks::setup();
}

void loop()
{
	// RTOS calls tasks
	// nothing to do here
}
