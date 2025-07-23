#ifndef FIGHTMANAGER_H
#define FIGHTMANAGER_H
#include "../Graphics/Graphics.h"
class Fighter 
{
public:
    int health;
    float resistance;
    virtual void Draw(Vector2D pos);
    virtual void PlayTurn();
};

class EnemyFighter : public Fighter
{
public:
    EnemyFighter();
    void PlayTurn() override;
    // void Draw(Vector2D pos) override;
};

class PlayerFighter : public Fighter
{
public:
    std::vector<Button> buttons;
    PlayerFighter();
    void PlayTurn() override;
    // void Draw(Vector2D pos) override;
private:
    char selectedButton = 0;
};

class FightManager
{
public:
    FightManager();
    void StartFight(std::vector<EnemyFighter> enemiesList, PlayerFighter player);
    void Update();
    void NewTurn();
    void DamageEnemy(int damage, int pos);
    void KillEnemy(int pos);
    
    bool waiting;
    bool playerturn;
    bool show;
private:
    std::vector<EnemyFighter> enemies;
    PlayerFighter playerCharacter;
};






#endif