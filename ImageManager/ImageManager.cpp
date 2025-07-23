#include "ImageManager.hpp"
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"

// Constants
constexpr int CHANNELS = 4; // RGBA

// Image cache
std::unordered_map<std::string, Image> ImageCache;

// Image class definitions
Image::Image() : width(0), height(0), data(nullptr) {}

Image::Image(int w, int h, BYTE* pxl) : width(w), height(h) {
    data = std::make_unique<BYTE[]>(width * height * CHANNELS);
    if (pxl) {
        std::copy(pxl, pxl + (width * height * CHANNELS), data.get());
    }
}

Image::Image(const Image& other)
    : width(other.width), height(other.height),
      data(std::make_unique<BYTE[]>(width * height * CHANNELS)) {
    std::copy(other.data.get(), other.data.get() + (width * height * CHANNELS), data.get());
}

Image& Image::operator=(const Image& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        data = std::make_unique<BYTE[]>(width * height * CHANNELS);
        std::copy(other.data.get(), other.data.get() + (width * height * CHANNELS), data.get());
    }
    return *this;
}

void Image::SetData(BYTE* pxl) {
    std::copy(pxl, pxl + (width * height * CHANNELS), data.get());
}

// Load image from file directly to a byte vector (no cache)
std::vector<BYTE> LoadImageToByteVector(const std::string& filename, int& width, int& height) {
    int channelsInFile;
    unsigned char* imgData = stbi_load(filename.c_str(), &width, &height, &channelsInFile, CHANNELS);
    if (!imgData) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return {};
    }

    std::vector<BYTE> imageData(imgData, imgData + (width * height * CHANNELS));
    stbi_image_free(imgData);
    return imageData;
}

std::vector<BYTE> GetImageData(const char* filename, int& width, int& height) {

    auto it = ImageCache.find(filename);
    if (it != ImageCache.end()) {
        const Image& img = it->second;
        width = img.width;
        height = img.height;
        return std::vector<BYTE>(img.data.get(), img.data.get() + (width * height * CHANNELS));
    }

    int channelsInFile;
    unsigned char* imgData = stbi_load(filename, &width, &height, &channelsInFile, CHANNELS);
    if (!imgData) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return {};
    }

    std::vector<BYTE> imageData(imgData, imgData + (width * height * CHANNELS));
    stbi_image_free(imgData);

    
    const int rowSize = width * CHANNELS;
    for (int y = 0; y < height / 2; ++y) {
        int top = y * rowSize;
        int bottom = (height - 1 - y) * rowSize;
        for (int x = 0; x < rowSize; ++x) {
            std::swap(imageData[top + x], imageData[bottom + x]);
        }
    }

    
    ImageCache[filename] = Image(width, height, imageData.data());

    return imageData;
}

