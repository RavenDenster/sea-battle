#ifndef GAME_MESSAGE_H_
#define GAME_MESSAGE_H_

#include <iostream>
#include <map>
#include <functional>
#include <utility> 
#include "../ship_manager.h"
#include "../ship.h"
#include "../ability_manager.h"
#include "../save-load/game_state.h"
#include "../game_field.h"
#include "../message_game_enum.cpp"

class GameMessage {
public:
    void message_attack_user(GameField& field);

    void message_attack_enemy(GameField& field);

    void message_apply_ability(pair<string, bool> abil);

    void message_next_ability(string ability);

    void get_new_ability(AbilityManager& ability_manager, int value);

    void help_message();

    void message_from_start(GameMessageEnum command);

    void game_message(GameMessageEnum command);

    void message_game_state(GameMessageEnum command);
};

#endif