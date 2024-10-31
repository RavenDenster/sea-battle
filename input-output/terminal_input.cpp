#include "terminal_input.h"

void TerminalInput::load_commands(const string& filename) {
    if (ifstream file{filename}) {
        json j;
        file >> j;

        for (auto& element : j.items()) {
            const string command = element.key();
            const string key = element.value();

            if (key_map.find(key) != key_map.end()) {
                throw invalid_argument("Duplicate key assignment: " + key);
            }

            if (command_map.find(command) != command_map.end()) {
                throw invalid_argument("Duplicate command assignment: " + command);
            }

            command_map[command] = key;
            key_map[key] = command;
        }
    } else {
        cerr << "Error opening " << filename << ", loading default commands." << endl;
        if (ifstream default_file{"default_commands.json"}) {
            json j;
            default_file >> j;

            for (auto& element : j.items()) {
                const string command = element.key();
                const string key = element.value();

                if (key_map.find(key) != key_map.end()) {
                    throw invalid_argument("Duplicate key assignment in default commands: " + key);
                }

                if (command_map.find(command) != command_map.end()) {
                    throw invalid_argument("Duplicate command assignment in default commands: " + command);
                }

                command_map[command] = key;
                key_map[key] = command; 
            }
        } else {
            throw runtime_error("Error opening default command file");
        }
    }
}

string TerminalInput::get_input() {
    while (true) {
        cout << "Enter command: ";
        string input = input_handler.input();

        try {
            return get_command(input);
        } catch (const invalid_argument& e) {
            cerr << e.what() << ". Please try again." << endl;
        }
    }
}

string TerminalInput::get_command(const string& input) {
    if (command_map.find(input) == command_map.end()) {
        throw invalid_argument("Unknown command: " + input);
    }
    return command_map[input];
}