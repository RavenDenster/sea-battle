#include "render_tracker.h"

template<typename RendererField, typename RendererMessage>
void RendererTracker<RendererField, RendererMessage>::update(const std::string &state) {
    current_state = state;
    game_renderer.update(state);
}

template<typename RendererField, typename RendererMessage>
std::string RendererTracker<RendererField, RendererMessage>::get_current_state() const {
    return current_state;
}