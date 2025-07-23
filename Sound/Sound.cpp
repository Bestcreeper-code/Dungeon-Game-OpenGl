#include "Sound.h"
#include <stdio.h>
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h" // Include the MiniAudio header if it's not included already

static AudioPlayer player;


void audio_player_uninit(ma_device* placeholder) {
    if (player.isInitialized) {
        
        ma_device_stop(&player.device);
        ma_device_uninit(&player.device);
        ma_decoder_uninit(&player.decoder);
        player.isInitialized = 0;
        printf("Audio player uninitialized.\n");
    }
}


void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
    ma_decoder* pDecoder = (ma_decoder*)pDevice->pUserData;
    ma_result result = ma_decoder_read_pcm_frames(pDecoder, pOutput, frameCount, NULL);

    if (result != MA_SUCCESS) {
        printf("Error reading PCM frames.\n");
        return;  
    }

    (void)pInput;  
}


int PlaySoundEffect(const char* filepath) {
    ma_result result;

    
    if (player.isInitialized) {
        printf("Audio player is already initialized.\n");
        return 1;  // Already playing, return early
    }

    // Initialize decoder
    result = ma_decoder_init_file(filepath, NULL, &player.decoder);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize decoder for %s\n", filepath);
        return -1;
    }

    // Set up playback device config
    ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
    deviceConfig.playback.format   = player.decoder.outputFormat;
    deviceConfig.playback.channels = player.decoder.outputChannels;
    deviceConfig.sampleRate        = player.decoder.outputSampleRate;
    deviceConfig.dataCallback      = data_callback;
    deviceConfig.pUserData         = &player.decoder;  // Pass the decoder to the callback
    deviceConfig.stopCallback      = audio_player_uninit;

    // Initialize the playback device
    result = ma_device_init(NULL, &deviceConfig, &player.device);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize the playback device for %s\n", filepath);
        ma_decoder_uninit(&player.decoder);
        return -2;
    }

    // Start the playback device
    result = ma_device_start(&player.device);
    if (result != MA_SUCCESS) {
        printf("Failed to start the playback device for %s\n", filepath);
        ma_device_uninit(&player.device);
        ma_decoder_uninit(&player.decoder);
        return -3;
    }

    
    player.isInitialized = 1;
    printf("Playing sound: %s\n", filepath);
    return 0;  // Success
}


void StopSoundEffect() {
    if (player.isInitialized) {
        audio_player_uninit(NULL); 
        printf("Sound stopped.\n");
    } else {
        printf("No sound is playing.\n");
    }
}


