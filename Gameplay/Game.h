#ifndef GAME_H
#define GAME_H
#define Special_Key_Offset 255
#define KEY_ESCAPE 27
#define KEY_ENTER  '\r'
class Player;
#include "../Player/Player.h"
#include "../Types/Types.h" 
#include <vector>
#include "../Ui/Menus/Menus.h"
#include "../Ui/Messages/Messages.h"
#include "../FightManager/FightManager.h"


enum Menus_Indexes{
    INVENTORY_MENU,
    COMBO_INPUT_MENU
};

class Game {
public:
    static bool* keys;
    static unsigned int* keyTimers;
    static Game* gameInstance;
    static Player* player;


    static Tilemap* currroom;
    static Vector2D MapPos;
    static Map map;

    static FightManager* fightManager;
    static std::vector<Menu*> menus;
    static MessageManager* messageManager;
    
    static bool paused;
    static bool inFight;
    static bool NoInventory;
    
    Game(int width, int height);
    static void Cleanup();
    static void Update();
    static void HandleMainInputs();
    static void UpdateTimers();
    static bool changeRoom(Vector2D Room);
    
};


void Loop(int fps);

#endif
