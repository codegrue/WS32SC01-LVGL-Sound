#ifndef SOUND_H
#define SOUND_H

#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"

#include "sounds/sampleaac.h"

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