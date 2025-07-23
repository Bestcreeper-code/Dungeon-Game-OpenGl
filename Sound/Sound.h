#ifndef SOUND_H
#define SOUND_H
#include <string>
#include "../Miniaudio/miniaudio.h"

typedef struct {
    const char* path;
    volatile bool play;  // use volatile to prevent optimization issues
} SoundThreadData;




SoundThreadData* PlaySoundEffect(const char* path);
void StopSoundEffect(SoundThreadData* data);
#endif