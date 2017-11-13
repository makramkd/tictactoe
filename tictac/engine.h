//
//  engine.h
//  tictac
//
//  Created by Makram Kamaleddine on 11/12/17.
//  Copyright © 2017 Butcher-of-blaviken. All rights reserved.
//

#ifndef engine_h
#define engine_h

#include "move.h"
#include "board.h"

namespace tictac {
    
    /*
     * An engine is an entity that takes in the current game state
     * (i.e the tic tac toe board) and returns a move that is valid
     *
     * engine_t in particular is an interface that defines the next_move
     * member function that will be overridden by classes that implement
     * this interface.
     */
    struct engine_t {
        explicit engine_t(char letter)
        : letter(letter)
        {
        }
        
        virtual ~engine_t() {}
        virtual move_t next_move(const board_t& board) = 0;
        
    protected:
        // 'x' or 'o'
        char letter;
    };
}

#endif /* engine_h */
