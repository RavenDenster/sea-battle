#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../ship_manager.h"
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../ship.h"
#include "../ability_manager.h"
#include "file_handler.h"
#include "../game_field.h"

using namespace std;
using json = nlohmann::json;

class GameState {
private:
    string filename;
    json saved_data;

public:
    GameState(const string& fname) : filename(fname) { }

    void save( GameField& field_user, GameField& field_enemy, 
    ShipManager& ship_manager_user, ShipManager& ship_manager_enemy,
    AbilityManager& ability_manager);

    void load(GameField& field_user, GameField& field_enemy, 
    ShipManager& ship_manager_user, ShipManager& ship_manager_enemy,
    AbilityManager& ability_manager);

    void write_state();

    bool is_file_written() const {
        std::ifstream file(filename);
        return file.peek() != std::ifstream::traits_type::eof();
    }

    friend ostream& operator<<(ostream& os, const GameState& game_state) {
        FileHandler file_handler(game_state.filename);
        file_handler.openForRead();

        json j;
        file_handler.read(j);
        
        os << j.dump(4) << endl;
        
        return os;
    }

    friend istream& operator>>(istream& is, GameState& game_state) {
        json j;
        
        is >> j; 
        game_state.saved_data = j;
        if (j.is_null()) {
            throw runtime_error("Failed to read valid JSON data.");
        }
        
        game_state.write_state();

        return is;
    }

};

#endif