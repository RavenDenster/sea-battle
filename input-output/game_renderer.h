#ifndef GAME_RENDER_H_
#define GAME_RENDER_H_

#include <iostream>
#include <string>
#include "../game.h"

class Game;

template<typename RendererField, typename RendererMessage>
class GameRenderer {
private:
    RendererField renderer_field;
    RendererMessage renderer_message;
    Game &game;

public:
    GameRenderer(Game &g) : game(g) {}

    void render(const std::string &command);

    void update(const std::string &command);
};

#include "game_renderer.hpp" 

#endif 