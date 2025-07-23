#ifndef SOUND_H
#define SOUND_H
#include <string>
#include "../Miniaudio/miniaudio.h"

typedef struct {
    ma_decoder decoder;
    ma_device device;
    int isInitialized;
} AudioPlayer;



int PlaySoundEffect(const char* filepath);
void StopSoundEffect();
void audio_player_uninit(ma_device* placeholder)
#endif