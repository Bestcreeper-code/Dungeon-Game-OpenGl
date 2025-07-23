#include "Game.h"
#include "../Graphics/Graphics.h"
#include "../Types/Types.h"
#include <GL/freeglut.h>
#include <cstring> 
#include <vector>
#include "../globals.h"
#include <string>
#include "../Ui/Menus/Menus.h"
#include "../Player/Player.h"
#include "../Ui/Messages/Messages.h"
#include "../FightManager/FightManager.h"

Game* Game::gameInstance = nullptr;
Tilemap* Game::currroom = nullptr;

Vector2D Game::MapPos = Vector2D{0, 0};

Map Game::map = Map{Vector2D{2, 2},
    std::vector<Tilemap*>{
        new Tilemap(8,8, std::vector<unsigned char>{
            1, 1, 1, 1, 1, 1, 1, 1, 
            1, 1, 1, 1, 1, 1, 1, 1, 
            1, 1, 1, 1, 1, 1, 1, 1, 
            1, 0, 2, 0, 0, 0, 0, 0,
            1, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 0, 0, 1, 1 ,1,
            1 ,1 ,1 ,0 ,0 ,1 ,1 ,1,
            1 ,1 ,1 ,0 ,0 ,1 ,1 ,1
        }),
        new Tilemap(32,32,
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 2, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0
        }
        ),
        new Tilemap(16,16, std::vector<unsigned char>{
            1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1,
            1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1,
            1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1,
            0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        }),
        new Tilemap(8,8, std::vector<unsigned char>{
            0, 1, 1, 0, 0, 1, 1, 1, 
            0, 1, 1, 0, 0, 1, 1, 1, 
            0, 1, 1, 0, 0, 1, 1, 1, 
            0, 0, 2, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 0, 0, 1, 1 ,1,
            1 ,1 ,1 ,0 ,0 ,1 ,1 ,1,
            1 ,1 ,1 ,0 ,0 ,1 ,1 ,1
        }),
    }   
};
MessageManager* Game::messageManager = new MessageManager(Vector2D{1,0.9});

bool* Game::keys = new bool[512]();
unsigned int* Game::keyTimers = new unsigned int[512]();

bool Game::paused = false;
bool Game::inFight = false;
bool Game::NoInventory = false;

Player* Game::player = new Player(Vector2D{0, 0}, 0.2f, 0.2f,1, 255, 0, 0);

FightManager* Game::fightManager = new FightManager();



std::vector<Menu*> Game::menus = { new Inventory(), new ComboInputUi() };

Game::Game(int width, int height) {
    
    fightManager->StartFight(std::vector<EnemyFighter>{EnemyFighter{},EnemyFighter{},EnemyFighter{}},PlayerFighter{});  // -------------
    gameInstance = this;    
    currroom = map.rooms[0];

    ((ComboInputUi*)menus[COMBO_INPUT_MENU])->Start(std::vector<unsigned short>{
            'd',
            GLUT_KEY_UP + Special_Key_Offset,
            'k',
            GLUT_KEY_LEFT + Special_Key_Offset,
            'w',
            'r',
            GLUT_KEY_DOWN + Special_Key_Offset,
            'a',
            'o',
            GLUT_KEY_RIGHT + Special_Key_Offset,
            'e',
            'z',
            'c',
            GLUT_KEY_UP + Special_Key_Offset,
            'm',
            GLUT_KEY_LEFT + Special_Key_Offset,
            't',
            GLUT_KEY_DOWN + Special_Key_Offset,
            'b',
            GLUT_KEY_RIGHT + Special_Key_Offset
        },60*20

    );

}

void Game::Update() {
    UpdateTimers();
    if (!paused) {
        if (!inFight){
            currroom->update(keys);
            player->update();
        }
        messageManager->Update();
        fightManager->Update();
    }
    for (Menu* menu : menus) {
        menu->update();
    }
    HandleMainInputs();
}

bool Game::changeRoom(Vector2D Room) {
    if (Room.x < 0 || Room.x >= map.size.x || Room.y < 0 || Room.y >= map.size.y) {
        return false; 
    }
    currroom = map.rooms[Room.x + Room.y * map.size.x];
    MapPos = Room;
    player->scaleToRoom();
    return true;
}


void Game::UpdateTimers() {
    for (int i = 0; i < 512; i++) {
        if (keys[i]) {
            keyTimers[i]++;
        }
        else {
            keyTimers[i] = 0;
        }
    }
}

void Game::HandleMainInputs() {
    if (keys[KEY_ESCAPE]) {
        if (keyTimers[KEY_ESCAPE] >= frameRate*3) {
            Cleanup();
        }
        glColor3ub(255, 255, 255);
        std::string dots((int)(keyTimers[KEY_ESCAPE]+10)/60,'.');
        std::string message = "Hold ESC to exit" + dots;
        drawText(-1, 1-((float)24/windowHeight), message.c_str(), GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if (keyTimers['r']){
        inFight = !inFight;
    }
    return;
}



void Game::Cleanup() {
    if (keys) {
        delete[] keys;
        keys = nullptr;
    }
    if (keyTimers) {
        delete[] keyTimers;
        keyTimers = nullptr;
    }
    if (currroom) {
        currroom = nullptr;
    }
    if (messageManager) {
        delete messageManager;
        messageManager = nullptr;
    }
    if (player) {
        delete player;
        player = nullptr;
    }

    for (auto menu : menus) {
        delete menu;
    }
    menus.clear();


    for (auto room : map.rooms) {
        delete room;
    }
    delete fightManager;
    map.rooms.clear();
    delete gameInstance;
    glutLeaveMainLoop();
}



void Loop(int fps) {
    int delay = 1000 / fps;
    display();
    glutTimerFunc(delay, Loop, fps);
}
