#include "FightManager.h"
#include "../Gameplay/Game.h"
#include "../globals.h"
#include <algorithm>
#include "../AnimationManager/AnimationManager.h"
std::vector<Vector2D> possibleEnemyPos = std::vector<Vector2D>{Vector2D{-0.5,0.5},Vector2D{0,0.5},Vector2D{0.5,0.5}};


void Fighter::Draw(Vector2D pos){
    drawRect(pos.x,pos.y,0.05,0.05);
    drawText(pos.x,pos.y+0.1,std::to_string(health),GLUT_BITMAP_HELVETICA_18);
}

int Fighter::PlayTurn(){
    return 0;
}

void Fighter::Hurt(int amount){
    health -= amount;
}
// Enemy -------------------------------

EnemyFighter::EnemyFighter(){
    health = 100;
    max_health = 100;
}
// void EnemyFighter::Draw(Vector2D pos){

// }
int EnemyFighter::PlayTurn() {
    if(Game::fightManager->combo_mode){
        char combosize =3+rand()%4;
        static_cast<ComboInputUi*>(Game::menus[COMBO_INPUT_MENU])->Start(
            Generate_Random_Key_Combo(combosize),
            350,
            [](int value,void* arg) {
                int damage = *((int*)arg);
                Game::fightManager->playerCharacter.Hurt(damage - value * 3);
                Game::fightManager->waiting = false;
                Game::fightManager->enemyTurnIndex++;
            },
            &damage,
            sizeof(damage)
        );
    }else{
        Game::fightManager->playerCharacter.Hurt(damage+(rand()%7-3));
        Game::fightManager->waiting = false;
        Game::fightManager->enemyTurnIndex++;
    }
    return 0;  
}


// Player -------------------------------

PlayerFighter::PlayerFighter(){
    health = 100;
    max_health = 100;
    resistance = 0;
    buttons.push_back(Button{Vector2D{-0.75,-0.9},0.4f,0.2f,"Attack", Color{255,0,0}, Color{255,180,180}});
    buttons.push_back(Button{Vector2D{-0.25,-0.9},0.4f,0.2f,"Defend", Color{0,0,255}, Color{180,180,255}});
    buttons.push_back(Button{Vector2D{0.25,-0.9},0.4f,0.2f,"Heal", Color{0,255,0}, Color{180,255,180}});
}
// void PlayerFighter::Draw(Vector2D pos){

// }

int PlayerFighter::PlayTurn(){
    
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
    Color textcolor = Game::fightManager->combo_mode? Color{0,255,0} : Color{255,0,0};
    glColor3ub(textcolor.r,textcolor.g,textcolor.b);
    if(Game::fightManager->combo_mode){
        drawText(-0.8,-0.5,"Combo Mode Activated",GLUT_BITMAP_HELVETICA_18);
    } else{
        drawText(-0.8,-0.5,"Press Tab to Switch to Combo Mode",GLUT_BITMAP_HELVETICA_18);
    }
    if (Game::keys[GLUT_KEY_LEFT + Special_Key_Offset] && Game::keyTimers[GLUT_KEY_LEFT + Special_Key_Offset] == 1) {
        selectedButton = (selectedButton - 1 + buttons.size()) % buttons.size();
    }
    
    else if (Game::keys[GLUT_KEY_RIGHT + Special_Key_Offset] && Game::keyTimers[GLUT_KEY_RIGHT + Special_Key_Offset] == 1) {
        selectedButton = (selectedButton + 1) % buttons.size();
    }

    else if (Game::keys['\t'] && Game::keyTimers['\t'] == 1) {
        Game::fightManager->combo_mode = !Game::fightManager->combo_mode;
    }
    
    else if (Game::keys[KEY_ENTER] && Game::keyTimers[KEY_ENTER] == 1) {
        if (selectedButton == 0) {
            //Combo mode on -> combo ui------------------------
            if(Game::fightManager->combo_mode){
                Game::fightManager->waiting = true;
                char combosize =3+rand()%4;
                static_cast<ComboInputUi*>(Game::menus[COMBO_INPUT_MENU])->Start(Generate_Random_Key_Combo(combosize),
                    combosize*GAME_FRAMERATE,
                    [](int value,void* arg) {
                        char size = static_cast<ComboInputUi*>(Game::menus[COMBO_INPUT_MENU])->Combosize();
                        int attack = Game::fightManager->playerCharacter.weapon.damage; 
                        Game::fightManager->DamageEnemy((float(attack)*1.3f/float(size))*value,0);
                        Game::fightManager->waiting = false;
                        Game::fightManager->playerturn = false;
                    },
                    NULL,
                    0
                );
            } else {
                int attack = Game::fightManager->playerCharacter.weapon.damage; 
                Game::fightManager->DamageEnemy(rand()%attack,0);
                Game::fightManager->playerturn = false;
            }
            
            PlayAnimation("Slash",possibleEnemyPos[0].x,possibleEnemyPos[0].y,2,6,false);
        } else if (selectedButton == 1) {
            // Defend logic
            health += 10; 
            health = health <= max_health? health:max_health;
        } else if (selectedButton == 2) {
            // Heal logic
            health += 20;
            health = health <= max_health? health:max_health;
        }
    }
    return 0;
}
    


// Fightmanager -----------------------------------------------------------------------------
FightManager::FightManager(){
    waiting = false;
    show = false;
    playerturn = true;
    combo_mode = false;
}

void FightManager::StartFight(std::vector<EnemyFighter> enemiesList,PlayerFighter player)  {
    enemies = enemiesList;
    playerCharacter = player;
    Game::NoInventory = true;
    show = true;
}

void FightManager::Update() {
    if (!(Game::inFight && show)) return;

    // Draw all characters
    glColor3ub(255,255,0);
    playerCharacter.Draw(Vector2D{0,-0.5});
    for (int i = 0; i < enemies.size(); i++) {
        glColor3ub(0,100,0);
        enemies[i].Draw(possibleEnemyPos[i]);
    }

    if (waiting || Game::paused) return; 

    if (playerturn) {
        playerCharacter.PlayTurn(); 
    } else {
        if (enemyTurnIndex < enemies.size()) {
            waiting = true; 
            enemies[enemyTurnIndex].PlayTurn();
        } else {
            playerturn = true;
            enemyTurnIndex = 0; 
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
    if (pos >= 0 && pos < enemies.size()) {
        enemies.erase(enemies.begin() + pos);
    }
}

void FightManager::DamageEnemy(int damage,int pos){
    if (pos >= 0 && pos < enemies.size()) {
       enemies[pos].Hurt(damage);
       if (enemies[pos].health <=0)KillEnemy(pos); 
    }
}