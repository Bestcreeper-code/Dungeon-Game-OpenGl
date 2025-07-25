#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <GL/glut.h> 
#include "../Types/Types.h"
#include <string>



void initGraphics(int width, int height);
void drawRect(float x, float y, float width, float height);
void display();
void drawText(float x, float y, std::string text, void* font = GLUT_BITMAP_HELVETICA_18);
void Draw_Image(const char* path,float x,float y,float scale, GLenum format = GL_RGBA );

class Button : public Object {
public:
    bool selected = false;
    bool show = true;

    std::string text;
    Color selectedColor = Color{255, 255, 0};

    Button(Vector2D pos, float width, float height, std::string text, Color baseColor, Color selectedColor);
    void Draw()override;

};


#endif
