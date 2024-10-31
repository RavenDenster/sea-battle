#include "game_message.h"

void GameMessage::message_attack_user(GameField& field) {
    if(field.get_last_attemp_user() == 0) {
        cout << "You miss!" << endl;
    } else {
        cout << "You hit!" << endl;
    }
}

void GameMessage::message_attack_enemy(GameField& field) {
    if(field.get_last_attemp_enemy() == 0) {
        cout << "Bot miss!" << endl;
    } else {
        cout << "Bot hit!" << endl;
    }
}

void GameMessage::message_apply_ability(pair<string, bool> ability) {
    if(ability.first == "DoubleDamage") {
        cout << "DoubleDamage" << endl;
        if(ability.second == 1) cout << "Next hit deals double damage" << endl;
    } else if(ability.first == "Scanner") {
        cout << "Scanner" << endl;
        if(ability.second == 0) cout << "No ships in the area" << endl;
        else if (ability.second == 1) cout << "Ship detected in the area" << endl;
    } else if (ability.first == "Bombard") {
        cout << "Bombard" << endl;
    } else {
        cout << "No abilities available." << endl;
    }
}

void GameMessage::message_next_ability(string ability) {
    cout << "Next ability: ";
    cout << ability << endl;
}

void GameMessage::get_new_ability(AbilityManager& ability_manager, int value) {
    if(value == 1) {
        cout << "New ability gained." << endl;
        ability_manager.set_is_grand_random_ability(0);
    }
}

void GameMessage::help_message() {
    cout << "attack - attack someone cell" << "\n" << "state_my_ships - a detailed description of my ships" << "\n" 
    << "state_enemy_ships - a detailed description of enemy ships" << "\n" << "end - end the game" << "\n"
    << "show_enemy_ships - hack to view enemy ships" << "\n" << "show_my_ships - view just my ships" << "\n"
    << "show_json_file - view the contents of the saved file" << "\n" << "change_json_file - change the contents of the file with saving" << "\n"
    << "fields - view the playing fields" << "\n" << "abilities - look next ability" << "\n" << "stop_game - the command to control serialization" << "\n"
    << "apply_ability - apply ability" << endl;
}

void GameMessage::message_from_start(GameMessageEnum command) {
    switch(command) {
        case GameMessageEnum::INPUT_WIDTH:
            cout << "Enter field width: ";
            break;
        case GameMessageEnum::INPUT_HEIGHT:
            cout << "Enter field height: ";
            break;
        case GameMessageEnum::INVALID_INPUT:
            cout << "Invalid input. Please enter a positive integer." << endl;
            break;
        case GameMessageEnum::INPUT_COORDINATE:
            cout << "Enter coordinates of the ship and orientation: ";
            break;
        case GameMessageEnum::INVALID_COORDINATE:
            cout << "Invalid input for coordinates. Please enter valid integers." << endl;
            break;
        case GameMessageEnum::RE_ENTER_COORDINATE:
            cout << "Please re-enter coordinates of the ship and orientation." << endl;
            break;
    }
}

void GameMessage::game_message(GameMessageEnum command) {
     switch(command) {
        case GameMessageEnum::ATTACK_COORDINATE:
            cout << "Coordinate for attack: ";
            break;
        case GameMessageEnum::SCANNER_COORDINATE:
            cout << "Coordinate for ability: ";
            break;
        case GameMessageEnum::OPTION_LOAD_GAME:
            cout << "Do you want load game?" << endl;
            break;
        case GameMessageEnum::COORDINATE_OUT_OF_RANGE:
            cout << "Attack coordinates are out of range. Please enter valid coordinates." << endl;
            break;
        case GameMessageEnum::INVALID_COORDINATE_FOR_ATTACK:
            cout << "Invalid input. Please enter valid integers for coordinates." << endl;
            break;
    }
}

void GameMessage::message_game_state(GameMessageEnum command) {
    switch(command) {
        case GameMessageEnum::LOST:
            cout << "You lost!" << endl;
            break;
        case GameMessageEnum::QUES_START_NEW_GAME:
            cout << "Do you want to start a new game: " << endl;
            break;
        case GameMessageEnum::START_NEW_GAME:
            cout << "Starting a new game." << endl;
            break;
        case GameMessageEnum::WIN:
            cout << "You won this round!" << endl;
            break;
        case GameMessageEnum::QUES_START_NEW_ROUND:
            cout << "Do you want to start a new round: ";
            break;
        case GameMessageEnum::START_NEW_ROUND:
            cout << "Starting the next round." << endl;
            break;
    }
}