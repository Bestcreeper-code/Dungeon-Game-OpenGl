#ifndef MENUS_H
#define MENUS_H
#include "../../Items/Items.h"
#include "../../ImageManager/ImageManager.hpp"
class Menu
{
public:

virtual void displayMenu();
virtual void update();
protected:
    bool Shown;
};

class Inventory : public Menu
{
public:
    Inventory();
    void displayMenu() override;
    void update() override;

};



class ComboInputUi : public Menu
{
public:
    ComboInputUi();
    void Start(std::vector<unsigned short> combo, int time, void (*callback)(int));
    void displayMenu() override;
    void update() override;
private:
    std::vector<unsigned short> combodata;    
    int correct_inputs_amount = 0;
    int time_left = 0;
    void (*callback_func)(int);
    int start_max_time = 0;
};

#endif