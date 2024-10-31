cmake_minimum_required(VERSION 3.25)
project(seabattle)
set(CMAKE_CXX_STANDARD 17)
find_package(nlohmann_json 3.11.2 REQUIRED)

file(GLOB SRCFILES "*.cpp")

add_executable(seabattle main.cpp input-output/terminal_input.cpp input-output/input_handler.cpp input-output/game_controller.cpp ability/ability.cpp ability/bombard.cpp ability/scanner.cpp ability/double_damage.cpp renderer-elements/field_renderer.cpp save-load/game_state.cpp save-load/file_handler.cpp renderer-elements/draw_field.cpp renderer-elements/message_render.cpp renderer-elements/game_message.cpp)
target_sources(seabattle PRIVATE ${SRCFILES})

target_link_libraries(seabattle sfml-graphics sfml-window sfml-system)
