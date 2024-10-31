#ifndef ABILITY_H_
#define ABILITY_H_

using namespace std;

class ShipManager;
class GameField;

class Ability {
public:
    virtual bool apply(GameField& field, int x, int y, ShipManager& manager) = 0;
    virtual ~Ability() {}
};

#endif
