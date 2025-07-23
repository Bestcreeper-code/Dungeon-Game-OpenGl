#ifndef IMAGE_MANAGER_HPP
#define IMAGE_MANAGER_HPP

#include <memory>
#include <vector>
#include <string>

using BYTE = unsigned char;

class Image {
public:
    int width;
    int height;
    std::unique_ptr<BYTE[]> data;

    Image();
    Image(int w, int h, BYTE* pxl);
    Image(const Image& other);
    Image& operator=(const Image& other);

    void SetData(BYTE* pxl);
};

std::vector<BYTE> LoadImageToByteVector(const std::string& filename, int& width, int& height);
std::vector<BYTE> GetImageData(const char* filename, int& width, int& height);

#endif // IMAGE_MANAGER_HPP
