/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 4cd2d66df3154b6c8b0ff27aa6791edb
 *
 * Michael Hymowitz, Teddy Sweeney
 * mhymo, tsween
 *
 * Project 4: Battleship
 *
 * Contains function definitions for the class Player.
 */

#include <fstream>

#include "Player.h"


Player::Player() {
    name = "";
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

Player::Player(string name_val) {
    name = name_val;
    num_ships = 0;
    remaining_ships = 0;
    init_grid();
}

void Player::init_grid() {
    for (int i = 0; i < MAX_GRID_SIZE; ++i) {
        for (int j = 0; j < MAX_GRID_SIZE; ++j) {
            grid[i][j] = EMPTY_LETTER;
            opponent_grid[i][j] = EMPTY_LETTER;
        }
    }
    return;
}

string Player::get_name() {
    return name;
}

int Player::get_num_ships() {
    return num_ships;
}

int Player::get_remaining_ships() {
    return remaining_ships;
}

char Player::get_grid_at(int row, int col) {
    return grid[row][col];
}

char Player::get_opponent_grid_at(int row, int col) {
    return opponent_grid[row][col];
}

void Player::add_ship(Ship ship) {
    if (num_ships >= MAX_NUM_SHIPS) {
        return;
    }
    else {
        ++num_ships;
        ++remaining_ships;
        Position shipStart = ship.get_start();
        Position shipEnd = ship.get_end();
        ships[(num_ships - 1)] = ship;
        if (shipStart.get_col() == shipEnd.get_col()) {
            if (shipStart.get_row() <= shipEnd.get_row()) {
                for (int i = shipStart.get_row(); i <= shipEnd.get_row();
                     ++i) {
                    grid[i][shipStart.get_col()] = SHIP_LETTER;
                }
            }
            else {
                for (int i = shipEnd.get_row(); i <= shipStart.get_row();
                     ++i) {
                    grid[i][shipStart.get_col()] = SHIP_LETTER;
                }
            }
        }
        else if (shipStart.get_row() == shipEnd.get_row()) {
            if (shipStart.get_col() <= shipEnd.get_col()) {
                for (int i = shipStart.get_col(); i <= shipEnd.get_col();
                     ++i) {
                    grid[shipStart.get_row()][i] = SHIP_LETTER;
                }
            }
            else {
                for (int i = shipEnd.get_col(); i <= shipStart.get_col();
                     ++i) {
                    grid[shipStart.get_row()][i] = SHIP_LETTER;
                }
            }
        }
    }
    return;
}

bool Player::position_not_hit(Position pos) {
    if (grid[pos.get_row()][pos.get_col()] == EMPTY_LETTER ||
        grid[pos.get_row()][pos.get_col()] == SHIP_LETTER) {
        return true;
    }
    return false;
}

void Player::attack(Player &opponent, Position pos) {
    if (opponent.position_not_hit(pos)) {
        if (opponent.get_grid_at(pos.get_row(), pos.get_col())
                == SHIP_LETTER) {
            
            opponent.grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
            opponent_grid[pos.get_row()][pos.get_col()] = HIT_LETTER;
            cout << name << " " << pos << " hit" << endl;
            int shipNum = 0;
            for (int i = 0; i < MAX_NUM_SHIPS; ++i) {
                if (opponent.ships[i].has_position(pos)) {
                    shipNum = i;
                }
            }
            opponent.ships[shipNum].hit();
            if (opponent.ships[shipNum].has_sunk()) {
                announce_ship_sunk(opponent.ships[shipNum].get_size());
                opponent.remaining_ships -= 1;
            }
        }
        else {
            opponent.grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
            opponent_grid[pos.get_row()][pos.get_col()] = MISS_LETTER;
            cout << name << " (" << pos.get_row() << ',' 
                 << pos.get_col() << ") miss" << endl;
        }
    }
    return;
}

void Player::announce_ship_sunk(int size) {
    cout << "Congratulations " << name << "! You sunk a ";
    if (size == 2) {
        cout << "Destroyer";
    }
    else if (size == 3) {
        cout << "Submarine";
    }
    else if (size == 4) {
        cout << "Battleship";
    }
    else {
        cout << "Carrier";
    }
    cout << endl;
    return;
}

bool Player::load_grid_file(string filename) {
    ifstream inputData;
    inputData.open(filename);
    bool result = false;
    char rowInput;
    char colInput;
    while (inputData.good()) {
        result = true;
        inputData >> rowInput;
        if (rowInput == '(') {
            char filler;
            inputData >> rowInput >> filler >> colInput >> filler;
            Position startPos(rowInput, colInput);
            inputData >> filler >> filler >> rowInput >> filler >> colInput;
            Position endPos(rowInput, colInput);
            Ship ship_in(startPos, endPos);
            add_ship(ship_in);
        }
        else {
            inputData >> colInput;
            Position startPos(rowInput, colInput);
            char filler;
            inputData >> filler >> rowInput >> colInput;
            Position endPos(rowInput, colInput);
            Ship ship_in(startPos, endPos);
            add_ship(ship_in);
        }
    }
    return result;
}


bool Player::destroyed() {
    if (remaining_ships == 0) {
        return true;
    }
    return false;
}

// Your code goes above this line.
// Don't change the implementations below!

void Player::print_grid() {
    ::print_grid(grid);
}

void Player::print_opponent_grid() {
    ::print_grid(opponent_grid);
}
