/**
 * Copyright 2019 University of Michigan EECS183
 *
 * Game.cpp
 * Project UID 4cd2d66df3154b6c8b0ff27aa6791edb
 *
 * Michael Hymowitz, Teddy Sweeney
 * mhymo, tsween
 *
 * Project 4: Battleship
 *
 * Contains function definitions for the class Game.
 */

#include <fstream>

#include "Game.h"


Game::Game() {
    p1 = Player();
    p2 = Player();
}

Game::Game(Player player1, string grid1, Player player2, string grid2) {

    if (grid1.empty() || !player1.load_grid_file(grid1)) {
        generate_random_grid(player1);
        cout << "Generating random grid for " << player1.get_name() << endl;
    }
    if (grid2.empty() || !player2.load_grid_file(grid2)) {
        generate_random_grid(player2);
        cout << "Generating random grid for CPU";
    }
    p1 = player1;
    p2 = player2;

}

Player Game::get_p1() {
    return p1;
}

Player Game::get_p2() {
    return p2;
}

string Game::get_move(string player_name) {
    string move;
    cout << player_name << " enter your move: ";
    cin >> move;
    return move;
}

bool Game::check_valid_move(string move) {
    char colInput = move[1];
    colInput = toupper(colInput);
    
    if (move.length() != 2) {
        cout << "Error 1: " << p1.get_name() << " you entered an invalid input"
        << endl;
        return false;
    }
    else if ((move[0] < 1 || move[0] > 8)
             && (colInput < 'A' || colInput > 'H')) {
        cout << "Error 2: " << p1.get_name()
        << " you entered an invalid position" << endl;
        return false;
    }
    return true;
}

void Game::start(char difficulty, int max_rounds) {
    int round = 0;
    while (round <= MAX_ROUNDS) {
        ++round;
        string move = get_move(p1.get_name());
        while (!check_valid_move(move)) {
            move = get_move(p1.get_name());
        }
        Position pos(move[0], move[1]);
        cout << endl << endl;
        p1.attack(p2, pos);
        
        if (p2.destroyed()) {
            cout << "Your grid" << endl;
            p1.print_grid();
            cout << "CPU's grid" << endl;
            p1.print_opponent_grid();
            
            cout << "Game over, winner is " << p1.get_name() << " in " << round
                 << " rounds" << endl;
            
            // The Game is over if player 2 is detroyed.
            return;
        }
        
        opponent_make_move(difficulty);
        if (!p1.destroyed()) {
            cout << "Your grid" << endl;
            p1.print_grid();
            cout << "CPU's grid" << endl;
            p1.print_opponent_grid();
        }
        else {
            cout << "Game over, winner is CPU in " << round << " rounds"
                 << endl;
            
            // The Game is over if player 1 is detroyed.
            return;
        }
    }
}

// Your code goes above this line.
// Don't change the implementations below!

void Game::generate_random_grid(Player &p) {
    // grid to check which position has been taken
    bool grid[MAX_GRID_SIZE][MAX_GRID_SIZE] = {{false}};

    for (int k = 0; k < 10 && p.get_num_ships() < 5; k++) {
        // i is the length of the ship to be made
        // decrementing i to create 2 ships of size 3
        int i = p.get_num_ships() + 1;
        if (i > 2) {
            i--;
        }

        // generate random position 1
        int row = get_random_number() % MAX_GRID_SIZE;
        int col = get_random_number() % MAX_GRID_SIZE;
        Position pos1(row, col);

        if (!grid[row][col]) {
            Position pos2;
            // Check if creating position two is not off the grid relative to
            // position 1 inthe order of bottom, right, left, top
            if (row + i < MAX_GRID_SIZE) {
                pos2 = Position(row + i, col);
            } else if (col + i < MAX_GRID_SIZE) {
                pos2 = Position(row, col + i);
            } else if (col - i >= 0) {
                pos2 = Position(row, col - i);
            } else if (row - i >= 0) {
                pos2 = Position(row - i, col);
            } else {
                continue;
            }

            Ship s(pos1, pos2);

            bool pos2_taken = false;
            if (s.is_horizontal()) {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_col() < pos2.get_col() ?
                            pos1.get_col() : pos2.get_col();
                int end = pos1.get_col() < pos2.get_col() ?
                          pos2.get_col() : pos1.get_col();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[pos1.get_row()][j]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[pos1.get_row()][j] = true;
                }
            } else {
                // start and end depends on if pos1 is to the left of pos2
                int start = pos1.get_row() < pos2.get_row() ?
                            pos1.get_row() : pos2.get_row();
                int end = pos1.get_row() < pos2.get_row() ?
                          pos2.get_row() : pos1.get_row();
                // Loop through start and end to check if any of the positions
                // has been taken
                for (int j = start; j <= end; j++) {
                    // break out of the loop if any of the position is taken
                    if (grid[j][pos1.get_col()]) {
                        pos2_taken = true;
                        break;
                    }
                }

                // If none of the positions were taken, set them as taken
                for (int j = start; j <= end; j++) {
                    grid[j][pos1.get_col()] = true;
                }
            }

            // Restart from beginning
            if (pos2_taken) {
                continue;
            }

            // Add the ship to p2's ships
            p.add_ship(s);
        }
    }
}

void Game::opponent_make_move(char difficulty) {
    if (difficulty == EMULATE) {
        Position next;
        cout << "Enter CPU emulation move: ";
        cin >> next;
        cout << endl;
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
    } else if (difficulty == EASY) {
#ifndef NOCPU
        int randRow = get_random_number() % MAX_GRID_SIZE;
        int randCol = get_random_number() % MAX_GRID_SIZE;
        Position randCoord(randRow, randCol);
        p2.attack(p1, randCoord);
        cout << "You received an attack at " << randCoord << endl << endl;
#else
        Position next;
        cin >> next;
        if (cin.fail()) {
            cin.clear();
            next = Position(7, 4);
        }
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
#endif
    } else if (difficulty == MEDIUM) {
        // Simple AI that checks right, bottom, left, top of hit position
        // TODO: implement for S'more version
    }
}

