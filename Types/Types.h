#ifndef TYPES_H
#define TYPES_H
#include <vector>
#include <string>

struct Vector2D {
    float x, y;
};

struct Color {
    unsigned char r, g, b;
};





class Object{
public:
    Vector2D position;
    float width, height;
    unsigned char r, g, b;
    
    Object(Vector2D pos, float w, float h, unsigned char r, unsigned char g, unsigned char b);
    virtual void Draw();
    virtual void update(bool* keys);
    virtual void move(float dx, float dy);
    virtual void setPosition(float x, float y);
    virtual ~Object() {}
    };
    
    class Tile : public Object {
    public:
        std::string sprite_name = "Res/Images/ComboImages/x.png";
        unsigned char Type;
        Tile(Vector2D pos, float w, float h,unsigned char tiletype, unsigned char r, unsigned char g, unsigned char b);
        void Draw() override;
        void update(bool* keys) override;
        virtual void interact();
        ~Tile();  
    };
    
    class Tilemap {
    public:
        int width, height;
        Tilemap(int width, int height, std::vector<unsigned char> tileData);
        void Draw();
        void update(bool* keys);
        void setTile(int x, int y, Tile* tile);
        void removeTile(Tile* tile);
        Tile* getTile(int x, int y);
        ~Tilemap();
        std::vector<Tile*>tiles;
        private:
    };

    
    struct Map
    {
        Vector2D size;
        std::vector<Tilemap*> rooms;
    };
    
    
#endif