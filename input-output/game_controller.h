#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include <iostream>
#include <map>
#include <functional>
#include "../renderer-elements/draw_field.h"
#include "../renderer-elements/game_message.h"
#include "../save-load/game_state.h"
#include "../game_field.h"
#include "game_renderer.h"
#include "render_tracker.h"
#include "../game.h"

template<typename InputMethod, typename RendererField, typename RendererMessage>
class GameController {
private:
    Game &game;
    InputMethod input_method;
    RendererTracker<RendererField, RendererMessage> renderer_tracker;
    std::map<std::string, std::function<void()>> commands;

public:
    GameController(Game &g) : game(g), renderer_tracker(g) { initialize_commands(); }
    
    void initialize_commands();
    
    void run();
};

#include "game_controller.hpp"

#endif 