#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include <SFML/Graphics.hpp>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <set>
#include <utility> 
#include <algorithm>
#include <sstream>
#include <random> 
#include <string>
#include <fstream>
#include "save-load/game_state.h"
#include "game.h"

void Game::start_new_game() {
    int width_field;
    int height_field;

    while (true) {
        game_message.message_from_start(GameMessageEnum::INPUT_WIDTH);
        string input = input_handler.input();
        stringstream ss(input);
        if (ss >> width_field) {
            break; 
        } else {
            game_message.message_from_start(GameMessageEnum::INVALID_INPUT);
        }
    }

    while (true) {
        game_message.message_from_start(GameMessageEnum::INPUT_HEIGHT);
        string input = input_handler.input();
        stringstream ss(input);
        if (ss >> height_field) {
            break; 
        } else {
            game_message.message_from_start(GameMessageEnum::INVALID_INPUT);
        }
    }
    
    field_user = GameField(width_field, height_field, false);
    field_enemy = GameField(width_field, height_field, true);
    ship_manager_enemy = field_enemy.calculation_count_ships();
    ship_manager_user = field_user.calculation_count_ships();
    int count_ships = field_user.count_ships;

    for (int i = 0; i < count_ships; i++) {
        Ship& ship = ship_manager_user.get_ship(i);
        int x, y;
        string orientation = "dont have";

        while (true) {
            game_message.message_from_start(GameMessageEnum::INPUT_COORDINATE);
            string input_line = input_handler.input();

            stringstream ss(input_line);
            ss >> x >> y;

            if (ss.fail() || ss.bad() || x < 0 || y < 0) {
                game_message.message_from_start(GameMessageEnum::INVALID_COORDINATE);
                continue;
            }

            if (ss.peek() != EOF) { 
                ss >> orientation; 
            }

            try {
                field_user.place_ship(ship, x, y, orientation);
                break;
            } catch (const exception& e) {
                cerr << e.what() << endl;
                game_message.message_from_start(GameMessageEnum::RE_ENTER_COORDINATE);
            }
        }
    }

    generate_enemy_ships();
}

void Game::generate_enemy_ships() {
    srand(static_cast<unsigned int>(time(NULL)));

    int width = field_enemy.get_width();
    int height = field_enemy.get_height();
    vector<vector<int>> field_mark(height, vector<int>(width, 0)); 
    
    for (int i = 0; i < ship_manager_enemy.get_ships_count(); i++) {
        Ship& ship = ship_manager_enemy.get_ship(i);
        int length = ship.get_length();
        bool placed = false;
        
        while (!placed) {
            int x = rand() % width;
            int y = rand() % height;
            string orientation = (rand() % 2 == 0) ? "h" : "v"; 
            bool canPlace = true;

            if (x > width || y > height || x < 0 || y < 0 || x+length > width || y+length > height) {
                continue; 
            }

            for (int j = 0; j < length; j++) {
                int check_x = (orientation == "h") ? x + j : x;
                int check_y = (orientation == "h") ? y : y + j;

                if (check_x >= 0 && check_x < width && check_y >= 0 && check_y < height) {
                    if (field_mark[check_y][check_x] != 0) {
                        canPlace = false;
                        break; 
                    }
                } else {
                    canPlace = false;
                    break;
                }
            }

            if (canPlace) {
                for (int j = 0; j < length; j++) {
                    int place_x = (orientation == "h") ? x + j : x;
                    int place_y = (orientation == "h") ? y : y + j;
                    field_mark[place_y][place_x] = 1;
                }

                for (int j = -1; j <= length; j++) {
                    for (int k = -1; k <= 1; k++) {
                        int startX = (orientation == "v") ? x + k : x + j;
                        int startY = (orientation == "v") ? y + j : y + k;

                        if (startX >= 0 && startX < width && startY >= 0 && startY < height) {
                            field_mark[startY][startX] = 1;
                        }
                    }
                }  

                field_enemy.place_ship(ship, x, y, orientation); 
                placed = true; 
            }
        }
    }
}

void Game::apply_ability() {
    string message = ability_manager.next_abilities();
    bool trigger = 0;
    if(message == "DoubleDamage") {
        trigger = ability_manager.apply_ability(field_enemy, 0, 0, ship_manager_enemy);
    } else if (message == "Scanner") {
        int x, y;
        game_message.game_message(GameMessageEnum::SCANNER_COORDINATE);
        string input = input_handler.input();
        stringstream ss(input);
        ss >> x >> y;
        trigger = ability_manager.apply_ability(field_enemy, x, y, ship_manager_enemy);
    } else if (message == "Bombard") {
        trigger = ability_manager.apply_ability(field_enemy, 0, 0, ship_manager_enemy);
    }
    abil = make_pair(message, trigger);
}

void Game::user_attack() {
    trigger_bot_attack = true;
    int x = -1, y = -1;

    while (true) {
        game_message.game_message(GameMessageEnum::ATTACK_COORDINATE);
        string input = input_handler.input();

        stringstream ss(input);
        ss >> x >> y;
        
        if (ss.fail() || ss.bad() || ss.peek() != EOF) {
            game_message.game_message(GameMessageEnum::INVALID_COORDINATE_FOR_ATTACK);
            continue;
        }

        try {
            field_enemy.attack_cell(x, y, ship_manager_enemy, ability_manager);
            break;
        } catch (const OutOfBoundsException&) {
            game_message.game_message(GameMessageEnum::COORDINATE_OUT_OF_RANGE);
        } catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }
}

void Game::computer_turn() {
    static vector<pair<int, int>> attack_queue;
    static bool focusing_on_ship = false;
    static int last_hit_x, last_hit_y;
    static vector<pair<int, int>> attacked_cells; 
    static bool next_target_cell = false;
    static int next_target_x, next_target_y;
    trigger_bot_attack = false;

    if(next_target_cell == true) {
        field_user.attack_cell(next_target_x, next_target_y, ship_manager_user, ability_manager);
        next_target_cell = false;
        return;
    }

    if (focusing_on_ship && !attack_queue.empty()) {
        auto target = attack_queue.back();
        attack_queue.pop_back();
        bool hit = field_user.attack_cell(target.first, target.second, ship_manager_user, ability_manager);
        if(hit) {
            next_target_cell = true;
            next_target_x = target.first;
            next_target_y = target.second;
        }
        attacked_cells.emplace_back(target.first, target.second); 
        return; 
    }

    int x, y;
    bool valid_attack = false;

    while (!valid_attack) {
        x = rand() % field_user.get_width(); 
        y = rand() % field_user.get_height();

        bool already_attacked = false;
        for (const auto& cell : attacked_cells) {
            if (cell.first == x && cell.second == y) {
                already_attacked = true;
                break;
            }
        }

        if (!already_attacked) {
            valid_attack = true; 
        }
    }

    bool hit = field_user.attack_cell(x, y, ship_manager_user, ability_manager);
    
    if(hit) {
        next_target_cell = true;
        next_target_x = x;
        next_target_y = y;
    }

    attacked_cells.emplace_back(x, y);

    if (hit) {
        focusing_on_ship = true; 
        last_hit_x = x;
        last_hit_y = y;

        vector<pair<int, int>> directions = {
            {1, 0},  // вниз
            {-1, 0}, // вверх
            {0, 1},  // вправо
            {0, -1}  // влево
        };

        for (const auto& dir : directions) {
            int new_x = last_hit_x + dir.first;
            int new_y = last_hit_y + dir.second;

            bool flag = true;
            if (new_x >= 0 && new_x < field_user.get_width() && new_y >= 0 && new_y < field_user.get_height()) {
                for (const auto& cell : attacked_cells) {
                    if (cell.first == new_x && cell.second == new_y) {
                        flag = false;
                    }
                }
                if(flag)
                    attack_queue.emplace_back(new_x, new_y);
            }
        }
    } else {
        focusing_on_ship = false;
    }
    check_game_state();
}

void Game::check_game_state() {
    if (ship_manager_user.all_ships_destroy()) {
        game_message.message_game_state(GameMessageEnum::LOST);
        game_message.message_game_state(GameMessageEnum::QUES_START_NEW_GAME);
        string answer = input_handler.input();
        if(answer == "yes") {
            game_message.message_game_state(GameMessageEnum::START_NEW_GAME);
            ability_manager.new_ability();
            start_new_game();
        } else {
            exit(0);
        }
    }  else if (ship_manager_enemy.all_ships_destroy()) {
        game_message.message_game_state(GameMessageEnum::WIN);
        game_message.message_game_state(GameMessageEnum::QUES_START_NEW_ROUND);
        string answer = input_handler.input();
        if(answer == "yes") {
            game_message.message_game_state(GameMessageEnum::START_NEW_ROUND);
            ship_manager_enemy.new_ships();
            field_enemy.clean(); 
            generate_enemy_ships();
        } else {
            exit(0);
        }
    }
}

void Game::play() {
    if(state.is_file_written()) {
        game_message.game_message(GameMessageEnum::OPTION_LOAD_GAME);
        string answer = input_handler.input();
        if(answer == "yes") {
            load_game();
        } else {
            start_new_game();
        }
    } else {
        start_new_game();
    }
}