#include "sound.h"

#include "sounds/beep1.h"
#include "sounds/beep2.h"

uint8_t channels = 2;
uint16_t sample_rate = 22050;

I2SConfig config;
MemoryStream sound1(beep1_wav, sizeof(beep1_wav));
MemoryStream sound2(beep2_wav, sizeof(beep2_wav));
I2SStream out; // Output to I2S
StreamCopy copier;

bool even = false;

void Sound::setup()
{
    ESP_LOGI("", "Sound::setup()");

    AudioLogger::instance().begin(Serial, AudioLogger::Info);

    config = out.defaultConfig(TX_MODE);
    config.sample_rate = sample_rate;
    config.channels = channels;
    config.bits_per_sample = 16;
    config.pin_bck = I2S_BCLK;
    config.pin_data = I2S_DOUT;
    config.pin_ws = I2S_LRC;
    out.begin(config);
}

void Sound::play()
{
    ESP_LOGI("", "Sound::play()");

    if (even)
    {
        sound1.begin();
        copier.begin(out, sound1);
    }
    else
    {
        sound2.begin();
        copier.begin(out, sound2);
    }
    even = !even;
}

void Sound::loop()
{
    copier.copy();
}
