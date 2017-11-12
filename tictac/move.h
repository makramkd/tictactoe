//
//  move.h
//  tictac
//
//  Created by Makram Kamaleddine on 11/12/17.
//  Copyright © 2017 Butcher-of-blaviken. All rights reserved.
//

#ifndef move_h
#define move_h

#include <tuple>

/*
 * A move is simply a combination of 3 things:
 * - the letter (i.e 'x' or 'o')
 * - the row to place the letter
 * - the column to place the letter
*/
namespace tictac {
    using move_t = std::tuple<char, int, int>;
}

#endif /* move_h */
