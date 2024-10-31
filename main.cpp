#include <iostream>
#include <stdexcept>
#include "game.h"
#include "input-output/terminal_input.h"
#include "renderer-elements/field_renderer.h"
#include "renderer-elements/message_render.h"
#include "input-output/game_controller.h"

using namespace std;
class Game;

int main() {
    try {
        Game game;
        GameController<TerminalInput, FieldRenderer, MessageRender> controller(game);

        controller.run();
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }
    return 0;
}
 
// 4 5
// 0 0
// 2 3
// 7 7
// 2 8
// 8 2
// 0 7 v
// 0 5
// 6 0
// 8 5