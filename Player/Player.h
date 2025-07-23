#ifndef PLAYER_H
#define PLAYER_H
#include "../Types/Types.h"
#include "../Items/Items.h"

class Player : public Object {
    public:
        int health;
        static std::vector<Item> inventory;

        Player(Vector2D pos, float w, float h,int speed, unsigned char r, unsigned char g, unsigned char b);
        void Draw() override;
        void update();
        ~Player();

        void scaleToRoom();
        void move(float dx, float dy) override;
        void setPosition(float x, float y) override;
    private:
        float speed;
        void checkSurroundings();
};




#endif