#include "../Tiles/Tiles.h"
#include <GL/glut.h>
#include "../Graphics/Graphics.h"
#include "../Gameplay/Game.h"
#include "../globals.h"
#include "../Items/Items.h"
#include <vector>
#include "../Player/Player.h"
#include <random>
#include "../Ui/Messages/Messages.h"


EmptyTile::EmptyTile(Vector2D pos, float w, float h) : Tile(pos, w, h, 0, 20, 20, 20){}

WallTile::WallTile(Vector2D pos, float w, float h) : Tile(pos, w, h, 1, 128, 128, 128){}

Chest::Chest(Vector2D pos, float w, float h,char amountOfItems) : Tile(pos, w, h, 2, 145, 92, 6){
    for (char i = 0;i<amountOfItems;i++)  
    {
        int itemIndex = std::rand() % ITEMS_H::all_items.size();
        
        if (!content) content = new std::vector<Item>();
        content->push_back(ITEMS_H::all_items[itemIndex]);
    }  
}

void Chest::interact() {
    if (!opened) { 
        opened = true;
        int i = 0;
        auto item = content->begin();
        while (item != content->end()) {
            Game::messageManager->AddMessage(Message{
                "You got a "+item->name+" !",
                Color{255, 255, 0},
                100,
                GLUT_BITMAP_TIMES_ROMAN_24
            });
            Player::inventory.push_back(*item);
            i++;
            item = content->erase(item);
        }
        Game::currroom->removeTile(this);
    }
}

Chest::~Chest() {
    if (content) {
        delete content;
        content = nullptr;
    }
}


