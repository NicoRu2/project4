/**
 * Copyright University of Michigan EECS183
 *
 * utility.cpp
 *
 * Project 4: Battleship
 *
 * Contains constants and helper functions.
 */

#include <iostream>

#include "utility.h"


using namespace std;


void print_grid(char grid[MAX_GRID_SIZE][MAX_GRID_SIZE]) {
    // print top row of numbers
    cout << "    ";
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        cout << static_cast<char>('A' + i) << "   ";
    }
    cout << endl << endl;

    // print rows of holes, with letters in leftmost column
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        // letter
        if (i == 9) {
            cout << i + 1 << "  ";
        } else {
            cout << i + 1 << "   ";
        }

        // holes
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            cout << grid[i][j] << "   ";
        }
        cout << endl << endl;
    }
}

void print_initial_header() {
    cout << "----------------------------------------" << endl;
    cout << "               EECS 183                 " << endl;
    cout << "              Battleship                " << endl;
    cout << "----------------------------------------" << endl << endl;
}

void print_menu() {
    cout << endl << endl;
    cout << "         Menu Options         " << endl;
    cout << "------------------------------" << endl;
    cout << "1) Play against easy AI" << endl;
    cout << "2) Play against medium AI (S'more)" << endl;
    cout << "3) Play while emulating CPU (CPU moves entered by player)" << endl;
    cout << "4) Quit" << endl << endl;
    cout << "Choice --> ";
}

void print_closer() {
    cout << endl;
    cout << "----------------------------------------" << endl;
    cout << "           Thanks for playing           " << endl;
    cout << "              Battleship                " << endl;
    cout << "----------------------------------------" << endl << endl;
}


int get_random_number() {
    static std::chrono::time_point<std::chrono::system_clock> p1 = chrono::system_clock::now();
    long elapsed = static_cast<long>(chrono::duration_cast<chrono::milliseconds>(p1.time_since_epoch()).count());
    return (rand() + elapsed) % numeric_limits<int>::max();
}

int get_menu_choice() {
    print_menu();
    int menu_choice = -1;
    while (cin >> menu_choice && (menu_choice < 1 || menu_choice > 4)) {
        cout << "Invalid menu choice" << endl;
        print_menu();
    }
    cout << endl;
    return menu_choice;
}
