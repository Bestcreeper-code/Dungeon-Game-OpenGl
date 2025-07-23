#include "Sound.h"
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <stdio.h>



void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);
    (void)pInput;
}

int PlaySoundEffect(AudioPlayer* player ,const char* filepath){
    ma_result result;

    player->isInitialized = 0;

    // Initialize decoder
    result = ma_decoder_init_file(filepath, NULL, &player->decoder);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize decoder for %s\n", filepath);
        return -1;
    }

    // Setup playback device config
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = player->decoder.outputFormat;
    deviceConfig.playback.channels = player->decoder.outputChannels;
    deviceConfig.sampleRate        = player->decoder.outputSampleRate;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = &player->decoder;

    // Initialize playback device
    if (ma_device_init(NULL, &deviceConfig, &player->device) != MA_SUCCESS) {
        printf("Failed to open playback device\n");
        ma_decoder_uninit(&player->decoder);
        return -2;
    }

    // Start playback device
    if (ma_device_start(&player->device) != MA_SUCCESS) {
        printf("Failed to start playback device\n");
        ma_device_uninit(&player->device);
        ma_decoder_uninit(&player->decoder);
        return -3;
    }

    player->isInitialized = 1;
    return 0;
}

void audio_player_uninit(AudioPlayer* player) {
    if (player->isInitialized) {
        ma_device_uninit(&player->device);
        ma_decoder_uninit(&player->decoder);
        player->isInitialized = 0;
    }
}
