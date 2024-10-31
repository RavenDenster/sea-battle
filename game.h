#ifndef GAME_H_
#define GAME_H_

#include <nlohmann/json.hpp>
#include <iostream>
#include <map>
#include <functional>
#include <utility> 
#include "ship_manager.h"
#include "ship.h"
#include "ability_manager.h"
#include "renderer-elements/draw_field.h"
#include "renderer-elements/game_message.h"
#include "input-output/input_handler.h"
#include "save-load/game_state.h"
#include "message_game_enum.cpp"
#include "game_field.h"
#include "exception.h"

using namespace std;
using json = nlohmann::json;

class Game {
private:
    GameField field_user;
    GameField field_enemy;
    ShipManager ship_manager_enemy;
    AbilityManager ability_manager;
    ShipManager ship_manager_user;
    GameState state;
    GameMessage game_message;
    InputHandler input_handler;

public:
    bool trigger_bot_attack = false;
    pair<string, bool> abil;

    Game() : field_user(0, 0, false), field_enemy(0, 0, true), ship_manager_enemy(field_enemy.calculation_count_ships()), ship_manager_user(field_user.calculation_count_ships()), state("data_game.json") {}

    void start_new_game();

    void generate_enemy_ships();

    void computer_turn();

    pair<GameField&, ShipManager&> user_object() { return make_pair(ref(field_user), ref(ship_manager_user));  }

    pair<GameField&, ShipManager&> enemy_object() { return make_pair(ref(field_enemy), ref(ship_manager_enemy)); }

    AbilityManager& get_ability_manager() { return ability_manager; }

    GameState& get_game_state() { return state; }

    void user_attack();

    void end() { exit(0); }

    void change_json_file() { cin >> state; }
    
    void apply_ability();

    void check_game_state();

    void save_game() { state.save(field_user, field_enemy, ship_manager_user, ship_manager_enemy, ability_manager); }

    void load_game() { state.load(field_user, field_enemy, ship_manager_user, ship_manager_enemy, ability_manager); }

    void play();
};



#endif