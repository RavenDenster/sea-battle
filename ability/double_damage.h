#ifndef DOUBLE_DAMAGE_H_
#define DOUBLE_DAMAGE_H_

#include "ability.h"

class DoubleDamage : public Ability {
public:
    bool apply(GameField& field, int x, int y, ShipManager& manager) override;
};

#endif