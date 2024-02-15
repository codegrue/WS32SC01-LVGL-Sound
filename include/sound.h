#ifndef SOUND_H
#define SOUND_H

#include "AudioTools.h"
#include "serial_helpers.h"

#define I2S_DOUT 37
#define I2S_BCLK 36
#define I2S_LRC 35

#define AUDIO_CHANNELS 1 // mono
#define SAMPLE_RATE 22050
#define BITS_PER_SAMPLE 16

namespace Sound
{
    void setup();
    void play();
    void stop();
    void loop();
}

#endif