#include "../Types/Types.h"
#include <GL/glut.h>
#include <algorithm>
#include <thread>
#include "../Graphics/Graphics.h"
#include "../globals.h"
#include "../Tiles/Tiles.h"



// Object ---------------------------------------------------------
Object::Object(Vector2D pos, float w, float h, unsigned char red, unsigned char green, unsigned char blue) {
    position = pos;
    width = w;
    height = h;
    r = red;
    g = green;
    b = blue;   
}
void Object::Draw() {
    glColor3ub(r, g, b); 
    glBegin(GL_QUADS);
        glVertex2f(position.x, position.y);
        glVertex2f(position.x + width, position.y);
        glVertex2f(position.x + width, position.y + height);
        glVertex2f(position.x, position.y + height);
    glEnd();
}
void Object::move(float dx, float dy) {
    position.x += dx;
    position.y += dy;
}

void Object::update(bool* keys ) {

    Draw();
}
void Object::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}





//Tile ---------------------------------------------------------
Tile::Tile(Vector2D pos, float w, float h,unsigned char tiletype, unsigned char red, unsigned char green, unsigned char blue) : Object(pos, w, h, red, green, blue) {
    Type = tiletype;
}
void Tile::Draw() {
    Draw_Image(sprite_name.c_str(),position.x,position.y,width*27);
//     glColor3ub(r, g, b);
//     drawRect(position.x, position.y, width, height);
}
void Tile::update(bool* keys) {
    Draw();
}
Tile::~Tile() {
    
}
void Tile::interact() {
}





//Tilemap ---------------------------------------------------------
Tilemap::Tilemap(int width, int height, std::vector<unsigned char> tileData) : width(width), height(height) {
    tiles.reserve(width * height);
    float tilew = 2.0f / width;
    float tileh = 2.0f / height;
    
    for (int i = 0; i < width * height; ++i) {
        int y = ((int)i / height);
        int flippedY = height - 1 - y;
        
        Tile base(Vector2D{0, 0}, 0, 0, 0, 0, 0, 0);
        Vector2D pos = Vector2D{(float)((i % width) * tilew)-1, (float)flippedY * tileh - 1.0f };
        
        switch (tileData[i]) {
            case 0:
                tiles.push_back(new EmptyTile(pos, tilew, tileh));
                break;
            case 1:
                tiles.push_back(new WallTile(pos, tilew, tileh));
                break;
            case 2:
            
                tiles.push_back(new Chest(pos, tilew, tileh, rand()%3));
                break;
            default:
                tiles.push_back(new Tile(pos, tilew, tileh, tileData[i], 255, 0, 255));
                break;
        }
        
    }
}
void Tilemap::Draw() {
    for (auto& tile : tiles) {
        
        tile->Draw();
    }
}
void Tilemap::update(bool* keys) {
    for (auto& tile : tiles) {
        tile->update(keys);
    }
}
void Tilemap::setTile(int x, int y, Tile* tile) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        tiles[y * width + x] = tile;
    }
}

void Tilemap::removeTile(Tile* tile) {
    auto it = std::find(tiles.begin(), tiles.end(), tile);
    if (it != tiles.end()) {
        int index = std::distance(tiles.begin(), it);
        Vector2D pos = tile->position;
        float tilew = tile->width;
        float tileh = tile->height;
        delete *it;
        tiles[index] = new EmptyTile(pos, tilew, tileh);
    }
}

Tile* Tilemap::getTile(int x, int y) {
    y = height - 1 - y;
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[y * width + x];
    }
    return nullptr;
}
Tilemap::~Tilemap() {
    for (auto& tile : tiles) {
        delete tile;
    }
    tiles.clear();

}

