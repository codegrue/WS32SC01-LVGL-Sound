#ifndef SOUND_H
#define SOUND_H

#include "AudioTools.h"
#include "serial_helpers.h"

#define I2S_DOUT 37
#define I2S_BCLK 36
#define I2S_LRC 35

namespace Sound
{
    void setup();
    void play();
    void loop();
}

#endif