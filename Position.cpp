/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Position.cpp
 * Project UID 4cd2d66df3154b6c8b0ff27aa6791edb
 *
 * Michael Hymowitz, Teddy Sweeney
 * mhymo, tsween
 *
 * Project 4: Battleship
 *
 * Contains function definitions for the class Position.
 */

#include "Position.h"
#include "utility.h"


Position::Position() {
    row = 0;
    col = 0;
}

Position::Position(int row_in, int col_in) {
    row = row_in;
    row = check_range(row);
    col = col_in;
    col = check_range(col);
}

Position::Position(char row_in, char col_in) {
    const int NUMBER_TO_INT_CONVERTER = 49;
    const int LETTER_TO_INT_CONVERTER = 65;
    
    row = static_cast<int>(row_in) - NUMBER_TO_INT_CONVERTER;
    row = check_range(row);
    
    col_in = toupper(col_in);
    col = static_cast<int>(col_in) - LETTER_TO_INT_CONVERTER;
    col = check_range(col);
}

int Position::get_row() {
    return row;
}

void Position::set_row(int row_in) {
    row = row_in;
    row = check_range(row);
    return;
}

int Position::get_col() {
    return col;
}

void Position::set_col(int col_in) {
    col = col_in;
    col = check_range(col);
    return;
}

void Position::read(istream &is) {
    const int LETTER_TO_INT_CONVERTER = 65;
    
    int rowInput;
    char colInput;
    is >> rowInput;
    
    if (is.fail()) {
        is.clear();
        char filler;
        is >> filler >> rowInput >> filler >> colInput >> filler;
    }
    else {
        is >> colInput;
    }
    
    colInput = toupper(colInput);
    int colNumber = static_cast<int>(colInput) - LETTER_TO_INT_CONVERTER;
    row = rowInput - 1;
    row = check_range(row);
    col = colNumber;
    col = check_range(col);
    return;
}

void Position::write(ostream &os) {
    const int LETTER_TO_INT_CONVERTER = 65;
    int rowOutput = row + 1;
    char colOutput = static_cast<char>(col) + LETTER_TO_INT_CONVERTER;
    os << "(" << rowOutput << "," << colOutput << ")";
    return;
}

int Position::check_range(int val) {
    if (val >= 0 && val < MAX_GRID_SIZE) {
        return val;
    }
    else if (val < 0) {
        return 0;
    }
    else {
        return MAX_GRID_SIZE - 1;
    }
}


// Your code goes above this line.
// Don't change the implementations below!

istream &operator>>(istream &is,  Position &pos) {
    pos.read(is);
    return is;
}

ostream &operator<<(ostream &os, Position pos) {
    pos.write(os);
    return os;
}

