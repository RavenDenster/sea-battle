#include "bombard.h"
#include "../game_field.h"
#include "../ship_manager.h"
#include "../ship.h"

bool Bombard::apply(GameField& field, int x, int y, ShipManager& manager) {
    srand(time(NULL));

    if(manager.get_ships_count() > 0) {
        Ship* target_ship = nullptr;
        int random_index;

        do {
            random_index = rand() % manager.get_ships_count();
            target_ship = &manager.get_ship(random_index);
        } while(target_ship->is_destroy());

        int segment_index;
        do {
            segment_index = rand() % target_ship->get_length();
        } while(target_ship->get_segment_state(segment_index) != 0);

        target_ship->damage_secret_segment(segment_index);

        // cout << "Bombard dealt damage to ship at number " << random_index + 1 
        //      << " segment " << segment_index + 1 << endl;
    } 
    return 1;
}
