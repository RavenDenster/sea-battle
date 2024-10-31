#ifndef MESSAGE_RENDERER_H_
#define MESSAGE_RENDERER_H_

#include <iostream>
#include <utility> 
#include "../game.h"

class MessageRender {
public:
    void attack_message(Game &game);

    void show_json(Game &game);

    void apply_ability(Game &game);

    void next_ability(Game &game);

    void get_ability(Game &game);

    void help();
};

#endif