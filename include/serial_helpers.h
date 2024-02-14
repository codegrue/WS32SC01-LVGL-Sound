#ifndef SERIAL_HELPERS_H
#define SERIAL_HELPERS_H

#include <Arduino.h>
#include <string>

using std::string;

#define DEFAULT_BAUD_RATE 115200


namespace SerialHelpers
{
    void setupSerial();
    void logHeapInfo(string context);
}

#endif