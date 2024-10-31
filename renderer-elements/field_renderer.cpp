#include "field_renderer.h"

void FieldRenderer::draw_field(Game &game) {
    DrawField field;
    auto user_data = game.user_object();
    auto enemy_data = game.enemy_object();

    field.print_with_fog_war(user_data.first, user_data.second, 0);
    field.print_with_fog_war(enemy_data.first, enemy_data.second, 1);
}

void FieldRenderer::state_ship(Game &game, bool trigger) {
    DrawField field;
    auto user_data = game.user_object();
    auto enemy_data = game.enemy_object();

    if(trigger == 0) {
        field.print(enemy_data.second);
    } else {
        field.print(user_data.second);
    }
}

void FieldRenderer::show_all_ship(Game &game, bool trigger) {
    DrawField field;
    auto user_data = game.user_object();
    auto enemy_data = game.enemy_object();

    if(trigger == 0) {
        field.print_all_ship(enemy_data.first);
    } else {
        field.print_all_ship(user_data.first);
    }
}