#include "game_renderer.h"

template<typename RendererField, typename RendererMessage>
void GameRenderer<RendererField, RendererMessage>::render(const std::string &command) {
    if (command == "fields") {
        renderer_field.draw_field(game);
    } else if (command == "attack_message") {
        renderer_message.attack_message(game);
    } else if (command == "state_my_ships") {
        renderer_field.state_ship(game, 1);
    } else if (command == "state_enemy_ships") {
        renderer_field.state_ship(game, 0);
    } else if (command == "show_enemy_ships") {
        renderer_field.show_all_ship(game, 0);
    } else if (command == "show_my_ships") {
        renderer_field.show_all_ship(game, 1);
    } else if (command == "show_json_file") {
        renderer_message.show_json(game);
    } else if (command == "apply_ability") {
        renderer_message.apply_ability(game);
    } else if (command == "next_ability") {
        renderer_message.next_ability(game);
    } else if (command == "get_new_ability") {
        renderer_message.get_ability(game);
    } else if (command == "help") {
        renderer_message.help();
    } 
}

template<typename RendererField, typename RendererMessage>
void GameRenderer<RendererField, RendererMessage>::update(const std::string &command) {
    render(command);
}
