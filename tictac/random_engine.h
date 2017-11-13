//
//  random_engine.h
//  tictac
//
//  Created by Makram Kamaleddine on 11/12/17.
//  Copyright © 2017 Butcher-of-blaviken. All rights reserved.
//

#ifndef random_engine_h
#define random_engine_h

#include <vector>
#include <algorithm>
#include <random>

#include "engine.h"

namespace tictac {
    
    /*
     * This is a very simple engine that randomly returns a valid
     * move on the given board. It most likely will not win very often
     * :).
     */
    struct random_engine : public engine_t {
        explicit random_engine(char letter): engine_t(letter) {}
        
        virtual move_t next_move(const board_t& board) {
            auto valid_moves = board.valid_moves(letter);
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(valid_moves.begin(), valid_moves.end(), g);
            return *valid_moves.begin();
        }
    };
}


#endif /* random_engine_h */
