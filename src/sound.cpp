#include "sound.h"

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

void Sound::setup()
{
    ESP_LOGI("", "Sound::setup()");

    aac = new AudioGeneratorAAC();
    out = new AudioOutputI2S();
    out->SetPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
}

void Sound::play()
{
    ESP_LOGI("", "Sound::play()");

    in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));
    aac->begin(in, out);
}

void Sound::loop()
{
    // ESP_LOGW("IsPlaying", "%d", aac->isRunning());

    if (aac->isRunning())
    {
        aac->loop();
    }
}
