#include <nlohmann/json.hpp>
#include <iostream>
#include <map>
#include <functional>
#include <utility> 
#include "../ship_manager.h"
#include "../ship.h"
#include "../save-load/game_state.h"
#include "../game_field.h"
#include "input_handler.h"
#include "../exception.h"

using namespace std;
using json = nlohmann::json;


class TerminalInput {
private:
    InputHandler input_handler;
    map<string, string> command_map; 
    map<string, string> key_map;     

public:
    TerminalInput() { load_commands("commands.json"); }

    void load_commands(const string& filename);

    string get_input();

    string get_command(const string& input);
};