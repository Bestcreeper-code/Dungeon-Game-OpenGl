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
    void Start(std::vector<unsigned short> combo, int time, void (*callback)(int hit_amount,void* callb_args),void* callback_args, size_t args_size);
    void displayMenu() override;
    void update() override;
    char Combosize(){return combodata.size();};
private:
    std::vector<unsigned short> combodata;    
    int correct_inputs_amount = 0;
    int time_left = 0;
    void (*callback_func)(int,void*);
    void* callbackdata;
    int start_max_time = 0;
};

std::vector<unsigned short> Generate_Random_Key_Combo(char size);

#endif