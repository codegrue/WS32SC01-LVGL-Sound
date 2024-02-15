#include "sound.h"

#include "sounds/beep1.h"
#include "sounds/beep2.h"

// How to create audio memory streams
// https://github.com/pschatzmann/arduino-audio-tools/wiki/MemoryStream:-Converting-a-File-to-Flash-Memory
// In Audacity:
//      - export WAV, Mono, 22050 Hz, Signed 16-bit PCM
// In VSCode bash terminal
//      - xxd -i file.wav file.h
//      - add 'const' keyword to object
uint8_t channels = 1;
uint16_t sample_rate = 22050;

// Caution: make sure the audio files are 'const' so they stay in PROMEM
MemoryStream sound1(beep1_wav, sizeof(beep1_wav), true, FLASH_RAM);
MemoryStream sound2(beep2_wav, sizeof(beep2_wav), true, FLASH_RAM);

I2SConfig config;
I2SStream out; // Output to I2S
StreamCopy copier;

bool even = false;

void Sound::setup()
{
    ESP_LOGI("", "Sound::setup()");

    AudioLogger::instance().begin(Serial, AudioLogger::Warning);

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

    SerialHelpers::logHeapInfo("after Sound::play");
}

void Sound::loop()
{
    copier.copy();
}
