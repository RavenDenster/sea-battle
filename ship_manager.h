#ifndef SHIP_MANAGER_H_
#define SHIP_MANAGER_H_

#include <iostream>
#include <vector>
#include <stdexcept>
#include <memory>
#include "ship.h"
#include "game_field.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std;
class Ship;
class ShipManager {

private:
    vector<unique_ptr<Ship>> ships;
    int count;
public:
    ShipManager(int count, const vector<int>& sizes) : count(count) {
        if (count != sizes.size()) {
            throw invalid_argument("Count of ships must match sizes vector.");
        }
        for (int size : sizes) {
            ships.emplace_back(make_unique<Ship>(size, size % 2 == 0));
        }
    }

    int get_ships_count() {return count;}

    Ship& get_ship(int index) const { return *ships[index]; }

    bool all_ships_destroy();

    json to_json() const;

    vector<unique_ptr<Ship>> & get_ships(){
        return ships;
    }

    void from_json(const json& j, GameField& field);

    void new_ships();
};

#endif