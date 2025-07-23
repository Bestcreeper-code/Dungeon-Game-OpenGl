#include "Graphics.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <unordered_map>
#include <string>
#include "../Gameplay/Game.h"
#include <math.h>
#include <numbers>
#include "../globals.h"


std::unordered_map<std::string, GLuint> textureCache;
 
void initGraphics(int width, int height) {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, height, 0.0);
}

void drawRect(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
        glVertex2f(x, y);             
        glVertex2f(x + width, y);    
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);       
    glEnd();
}



void drawText(float x, float y, std::string text, void* font) {
    glRasterPos2f(x, y); 
    for (char c : text) {
        glutBitmapCharacter(font, c);
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    Game::gameInstance->Update();
    glutSwapBuffers();
}


//Button -------------------------------------------------------------
Button::Button(Vector2D pos, float width, float height, std::string text, Color baseColor, Color selectedColor)
    : Object(pos, width, height, baseColor.r, baseColor.g, baseColor.b), text(text), selectedColor(selectedColor)
{
    //
}
void Button::Draw() {
    Color currColor = {r, g, b};
    if (selected){
        currColor.r = selectedColor.r;
        currColor.g = selectedColor.g;
        currColor.b = selectedColor.b;
    }
    glColor3ub(currColor.r, currColor.g, currColor.b);
    drawRect(position.x, position.y, width, height);
    glColor3ub(0, 0, 0);
    drawRect(position.x + 0.01, position.y + 0.01, width - 0.02, height - 0.02);
    glColor3ub(currColor.r, currColor.g, currColor.b);
    float textWidth = 0.0f;
    for (char c : text) {
        textWidth += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, c);
        
    }
    
    float normTextWidth = (textWidth / windowWidth) * width;

    
    drawText(position.x + width / 2 - normTextWidth*2 ,  position.y + height / 2 , text, GLUT_BITMAP_HELVETICA_18);

}