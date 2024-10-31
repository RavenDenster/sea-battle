#include "scanner.h"
#include "../game_field.h"
#include "../ship_manager.h"

bool Scanner::apply(GameField& field, int x, int y, ShipManager& manager) {
    bool foundShip = false;

    for(int i = x; i < x + 2; ++i) {
        for(int j = y; j < y + 2; ++j) {
            if(i < field.get_height() && j < field.get_width()) {
                if(field.get_cell_status(j, i) == 2) {
                    foundShip = true;
                    break;
                }
            }
        }
        if (foundShip) break;
    } 

    if (foundShip) {
        return 1; // "Ship detected in the area";
    } else {
        return 0; // "No ships in the area";
    }
} 
