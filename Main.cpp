#include <GL/freeglut.h>
#include "Graphics/Graphics.h"
#include "Gameplay/Game.h"
#include "globals.h"
// #include <mmsystem.h>

int frameRate = GAME_FRAMERATE;
int windowWidth = 800,windowHeight = 800;

Game* game = new Game(windowWidth, windowHeight);



void KeyDown(UINT8 key,int x, int y) {
    game->keys[key] = true;  
}

void KeyUp(UINT8 key,int x, int y) {

    game->keys[key] = false;  
}

void SpecialKeyDown(int key, int x, int y) {
    game->keys[key+Special_Key_Offset] = true;
}

void SpecialKeyUp(int key, int x, int y) {

    game->keys[key+Special_Key_Offset] = false;
}




void reshape(int w, int h) {
    int squareSize = std::min(w, h);
    int offsetX = (w - squareSize) / 2;
    int offsetY = (h - squareSize) / 2;

    glViewport(offsetX, offsetY, squareSize, squareSize);

}

void Close() {
    game->Cleanup();
    free(game);
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Dungeon...?");
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    initGraphics(windowWidth, windowHeight);
    
    glutKeyboardFunc(KeyDown);
    glutKeyboardUpFunc(KeyUp);
    glutSpecialFunc(SpecialKeyDown);
    glutSpecialUpFunc(SpecialKeyUp);
    
    glutDisplayFunc(display);
    glutCloseFunc(Close);
        
    glutReshapeFunc(reshape);
    glutFullScreen();
    
    // PlaySound(TEXT("pacman_x.wav"), NULL, SND_FILENAME | SND_ASYNC);
    Loop(frameRate); 
    glutMainLoop();
    return 0;
}


// git add .
// git commit -m "message"
// git push origin master:main

