#include "Sound.h"
#include <windows.h>

void PlaySoundEffect(const char* filename) {
#ifdef _WIN32
    PlaySound(TEXT(filename), NULL, SND_FILENAME | SND_ASYNC);
#elif __linux__
    // Use OpenAL or other
#endif
}
