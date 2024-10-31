#include "message_render.h"


void MessageRender::attack_message(Game &game) {
    GameMessage message;
    auto user_data = game.user_object();
    auto enemy_data = game.enemy_object();

    message.message_attack_user(enemy_data.first);
    message.message_attack_enemy(user_data.first);
} 

void MessageRender::show_json(Game &game) {
    GameState& state = game.get_game_state();
    cout << state << endl;
}

void MessageRender::apply_ability(Game &game) {
    GameMessage message;
    message.message_apply_ability(game.abil);
}

void MessageRender::next_ability(Game &game) {
    GameMessage message;
    AbilityManager& ability_manager = game.get_ability_manager();
    string name_ability = ability_manager.next_abilities();
    message.message_next_ability(name_ability);
}

void MessageRender::get_ability(Game &game) {
    GameMessage message;
    AbilityManager& ability_manager = game.get_ability_manager();
    int value = ability_manager.get_is_grand_random_ability();
    message.get_new_ability(ability_manager, value);
}

void MessageRender::help() {
    GameMessage message;
    message.help_message();
}