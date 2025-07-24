#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H
#include <string>
#include <vector>
#include "../ImageManager/ImageManager.hpp"

struct Animation {
    std::vector<Image> frames;
};

struct PlayingAnimation {
    const Animation* anim = nullptr;
    size_t currentFrame = 0;
    float elapsedTime = 0.0f;    // ms
    float frameDuration = 100.0f; // ms per frame
    float x = 0, y = 0, size = 1.0f;
    bool finished = false;
    bool loop = false;
};

// Function declarations matching your .cpp:
void LoadAnimations();
void PlayAnimation(const std::string& name, float x, float y, float size, float fps, bool loop = false);
void RenderAnimations();
void UpdateAnimations();
void EndAnimation(const std::string& name);

#endif // ANIMATIONMANAGER_H