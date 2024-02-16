#include "sound.h"

#include "sounds/beep1.h"
#include "sounds/beep2.h"

// How to create audio memory streams
// https://github.com/pschatzmann/arduino-audio-tools/wiki/MemoryStream:-Converting-a-File-to-Flash-Memory
// In Audacity:
//      - export WAV, Mono, 22050 Hz, Signed 16-bit PCM
// In VSCode bash terminal
//      - xxd -i file.wav file_wav.h
//      - add 'const' keyword to object
// Caution: make sure the audio files are 'const' so they stay in PROGMEM
MemoryStream beep1(beep1_wav, sizeof(beep1_wav), true, FLASH_RAM);
MemoryStream beep2(beep2_wav, sizeof(beep2_wav), true, FLASH_RAM);

AudioInfo audioInfo(SAMPLE_RATE, AUDIO_CHANNELS, BITS_PER_SAMPLE);

// data flow: sound -> volume -> i2s
MemoryStream *sound;
I2SStream i2s;
VolumeStream volume(i2s);
StreamCopy copier;

bool even = true;
float currentVolume = 0.5;

void Sound::setup()
{
    ESP_LOGI("", "Sound::setup()");

    AudioLogger::instance().begin(Serial, AudioLogger::Warning);

    I2SConfig config = i2s.defaultConfig(TX_MODE);
    config.copyFrom(audioInfo);
    config.pin_bck = I2S_BCLK;
    config.pin_data = I2S_DOUT;
    config.pin_ws = I2S_LRC;
    i2s.begin(config);

    volume.begin(config); // we need to provide the bits_per_sample and channels
    volume.setVolume(currentVolume);

    // set default sound
    sound = &beep1;
    sound->end(); // dont play the placeholder sound
}

void Sound::stop()
{
    // lower volume to eliminate pops when ending audio playback
    volume.setVolume(0.0);
    sound->end();
    copier.end();
}

void Sound::play()
{
    ESP_LOGI("", "Sound::play()");

    // select which sound to play
    if (even)
        sound = &beep1;
    else
        sound = &beep2;

    sound->begin();                  // reset sound at beginning of data
    volume.setVolume(currentVolume); // set the playback volume
    copier.begin(volume, *sound);    // begin playback

    even = !even;

    SerialHelpers::logHeapInfo("after Sound::play");
}

void Sound::loop()
{
    copier.copy();
}
