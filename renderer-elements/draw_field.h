#ifndef DRAW_FIELD_H_
#define DRAW_FIELD_H_

#include <iostream>
#include <utility> 
#include "../ship_manager.h"
#include "../ship.h"
#include "../game_field.h"

class DrawField {
public:
    const string BLUE_SQUARE = "\033[44m  \033[0m"; 
    const string WHITE_SQUARE = "\033[47m  \033[0m"; 
    const string RED_SQUARE = "\033[41m  \033[0m";  
    const string ORANGE_SQUARE = "\033[48;5;214m  \033[0m";

    void print_with_fog_war(GameField& field, ShipManager& manager, bool trigger);

    void print_all_ship(GameField& field);

    void print(ShipManager& manager);

};

#endif