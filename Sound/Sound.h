#ifndef SOUND_H
#define SOUND_H
#include <string>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

typedef struct {
    ma_decoder decoder;
    ma_device device;
    int isInitialized;
} AudioPlayer;


int PlaySoundEffect(AudioPlayer* player ,const char* filepath);

#endif