#include "FightManager.h"
#include "../Gameplay/Game.h"
#include <algorithm>
std::vector<Vector2D> possibleEnemyPos = std::vector<Vector2D>{Vector2D{-0.5,0.5},Vector2D{0,0.5},Vector2D{0.5,0.5}};


void Fighter::Draw(Vector2D pos){
    drawRect(pos.x,pos.y,0.05,0.05);
}

void Fighter::PlayTurn(){

}
// Enemy -------------------------------

EnemyFighter::EnemyFighter(){

}
// void EnemyFighter::Draw(Vector2D pos){

// }
void EnemyFighter::PlayTurn(){

}

// Player -------------------------------

PlayerFighter::PlayerFighter(){
    health = 100;
    resistance = 0;
    buttons.push_back(Button{Vector2D{-0.75,-0.9},0.4f,0.2f,"Attack", Color{255,0,0}, Color{255,180,180}});
    buttons.push_back(Button{Vector2D{-0.25,-0.9},0.4f,0.2f,"Defend", Color{0,0,255}, Color{180,180,255}});
    buttons.push_back(Button{Vector2D{0.25,-0.9},0.4f,0.2f,"Heal", Color{0,255,0}, Color{180,255,180}});
}
// void PlayerFighter::Draw(Vector2D pos){

// }

void PlayerFighter::PlayTurn(){
    
    Button attackButton = buttons[0];
    Button defendButton = buttons[1];
    Button healButton = buttons[2];
    for (char i = 0; i < buttons.size(); i++) {
        if (i == selectedButton) {
            buttons[i].selected = true;
        } else {
            buttons[i].selected = false;
        }
    }
    attackButton.Draw();
    defendButton.Draw();
    healButton.Draw();
    if (Game::keys[GLUT_KEY_LEFT+Special_Key_Offset] && Game::keyTimers[GLUT_KEY_LEFT+Special_Key_Offset] == 1) {
        selectedButton = (selectedButton - 1 + buttons.size()) % buttons.size();
    } else if (Game::keys[GLUT_KEY_RIGHT+Special_Key_Offset] && Game::keyTimers[GLUT_KEY_RIGHT+Special_Key_Offset] == 1) {
        selectedButton = (selectedButton + 1) % buttons.size();
    } else if (Game::keys['\n'] && Game::keyTimers['\n'] == 1) {
        if (selectedButton == 0) {
            // Attack logic
            Game::fightManager->KillEnemy(1);
        } else if (selectedButton == 1) {
            // Defend logic
            health += 10; 
        } else if (selectedButton == 2) {
            // Heal logic
            health += 20;
        }
    }
}
    


// Fightmanager -----------------------------------------------------------------------------
FightManager::FightManager(){

}

void FightManager::StartFight(std::vector<EnemyFighter> enemiesList,PlayerFighter player)  {
    enemies = enemiesList;
    playerCharacter = player;
}

void FightManager::Update(){
    if (Game::inFight) {
        glColor3ub(255,255,0);
        playerCharacter.Draw(Vector2D{0,-0.5});
        for (int i = 0;i<enemies.size();i++){
            glColor3ub(255,0,0);
            enemies[i].Draw(possibleEnemyPos[i]);
        }
        if(playerturn) playerCharacter.PlayTurn(); 
        else {
            for (auto& enemy : enemies) {
                enemy.PlayTurn();
            }
        }
    }
}

void FightManager::NewTurn(){
    playerCharacter.PlayTurn();
    for (auto enemy : enemies){
        enemy.PlayTurn();
    }
}

void FightManager::KillEnemy(int pos){
    pos--;
    if (pos >= 0 && pos < enemies.size()) {
        enemies.erase(enemies.begin() + pos);
    }
}