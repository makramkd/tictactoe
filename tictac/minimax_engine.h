//
//  minimax_engine.h
//  tictac
//
//  Created by Makram Kamaleddine on 11/13/17.
//  Copyright © 2017 Butcher-of-blaviken. All rights reserved.
//

#ifndef minimax_engine_h
#define minimax_engine_h

#include <unordered_map>

#include "engine.h"

namespace tictac {

    /*
     * This engine uses the naive minimax adverserial search algorithm in order to
     * decide the next move it wants to make. Put compactly, the minimax algorithm
     * is as follows:
     * minimax(s) =
     * - utility(s) if s is a terminal state
     * - max(minimax(result(s, a))), if the player is max
     * - min(minimax(result(s, a))), if the player is min
     *
     * In other words, 'max' tries to maximize the minimum utility he can make with each move,
     * whereas 'min' tries to minimize the maximum utility that max can make with each move.
    */
    struct minimax_engine : public engine_t {
        explicit minimax_engine(char letter)
        : engine_t(letter)
        {
        }

        move_t next_move(const board_t& board) {
            return minimax_decision(board);
        }
    private:
        using utility_t = int;

        move_t minimax_decision(const board_t& board) {
            // auto valid_moves = board.valid_moves(letter);
            // std::unordered_map<move_t, utility_t> move_to_utility;
            return std::make_tuple('x', -1, -1); // stub
        }

        utility_t max_value(const board_t& board) {
            return -1; // stub
        }

        utility_t min_value(const board_t& board) {
            return -1; // stub
        }
    };
}
#endif /* minimax_engine_h */
