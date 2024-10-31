#include "input_handler.h"

string InputHandler::input() {
    string input;
    getline(cin, input);
    return input;
}