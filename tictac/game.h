//
//  game.h
//  tictac
//
//  Created by Makram Kamaleddine on 11/12/17.
//  Copyright © 2017 Butcher-of-blaviken. All rights reserved.
//

#ifndef game_h
#define game_h

#include <iostream>
#include <tuple>

#include "board.h"
#include "board_state.h"
#include "move.h"

namespace tictac {
    struct game_t {
        game_t()
        : board()
        {
            
        }
        
        int play() {
            using std::cout;
            using std::cin;
            
            cout << "Welcome to TicTacToe!\n";
            cout << "You can play by entering your move in the repl (x or o)\n";
            cout << "As well as the coordinates of the move separated by spaces\n";
            cout << "Example: 'x 0 1' plays x on the top middle of the board\n";
            
            char letter;
            int x, y;
            board_state state;
            while (1) {
                cout << ">>> ";
                cin >> letter >> x >> y;
                auto current_move = std::make_tuple(letter, x, y);
                
                if (!board.valid_move(current_move)) {
                    cout << "Invalid move\n";
                } else {
                    board.play_move(current_move);
                    state = board.check_board();
                    switch(state) {
                        case board_state::x_win:
                            cout << "Player x has won!\n";
                            return 0;
                        case board_state::y_win:
                            cout << "Player o has won!\n";
                            return 0;
                        case board_state::draw:
                            cout << "It was a draw! Good play!\n";
                            break;
                        default:
                            continue;
                    }
                }
            }
        }
    private:
        board_t board;
    };
}

#endif /* game_h */
