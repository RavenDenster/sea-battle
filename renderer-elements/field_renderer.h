#ifndef FIELD_RENDERER_H_
#define FIELD_RENDERER_H_

#include <iostream>
#include <utility> 
#include "../game.h"

class FieldRenderer {
public:
    void draw_field(Game &game);

    void state_ship(Game &game, bool trigger);

    void show_all_ship(Game &game, bool trigger);

};

#endif