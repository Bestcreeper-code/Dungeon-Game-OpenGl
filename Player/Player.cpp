#include "../Player/Player.h"
#include "../Graphics/Graphics.h"
#include "../Gameplay/Game.h"
#include <math.h>

std::vector<Item> Player::inventory = std::vector<Item>();
Player::Player(Vector2D pos, float w, float h,int speed, unsigned char red, unsigned char green, unsigned char blue) : Object(pos, w, h, red, green, blue) {
    health = 100;
    this->speed = speed;
        
}
void Player::Draw() {
    glColor3ub(r, g, b);
    float tilew = 2.0f / Game::currroom->width;
    float tileh = 2.0f / Game::currroom->height;
    float offw = (tilew-width)/2;
    float offh = (tileh-height)/2;
    drawRect(position.x+offw, position.y+offh, width, height);
}


void Player::scaleToRoom() {
    float tilew = 2.0f / Game::currroom->width;
    float tileh = 2.0f / Game::currroom->height;
    width = tilew*0.8;
    height = tileh*0.8; 
    position.x = std::round((position.x + 1.0f) / tilew) * tilew - 1.0f;
    position.y = std::round((position.y + 1.0f) / tileh) * tileh - 1.0f;
}
void Player::update() {
    if (Game::keyTimers[GLUT_KEY_UP+Special_Key_Offset] == 1) {
        move(0, speed);
    }
    if (Game::keyTimers[GLUT_KEY_DOWN+Special_Key_Offset] == 1) {
        move(0, -speed);
    }
    if (Game::keyTimers[GLUT_KEY_LEFT+Special_Key_Offset] == 1) {
        move(-speed, 0);
    }
    if (Game::keyTimers[GLUT_KEY_RIGHT+Special_Key_Offset] == 1) {
        move(speed, 0);
    }
    
    float tilesize = 1/Game::map.size.x;
    if (position.x < -1 && Game::keyTimers[GLUT_KEY_LEFT+Special_Key_Offset] == 1 ) {
        if (!Game::changeRoom(Vector2D{Game::MapPos.x - 1, Game::MapPos.y})) {
            position.x = -1;
        }
        else {
            
            position.x = 1-width/0.8;
        }
    } 
    else if (position.x >= 1-width && Game::keyTimers[GLUT_KEY_RIGHT+Special_Key_Offset] == 1) {
        if (!Game::changeRoom(Vector2D{Game::MapPos.x + 1, Game::MapPos.y})) {
            position.x = 1-width/0.8;
        }
        else {
            
            position.x = -1;
        }
    }
    else if (position.y <= -1-height/2 && Game::keyTimers[GLUT_KEY_DOWN+Special_Key_Offset] == 1) {
        if (!Game::changeRoom(Vector2D{Game::MapPos.x, Game::MapPos.y + 1})) {
            position.y = -1;
        }
        else {
            
            position.y = 1-height/0.8;
        }
    } 
    else if (position.y >= 1 && Game::keyTimers[GLUT_KEY_UP+Special_Key_Offset] == 1) {
        if (!Game::changeRoom(Vector2D{Game::MapPos.x, Game::MapPos.y - 1})) {
            position.y = 1-height/0.8;
        }
        else {
            
            position.y = -1;
        }
    }
    
    if (Game::keyTimers['e'] >= 1 || Game::keyTimers['E'] >= 1) {
        checkSurroundings();
    }
    Draw();
}
void Player::move(float dx, float dy) 
{
    dx = (int)dx;
    dy = (int)dy;
    Tilemap* room = Game::currroom;
    float tilew = 2.0f / room->width;
    float tileh = 2.0f / room->height;

    int tileX = (int)((position.x + 1.0f) / tilew) + dx;
    int tileY = (int)((position.y + 1.0f) / tileh) + dy;

    
    Tile* tile = room->getTile(tileX, tileY);
    if (tile) {

        if (tile->Type != 0) {
            return;
        }
    }
    position.x += dx * tilew;
    position.y += dy * tileh;
}

void Player::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

void Player::checkSurroundings() {
    Tilemap* room = Game::currroom;
    float tilew = 2.0f / room->width;
    float tileh = 2.0f / room->height;
    Vector2D mappos = Vector2D{
        (float)(int)((position.x + 1.0f) / tilew),
        (float)(int)((position.y + 1.0f) / tileh)
    };
    const int dirs[4][2] = { {0, 1}, {0, -1}, {-1, 0}, {1, 0} };
    for (int i = 0; i < 4; ++i) {
        int x = mappos.x + dirs[i][0];
        int y = mappos.y + dirs[i][1];
        Tile* tile = room->getTile(x, y);
        if (tile) {
            if (tile->Type == 2) {
                tile->interact();
            }
        }
    }
}

Player::~Player() {
    
}