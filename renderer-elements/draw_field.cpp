#include "draw_field.h"

void DrawField::print_with_fog_war(GameField& field, ShipManager& manager, bool trigger) {
    cout << endl;
    if(trigger == 0) cout << "User field" << endl;
    else cout << "Enemy field" << endl;
    cout << "  "; 
    
    for (int x = 0; x < field.get_width(); x++) {
        cout << " " << x; 
    }
    cout << endl;
    
    for (int y = 0; y < field.get_height(); y++) {
        cout << y << " ";
        
        for (int x = 0; x < field.get_width(); x++) {
            bool is_hitx2 = false;
            bool is_hitx1 = false;

            for (int i = 0; i < field.count_ships; ++i) {
                Ship& ship = manager.get_ship(i);
                int ship_length = ship.get_length();
                bool is_vertical = ship.is_vertical_orientation();

                if (is_vertical) {
                    if (x == ship.get_x()) {
                        for (int j = 0; j < ship_length; ++j) {
                            if (y == ship.get_y() + j && ship.get_segment_state(j) == 2) {
                                is_hitx2 = true;
                                break;
                            }
                            if (y == ship.get_y() + j && ship.get_segment_state(j) == 1) {
                                is_hitx1 = true;
                                break;
                            }
                        }
                    }
                } else {
                    if (y == ship.get_y()) {
                        for (int j = 0; j < ship_length; ++j) {
                            if (x == ship.get_x() + j && ship.get_segment_state(j) == 2) {
                                is_hitx2 = true;
                                break;
                            }
                            if (x == ship.get_x() + j && ship.get_segment_state(j) == 1) {
                                is_hitx1 = true;
                                break;
                            }
                        }
                    }
                }
                if (is_hitx2 || is_hitx1) break;
            }
            
            if (field.get_cell_status(y, x) == 0) {
                cout << BLUE_SQUARE ; 
            } else if (field.get_cell_status(y, x) == 1) {
                cout << WHITE_SQUARE ; 
            } else if (is_hitx2) {
                cout << RED_SQUARE ; 
            } else if (is_hitx1) {
                cout << ORANGE_SQUARE ; 
            } else {
                cout << BLUE_SQUARE ; 
            }
        }
        cout << endl;
    }
}

void DrawField::print_all_ship(GameField& field) {
    cout << endl;
    cout << "Ships on the field: " << endl;
    cout << "  "; 
    
    for (int x = 0; x < field.get_width(); x++) {
        cout << " " << x; 
    }
    cout << endl;
    for(int x = 0; x < field.get_height(); x++) {
        cout << x << " ";
        for(int y = 0; y < field.get_height(); y++) {
            if(field.get_cell_status(x,y) == 2) {
                cout << RED_SQUARE;
            } else if (field.get_cell_status(x,y) == 0 || field.get_cell_status(x,y) == 1) {
                cout << BLUE_SQUARE;
            }
        }
        cout << endl;
    }
}

void DrawField::print(ShipManager& manager) {
    vector<unique_ptr<Ship>>& ships = manager.get_ships();
    for(int i = 0; i < ships.size(); i++) {
        Ship& ship = *ships[i];
        int len_ship = ship.get_length();
        int count_destroy = 0;
        cout << "Ship " << i+1 <<": ";
        for(int i = 0; i < len_ship; i++) {
            int state = ship.get_segment_state(i);
            if(state == 0) {
                cout << "w"; // whole
            } else if (state == 1) {
                cout << "1h"; // 1 hit
            } else if (state == 2) {
                cout << "d"; // destroy 
                count_destroy++;
            }
            cout << " ";
        }
        if(count_destroy == len_ship) {
            cout << " " << "Ship destroy";
        }
        cout << endl;
    }
}