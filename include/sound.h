#ifndef SOUND_H
#define SOUND_H

#include "AudioTools.h"
#include "serial_helpers.h"

#define I2S_DOUT 37
#define I2S_BCLK 36
#define I2S_LRC 35

// How to create audio memory streams
// https://github.com/pschatzmann/arduino-audio-tools/wiki/MemoryStream:-Converting-a-File-to-Flash-Memory
// In Audacity:
//      - export WAV, Mono, 22050 Hz, Signed 16-bit PCM

namespace Sound
{
    void setup();
    void play();
    void loop();
}

#endif