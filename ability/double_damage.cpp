#include "double_damage.h"
#include "../game_field.h"
#include "../ship_manager.h"

bool DoubleDamage::apply(GameField& field, int x, int y, ShipManager& manager) {
    field.set_double_damage(true);
    return 1;
}