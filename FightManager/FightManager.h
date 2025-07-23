#ifndef FIGHTMANAGER_H
#define FIGHTMANAGER_H
#include "../Graphics/Graphics.h"
class Fighter 
{
public:
    int health;
    int max_health;
    float resistance;
    virtual void Draw(Vector2D pos);
    virtual int PlayTurn();
    virtual void Hurt(int amount);
};

class EnemyFighter : public Fighter
{
public:
    EnemyFighter();
    int PlayTurn() override;
    // void Draw(Vector2D pos) override;
};

class PlayerFighter : public Fighter
{
public:
    std::vector<Button> buttons;
    PlayerFighter();
    int PlayTurn() override;
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
    int enemyTurnIndex = 0; 
    bool playerturn;
    bool show;
    PlayerFighter playerCharacter;
private:
    std::vector<EnemyFighter> enemies;
};






#endif