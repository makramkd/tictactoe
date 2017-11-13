//
//  minimax_engine.h
//  tictac
//
//  Created by Makram Kamaleddine on 11/13/17.
//  Copyright © 2017 Butcher-of-blaviken. All rights reserved.
//

#ifndef minimax_engine_h
#define minimax_engine_h

#include <vector>
#include <algorithm>
#include <limits>

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
        using move_utility = std::pair<move_t, utility_t>;

        move_t minimax_decision(const board_t& board) {
            auto valid_moves = board.valid_moves(letter);
            std::vector<move_utility> utilities;
            for (auto i = valid_moves.begin(); i != valid_moves.end(); ++i) {
                utilities.push_back(std::make_pair(*i, min_value(board.result(*i))));
            }
            return std::max_element(utilities.begin(), utilities.end(), [&](const move_utility& mu1, const move_utility& mu2){
                return mu1.second < mu2.second;
            })->first;
        }

        utility_t max_value(const board_t& board) const {
            if (board.terminal_state()) {
                return utility(board);
            }
            auto v = std::numeric_limits<int>::min();
            for (const auto& move: board.valid_moves(board.current_letter())) {
                v = std::max(v, min_value(board.result(move)));
            }
            return v;
        }

        utility_t min_value(const board_t& board) const {
            if (board.terminal_state()) {
                return utility(board);
            }
            auto v = std::numeric_limits<int>::max();
            for (const auto& move: board.valid_moves(board.current_letter())) {
                v = std::min(v, max_value(board.result(move)));
            }
            return v;
        }

        utility_t utility(const board_t& board) const {
            auto state = board.check_board();
            switch (state) {
                case board_state::x_win:
                    return 1;
                case board_state::o_win:
                    return -1;
                case board_state::draw:
                    return 0;
                default:
                    return -1;
            }
        }
    };
}
#endif /* minimax_engine_h */
