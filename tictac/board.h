//
//  board.h
//  tictac
//
//  Created by Makram Kamaleddine on 11/12/17.
//  Copyright © 2017 Butcher-of-blaviken. All rights reserved.
//

#ifndef board_h
#define board_h

#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include <tuple>
#include <algorithm>
#include <string>

#include "move.h"
#include "board_state.h"
#include "player.h"

namespace tictac {
    struct board_t {
        /*
         * Create a board that corresponds to the beginning
         * of a tic tac toe game.
        */
        explicit board_t()
        : board(3, std::vector<char>(3, ' ')),
        last_player(player::o)
        {
        }

        board_t(const board_t& other_board)
        : board(other_board.board),
        last_player(other_board.last_player)
        {
        }

        /*
         * Play the given move on this board. This mutates
         * the state of the board.
        */
        move_status play_move(move_t move) {
            if (!valid_move(move)) {
                draw_board();
                return move_status::invalid;
            }

            using std::get;
            auto letter = get<0>(move);
            auto x = get<1>(move), y = get<2>(move);
            // modify the current board with the given move
            board[x][y] = letter;
            // draw the board
            draw_board();
            // update the last_player
            update_last_player();
            return move_status::valid;
        }

        move_status play_move_no_stdout(move_t move) {
            if (!valid_move(move)) {
                return move_status::invalid;
            }

            using std::get;
            auto letter = get<0>(move);
            auto x = get<1>(move), y = get<2>(move);
            // modify the current board with the given move
            board[x][y] = letter;
            // update the last_player
            update_last_player();
            return move_status::valid;
        }

        board_state check_board() const {
            // loop through all possible winning states to check if any one
            // of them are satisfied
            // The winning states consist of horizontal, vertical, and diagonal
            // 3-in-a-rows, where all the elements are x's or o's exclusively
            board_state state = board_state::unknown;
            state = check_winning_states();

            // if board state is still unknown it means no one has won:
            // it's either a draw or the game is still in progress
            auto game_in_progress = in_progress();
            if (state == board_state::unknown && game_in_progress) {
                state = board_state::in_progress;
            } else if (state == board_state::unknown && !game_in_progress) {
                state = board_state::draw;
            }

            return state;
        }

        /*
         * Return true if and only if the given move is valid.
         */
        bool valid_move(move_t move) {
            auto letter = std::get<0>(move);
            auto x = std::get<1>(move), y = std::get<2>(move);
            bool valid = true;
            valid = valid && (letter == 'x' || letter == 'o');
            valid = valid && ((x >= 0 && x < 3) && (y >= 0 && y < 3));
            valid = valid && (board[x][y] == ' ');
            return valid;
        }

        /*
         * Return a vector of valid moves that can be performed.
        */
        std::vector<move_t> valid_moves(char letter) const {
            std::vector<move_t> moves;
            for (auto i = 0; i < board.size(); ++i) {
                for (auto j = 0; j < board[i].size(); ++j) {
                    if (board[i][j] == ' ') {
                        moves.push_back(std::make_tuple(letter, i, j));
                    }
                }
            }
            return moves;
        }

        player current_player() const {
            switch (last_player) {
                case player::x:
                    return player::o;
                default:
                    return player::x;
            }
        }

        char current_letter() const {
            switch(last_player) {
                case player::x:
                    return 'o';
                default:
                    return 'x';
            }
        }

        bool terminal_state() const {
            auto state = check_board();
            return state == board_state::x_win || state == board_state::o_win
                || state == board_state::draw;
        }

        /*
         * Returns a board that would be the state of the game if the given move
         * is played. This does not mutate the board.
        */
        board_t result(move_t move) const {
            board_t new_board(*this);
            new_board.play_move_no_stdout(move);
            return new_board;
        }
    private:
        std::vector<std::vector<char>> board;

        // this is in order to return the player whose turn it is
        // to play on this board in its current state
        player last_player;

        // This array maintains the possible winning states, irrespective of letter
        // used (i.e x or o). If we account for the letter there are simply double the
        // number of winning states shown below.
        static constexpr auto NUM_WINNING_STATES = 8;
        static constexpr std::array<winning_state_t, NUM_WINNING_STATES> winning_states = {
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
        static constexpr std::array<char, 2> valid_letters = {
            'x',
            'o'
        };

        /*
         * Check the winning states to see if they are satisfied
         * by either 'x' or 'o'. If they are not, we return the
         * 'unknown' board_state.
        */
        board_state check_winning_states() const {
            board_state state;
            for (auto i = winning_states.begin(); i != winning_states.end(); ++i)
            {
                for (auto j = valid_letters.begin(); j != valid_letters.end(); ++j)
                {
                    // check that the state has the given letter
                    auto g0 = std::get<0>(*i), g1 = std::get<1>(*i), g2 = std::get<2>(*i);
                    if (board[g0.first][g0.second] == *j &&
                        board[g1.first][g1.second] == *j &&
                        board[g2.first][g2.second] == *j)
                    {
                        state = *j == 'x' ? x_win : o_win;
                        return state;
                    }
                }
            }
            return unknown;
        }

        /*
         * Checks whether the game played on this board is in progress.
         * This is indicated by any unplayed moves on the board. This
         * only works if no winning state is satisfied.
        */
        bool in_progress() const {
            std::vector<bool> unplayed_present;
            std::for_each(board.begin(), board.end(), [&](const std::vector<char>& v){
                unplayed_present.push_back(std::any_of(v.begin(), v.end(), [](const char& c){
                    return c == ' ';
                }));
            });
            return std::find(unplayed_present.begin(), unplayed_present.end(), true) != unplayed_present.end();
        }

        /*
         * Draw the board onto stdout.
        */
        void draw_board() const {
            for (auto i = board.begin(); i != board.end(); ++i) {
                for (auto j = i->begin(); j != i->end(); j++) {
                    // draw letter padded by a single space on each side
                    // separated by a | character
                    std::cout << ' ' << *j << ' ' << '|';
                }
                std::cout << '\n';
            }
        }

        void update_last_player() {
            switch(last_player) {
                case player::x:
                    last_player = player::o;
                    break;
                default:
                    last_player = player::x;
            }
        }
    };
}

#endif /* board_h */
