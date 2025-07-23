#ifndef TILES_H
#define TILES_H
#include "../Types/Types.h"
#include <vector>
#include "../Items/Items.h"

class EmptyTile : public Tile{
public:
    EmptyTile(Vector2D pos, float w, float h);
};

class WallTile : public Tile{
public:
    WallTile(Vector2D pos, float w, float h);
};

class Chest : public Tile {
public:

    Chest(Vector2D pos, float w, float h,char amountOfItems);
    void interact() override;
    ~Chest();
protected:
    std::vector<Item>* content = new std::vector<Item>();;
    bool opened = false;
};



#endif