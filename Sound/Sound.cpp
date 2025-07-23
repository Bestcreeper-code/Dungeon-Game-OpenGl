#define MINIAUDIO_IMPLEMENTATION
#include "../Miniaudio/miniaudio.h"
#include "Sound.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // for usleep
#include <stdlib.h>


void* PlaySoundEffect_Thread(void* arg)
{
    SoundThreadData* data = (SoundThreadData*)arg;

    ma_result result;
    ma_engine engine;
    ma_sound sound;

    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine.\n");
        free(data);
        return NULL;
    }

    result = ma_sound_init_from_file(&engine, data->path, 0, NULL, NULL, &sound);
    if (result != MA_SUCCESS) {
        printf("Failed to load sound file.\n");
        ma_engine_uninit(&engine);
        free(data);
        return NULL;
    }

    result = ma_sound_start(&sound);
    if (result != MA_SUCCESS) {
        printf("Failed to start sound.\n");
        ma_sound_uninit(&sound);
        ma_engine_uninit(&engine);
        free(data);
        return NULL;
    }

    while (ma_sound_is_playing(&sound) && data->play) {
        usleep(100 * 1000);
    }

    if (!data->play) {
        ma_sound_stop(&sound);
    }

    ma_sound_uninit(&sound);
    ma_engine_uninit(&engine);
    free(data);
    return NULL;
}



SoundThreadData* PlaySoundEffect(const char* path)
{
    pthread_t thread_id;
    SoundThreadData* data = (SoundThreadData*)malloc(sizeof(SoundThreadData));
    if (!data) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    data->path = path;
    data->play = true;

    if (pthread_create(&thread_id, NULL, PlaySoundEffect_Thread, data) != 0) {
        printf("Failed to create thread.\n");
        free(data);
        return NULL;
    }

    pthread_detach(thread_id);
    return data;
}

void StopSoundEffect(SoundThreadData* data)
{
    if (data) {
        data->play = false;
    }
}
