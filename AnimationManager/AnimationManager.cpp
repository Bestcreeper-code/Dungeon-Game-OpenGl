#include "AnimationManager.h"
#include "../globals.h"
#include <filesystem>
#include <unordered_map>
#include <thread>
#include <GL/freeglut.h>
#include <algorithm>
#include <list>
namespace fs = std::filesystem;

std::unordered_map<std::string, Animation> AnimationCache;
std::list<PlayingAnimation*> activeAnimations;


void LoadAnimations(){
    fs::path directory = "Res/Animations"; 

    if (fs::exists(directory) && fs::is_directory(directory)) { 
        
        for (const auto& entry : fs::directory_iterator(directory)) { 

            if (fs::exists(entry) && fs::is_directory(entry)) { 
                Animation* anim = &AnimationCache[entry.path().stem().string()];   
                for (const auto& file : fs::directory_iterator(entry)) { 
                    printf("File: %s\n", file.path().string().c_str());
                    int w,h;
                    std::vector<BYTE> data = LoadImageToByteVector(file.path().string().c_str(), w, h);
                    anim->frames.push_back(Image(w,h,data.data()));
                }
                printf("Loaded Animation %s\n",entry.path().string().c_str());
            }
        }
    }
}

PlayingAnimation* PlayAnimation(const std::string& name, float x, float y, float size, float fps, bool loop) {
    auto it = AnimationCache.find(name);
    if (it == AnimationCache.end() || it->second.frames.empty()) return NULL;

        PlayingAnimation* pAnim = new PlayingAnimation();
    pAnim->anim = &it->second;
    pAnim->currentFrame = 0;
    pAnim->elapsedTime = 0.0f;
    pAnim->frameDuration = 1000.0f / fps;
    pAnim->x = x;
    pAnim->y = y;
    pAnim->size = size;
    pAnim->finished = false;
    pAnim->loop = loop;

    activeAnimations.push_back(pAnim);
    return pAnim;
}



void RenderAnimations() {
    for (const auto* pAnim : activeAnimations) {
        if (pAnim->finished) continue;

        const Image& frame = pAnim->anim->frames[pAnim->currentFrame];
        glRasterPos2f(pAnim->x, pAnim->y);
        glPixelZoom(pAnim->size, pAnim->size);
        glDrawPixels(frame.width, frame.height, GL_RGBA, GL_UNSIGNED_BYTE, frame.data.get());
        glPixelZoom(1.0f, 1.0f);
    }

}

void UpdateAnimations() {
    for (auto* pAnim : activeAnimations) {
        if (pAnim->finished) continue;

        pAnim->elapsedTime += 1000 / GAME_FRAMERATE;
        if (pAnim->elapsedTime >= pAnim->frameDuration) {
            pAnim->elapsedTime -= pAnim->frameDuration;
            pAnim->currentFrame++;
            if (pAnim->currentFrame >= pAnim->anim->frames.size()) {
                if (pAnim->loop) {
                    pAnim->currentFrame = 0;
                } else {
                    pAnim->currentFrame = pAnim->anim->frames.size() - 1;
                    pAnim->finished = true;
                }
            }
        }
    }

    // Cleanup
    for (auto it = activeAnimations.begin(); it != activeAnimations.end(); ) {
        if ((*it)->finished) {
            delete *it;
            it = activeAnimations.erase(it);
        } else {
            ++it;
        }
    }
}

void EndAnimation(PlayingAnimation* animPtr) {
    if (!animPtr) return;

    for (auto it = activeAnimations.begin(); it != activeAnimations.end(); ++it) {
        if (*it == animPtr) {
            delete *it;
            activeAnimations.erase(it);
            break;
        }
    }
}

