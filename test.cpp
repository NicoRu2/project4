/**
 * Copyright 2019 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 4cd2d66df3154b6c8b0ff27aa6791edb
 *
 * Project 4: Battleship
 *
 * Contains functions for testing classes in the project. 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

#include "Position.h"
#include "Ship.h"
#include "Player.h"
#include "Game.h"
#include "utility.h"

using namespace std;


void test_position();
void test_ship();
void test_player();
void test_game();

int main() {
    test_position();
    test_ship();
    test_player();
    return 0;
}

void test_position() {
    cout << "default position constructor" << endl;
    Position pos1;
    cout << "(" << pos1.get_row() << "," << pos1.get_col() << ")" << " expected (0,0)" << endl;

    cout << "non-default position constructor" << endl;
    Position pos2('1', 'B');
    cout << pos2 << " expected (1,B)" << endl;
    Position pos3(1, 1);
    cout << pos3 << " expected (2,B)" << endl;
    Position pos4('9', 'I');
    cout << pos4 << " expected (8,H)" << endl;
    Position pos5(-1, -2);
    cout << pos5 << " expected (1,A)" << endl;
    
    cout << "read" << endl;
    ifstream inputData;
    inputData.open("grid1.txt");
    Position posRead;
    posRead.read(inputData);
    cout << posRead << " expected (8,B)" << endl;
    return;
}

void test_ship() {
    cout << endl << "ship default constructor" << endl;
    Ship ship1;
    cout << ship1.get_start() << " expected (1,A)" << endl;
    cout << ship1.get_size() << " expected 0" << endl;
    cout << ship1.get_end() << " expected (1,A)" << endl;

    cout << "ship non-default constructor" << endl;
    Position pos1(1, 0);
    Position pos2(1, 3);
    Position pos3(0, 0);
    Ship ship2(pos1, pos2);
    cout << ship2.get_start() << " expected (2,A)" << endl;
    cout << ship2.get_end() << " expected (2,D)" << endl;
    cout << ship2.get_size() << " expected 4" << endl;

    cout << endl << "ship has position" << endl;
    cout << ship2.has_position(pos1) << " expected 1" << endl;
    cout << ship2.has_position(pos3) << " expected 0" << endl;
    cout << ship2.has_position(pos2) << " expected 1" << endl;

    cout << endl << "ship hit" << endl;
    ship2.hit();
    cout << ship2.has_sunk() << " expected 0" << endl;
    ship2.hit();
    cout << ship2.has_sunk() << " expected 0" << endl;
    ship2.hit();
    cout << ship2.has_sunk() << " expected 0" << endl;
    ship2.hit();
    cout << ship2.has_sunk() << " expected 1" << endl;



    return;
}

void test_player() {
    cout << "testing default player constructor" << endl;

    Player p1;
    cout << p1.get_name() << " expected" << endl;
    cout << p1.get_num_ships() << " expected 0" << endl;

    cout << "testing non-default player constructor" << endl;
    Player p2("Teddy");
    cout << p2.get_name() << " expected Teddy" << endl;
    cout << p2.get_num_ships() << " expected 0" << endl;

    cout << endl << "testing add ship" << endl;
    Position pos1(0, 0);
    Position pos2(0, 2);
    Ship ship1(pos1, pos2);
    p2.add_ship(ship1);
    p2.print_grid();
    cout << p2.get_num_ships() << " expected 1" << endl;
    pos1.set_col(1);
    Ship ship2(pos1, pos2);
    p1.add_ship(ship2);
    p1.print_grid();
    cout << p1.get_num_ships() << " expected 1" << endl;
    Position pos3(3, 3);
    Position pos4(5, 3);
    Ship ship3(pos3, pos4);
    p1.add_ship(ship3);
    p1.print_grid();
    cout << p1.get_num_ships() << " expected 2" << endl;

    cout << endl << "testing position not hit" << endl;
    cout << p1.position_not_hit(pos1) << " expected 1" << endl;
    p1.attack(p1, pos1);
    cout << p1.position_not_hit(pos1) << " expected 0" << endl;
    Position pos5(5, 5);
    cout << p1.position_not_hit(pos5) << " expected 1" << endl;



    return;
}

