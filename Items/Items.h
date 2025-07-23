#ifndef ITEMS_H
#define ITEMS_H
#include "../Types/Types.h"
#include <string>

struct Item {
    std::string name;
    std::string description;
    
};

const std::vector<Item> all_items = std::vector<Item>{
    Item{"Sword","Tha Sword"},
    Item{"Shield","Shield xD"},
    Item{"Gold Coin","Gold"}
};
// class Item{
// public:
//     std::string name;
//     std::string description;
// };







#endif