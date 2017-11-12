//
//  board.h
//  tictac
//
//  Created by Makram Kamaleddine on 11/12/17.
//  Copyright © 2017 Butcher-of-blaviken. All rights reserved.
//

#ifndef board_h
#define board_h

#include <vector>
#include <array>
#include <utility>
#include <tuple>

#include "move.h"
#include "board_state.h"

namespace tictac {
    struct board_t {
        /*
         * Create a board that corresponds to the beginning
         * of a tic tac toe game.
        */
        explicit board_t()
        : board(3, std::vector<char>(3, ' '))
        {
        }
        
        /*
         * Play the given move on this board. This mutates
         * the state of the board.
        */
        void play_move(move_t move) {
            // stub
        }
        
        board_state check_board() const {
            return board_state::unknown; //stub
        }
    private:
        std::vector<std::vector<char>> board;
        
        // This array maintains the possible winning states, irrespective of letter
        // used (i.e x or o). If we account for the letter there are simply double the
        // number of winning states shown below.
        constexpr std::array<winning_state_t, NUM_WINNING_STATES> winning_states = {
            // winning horizontally (i.e all x's/o's in the 1st, 2nd, or 3rd rows)
            MAKE_HORIZONTAL_STATE(0, 0),
            MAKE_HORIZONTAL_STATE(1, 0),
            MAKE_HORIZONTAL_STATE(2, 0),
            
            // winning vertically (i.e all x's/o's in the 1st, 2nd, or 3rd columns)
            MAKE_VERTICAL_STATE(0, 0),
            MAKE_VERTICAL_STATE(0, 1),
            MAKE_VERTICAL_STATE(0, 2),
            
            // winning diagonally (i.e all x's/o's along the main and reverse main diagonal)
            std::make_tuple(std::make_pair(0, 0), std::make_pair(1, 1), std::make_pair(2, 2)),
            std::make_tuple(std::make_pair(0, 2), std::make_pair(1, 1), std::make_pair(2, 0))
        };
        
        /*
         * Return true if and only if the given move is valid.
        */
        bool valid_move(move_t move) {
            return false; // stub
        }
        
        /*
         * Check the winning states to see if they are satisfied
         * by either 'x' or 'o'. If they are not, we return the
         * 'unknown' board_state.
        */
        board_state check_winning_states() const {
            return board_state::unknown; // stub
        }
        
        /*
         * Checks whether the game played on this board is in progress.
         * This is indicated by any unplayed moves on the board. This
         * only works if no winning state is satisfied.
        */
        bool in_progress() const {
            return false; // stub
        }
    }
}

#endif /* board_h */
