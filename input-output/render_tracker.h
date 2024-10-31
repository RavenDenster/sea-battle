#ifndef RENDER_TRACKER_H_
#define RENDER_TRACKER_H_

#include <string>
#include "../game.h"

template<typename RendererField, typename RendererMessage>
class RendererTracker {
private:
    GameRenderer<RendererField, RendererMessage> game_renderer; 
    std::string current_state; 

public:
    RendererTracker(Game &game) : game_renderer(game), current_state("") {}

    void update(const std::string &state);

    std::string get_current_state() const;
};

#include "render_tracker.hpp" 

#endif