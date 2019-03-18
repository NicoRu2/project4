/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Ship.cpp
 * Project UID 4cd2d66df3154b6c8b0ff27aa6791edb
 *
 * Michael Hymowitz, Teddy Sweeney
 * mhymo, tsween
 *
 * Project 4: Battleship
 *
 * Contains function definitions for the class Ship.
 */

#include <cmath>

#include "Ship.h"


Ship::Ship() {
    start.set_row(0);
    start.set_col(0);
    
    end.set_row(0);
    end.set_col(0);
    
    num_hits = 0;
    size = 0;
}

Ship::Ship(Position start_in, Position end_in) {
    start = start_in;
    end = end_in;
    num_hits = 0;
    
    if(is_horizontal()) {
        size = abs(end.get_col() - start.get_col()) + 1;
    }
    else {
        size = abs(end.get_row() - start.get_row()) + 1;
    }
}

Position Ship::get_start() {
    return start;
}

Position Ship::get_end() {
    return end;
}

int Ship::get_size() {
    return size;
}

bool Ship::is_horizontal() {
    if (start.get_row() == end.get_row()) {
        return true;
    }
    return false;
}

bool Ship::has_position(Position pos) {
    if (pos.get_row() >= start.get_row() && pos.get_row() <= end.get_row()
        && !is_horizontal() && pos.get_col() == start.get_col()) {
        return true;
    }
    else if (pos.get_row() >= end.get_row() && pos.get_row() <= start.get_row()
             && !is_horizontal() && pos.get_col() == start.get_col()) {
        return true;
    }
    else if (pos.get_col() >= start.get_col() && pos.get_col() <= end.get_col()
             && is_horizontal() && pos.get_row() == start.get_row()) {
        return true;
    }
    else if (pos.get_col() >= end.get_col() && pos.get_col() <= start.get_col()
             && is_horizontal() && pos.get_row() == start.get_row()) {
        return true;
    }
    else {
        return false;
    }
}

void Ship::hit() {
    if (num_hits < size) {
        ++num_hits;
    }
    return;
}

bool Ship::has_sunk() {
    if (num_hits == size) {
        return true;
    }
    return false;
}
