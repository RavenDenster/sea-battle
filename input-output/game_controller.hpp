#include "game_controller.h"

template<typename InputMethod, typename RendererField, typename RendererMessage>
void GameController<InputMethod, RendererField, RendererMessage>::initialize_commands() {
    commands["attack"] = [&]() { 
        game.user_attack();
        renderer_tracker.update("get_new_ability");
        renderer_tracker.update("new_game");
    };
    commands["state_my_ships"] = [&]() { renderer_tracker.update("state_my_ships"); };
    commands["state_enemy_ships"] = [&]() { renderer_tracker.update("state_enemy_ships"); };
    commands["end"] = [&]() { game.end(); };
    commands["fields"] = [&]() { renderer_tracker.update("fields"); };
    commands["show_enemy_ships"] = [&]() { renderer_tracker.update("show_enemy_ships"); };
    commands["show_my_ships"] = [&]() { renderer_tracker.update("show_my_ships"); };
    commands["show_json_file"] = [&]() { renderer_tracker.update("show_json_file"); };
    commands["change_json_file"] = [&]() { game.change_json_file(); };
    commands["next_ability"] = [&]() { renderer_tracker.update("next_ability"); };
    commands["save_game"] = [&]() { game.save_game(); };
    commands["load_game"] = [&]() { game.load_game(); };
    commands["apply_ability"] = [&]() { 
        game.apply_ability(); 
        renderer_tracker.update("apply_ability");
    };
    commands["help"] = [&]() { renderer_tracker.update("help"); };
}

template<typename InputMethod, typename RendererField, typename RendererMessage>
void GameController<InputMethod, RendererField, RendererMessage>::run() {
    game.play();
    while (true) {
        std::string input = input_method.get_input();
        if (commands.find(input) != commands.end()) {
            commands[input]();
        } else {
            std::cout << "Unknown command!" << std::endl;
        }
        if (!game.trigger_bot_attack) continue;
        game.computer_turn();
        game.check_game_state();
        renderer_tracker.update("attack_message"); 
        renderer_tracker.update("fields");
    }   
}
