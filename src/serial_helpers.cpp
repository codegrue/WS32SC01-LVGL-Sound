#include "serial_helpers.h"
#include "user_interface.h"

char *stack_start;

bool isSerialAvailable = false;

void SerialHelpers::setupSerial()
{
  Serial.begin(DEFAULT_BAUD_RATE);

  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  delay(1000); // allow serial to start

  ESP_LOGI("-----", "Program Start");

  isSerialAvailable = true;
}

void SerialHelpers::logHeapInfo(string context)
{
  ESP_LOGI("HEAP/PSRAM", "%s: %d / %d", context.c_str(), ESP.getFreeHeap(), ESP.getFreePsram());
}
