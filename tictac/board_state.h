//
//  board_state.h
//  tictac
//
//  Created by Makram Kamaleddine on 11/12/17.
//  Copyright © 2017 Butcher-of-blaviken. All rights reserved.
//

#ifndef board_state_h
#define board_state_h

#include <tuple>
#include <utility>

// utility macros to ease copy pasta
#ifndef MAKE_HORIZONTAL_STATE
#define MAKE_HORIZONTAL_STATE(row,col) \
    std::make_tuple(std::make_pair((row), (col)), std::make_pair((row), (col+1)), std::make_pair((row), (col+2)))
#endif

#ifndef MAKE_VERTICAL_STATE
#define MAKE_VERTICAL_STATE(row,col) \
    std::make_tuple(std::make_pair((row), (col)), std::make_pair((row+1), (col)), std::make_pair((row+2), (col)))
#endif

namespace tictac {
    /*
     * Possible states of the board. The unknown state is used to
     * detect the draw state by checking if there are empty squares
     * (i.e unplayed moves) that are yet possible on the board.
    */
    enum board_state {
        x_win,
        o_win,
        in_progress,
        draw,
        unknown
    };
    
    // a winning state need only consist of 3 coordinates
    using coordinate = std::pair<int, int>;
    using winning_state_t = std::tuple<coordinate,
                                  coordinate,
                                  coordinate>;
}

#endif /* board_state_h */
