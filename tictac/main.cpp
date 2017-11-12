#include <iostream>
#include <vector>
#include <array>
#include <tuple>
#include <utility>
#include <algorithm>

// utility macros to ease copy pasta
#define MAKE_HORIZONTAL_STATE(row,col) \
make_tuple(make_pair((row), (col)), make_pair((row), (col+1)), make_pair((row), (col+2)))

#define MAKE_VERTICAL_STATE(row,col) \
make_tuple(make_pair((row), (col)), make_pair((row+1), (col)), make_pair((row+2), (col)))

using std::cout;
using std::cin;
using std::vector;
using std::array;
using std::tuple;
using std::pair;
using std::make_tuple;
using std::make_pair;

// relevant types
enum board_state {
    x_win,
    y_win,
    in_progress,
    draw,
    unknown
};

using board_t = vector<vector<char>>;
using state_t = tuple<pair<int, int>, pair<int, int>, pair<int, int>>;

// fwd-decl
board_t create_board();
bool valid_move(char letter, int x, int y, const board_t& current_board);
void play_and_draw_board(char letter, int x, int y, board_t& current_board);
board_state check_board(const board_t& current_board);
board_state check_winning_states(const board_t& current_board);
bool game_in_progress(const board_t& current_board);

// constants

// This vector maintains the possible winning states, irrespective of letter
// used (i.e x or o). If we account for the letter there are simply double the
// number of winning states shown below
constexpr auto NUM_WINNING_STATES = 8;
constexpr array<state_t, NUM_WINNING_STATES> winning_states {
    // winning horizontally (i.e all x's/o's in the 1st, 2nd, or 3rd rows)
    MAKE_HORIZONTAL_STATE(0, 0),
    MAKE_HORIZONTAL_STATE(1, 0),
    MAKE_HORIZONTAL_STATE(2, 0),
    
    // winning vertically (i.e all x's/o's in the 1st, 2nd, or 3rd columns)
    MAKE_VERTICAL_STATE(0, 0),
    MAKE_VERTICAL_STATE(0, 1),
    MAKE_VERTICAL_STATE(0, 2),
    
    // winning diagonally (i.e all x's/o's along the main and reverse main diagonal)
    make_tuple(make_pair(0, 0), make_pair(1, 1), make_pair(2, 2)),
    make_tuple(make_pair(0, 2), make_pair(1, 1), make_pair(2, 0))
};

int main() {
    cout << "Welcome to TicTacToe!\n";
    cout << "You can play by entering your move in the repl (x or o)\n";
    cout << "As well as the coordinates of the move separated by spaces\n";
    cout << "Example: 'x 0 1' plays x on the top middle of the board\n";
    
    // Flattened 3x3 matrix
    auto board = create_board();
    // x or o
    char letter;
    // the coordinates of the move
    int x, y;
    // the state of the board
    board_state state;
    while (1) {
        cout << ">>> ";
        cin >> letter >> x >> y;
        if (!valid_move(letter, x, y, board)) {
            cout << "Invalid move\n";
        } else {
            play_and_draw_board(letter, x, y, board);
            state = check_board(board);
            switch(state) {
                case board_state::x_win:
                    cout << "Player x has won!\n";
                    return 0;
                case board_state::y_win:
                    cout << "Player y has won!\n";
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

bool valid_move(char letter, int x, int y, const board_t& current_board) {
    bool valid = true;
    valid = valid && (letter == 'x' || letter == 'o');
    valid = valid && ((x >= 0 && x < 3) && (y >= 0 && y < 3));
    valid = valid && (current_board[x][y] == ' ');
    return valid;
}

board_t create_board() {
    board_t v(3, vector<char>(3, ' '));
    return v;
}

void play_and_draw_board(char letter, int x, int y, board_t& current_board) {
    // modify the current board with the given move
    current_board[x][y] = letter;
    // draw the board
    for (auto i = current_board.begin(); i != current_board.end(); ++i) {
        for (auto j = i->begin(); j != i->end(); j++) {
            // draw letter padded by a single space on each side
            // separated by a | character
            cout << ' ' << *j << ' ' << '|';
        }
        cout << '\n';
    }
}

board_state check_board(const board_t& current_board) {
    // loop through all possible winning states to check if any one
    // of them are satisfied
    // The winning states consist of horizontal, vertical, and diagonal
    // 3-in-a-rows, where all the elements are x's or o's exclusively
    
    
    board_state state = board_state::unknown;
    state = check_winning_states(current_board);
    
    
    // if board state is still unknown it means no one has won:
    // it's either a draw or the game is still in progress
    auto in_progress = game_in_progress(current_board);
    if (state == board_state::unknown && in_progress) {
        state = board_state::in_progress;
    } else if (state == board_state::unknown && !in_progress) {
        state = board_state::draw;
    }
    
    return state;
}

board_state check_winning_states(const board_t& current_board) {
    static vector<char> valid_letters {
        'x',
        'o'
    };
    
    board_state state;
    for (auto i = winning_states.begin(); i != winning_states.end(); ++i)
    {
        for (auto j = valid_letters.begin(); j != valid_letters.end(); ++j)
        {
            // check that the state has the given letter
            auto g0 = std::get<0>(*i), g1 = std::get<1>(*i), g2 = std::get<2>(*i);
            if (current_board[g0.first][g0.second] == *j &&
                current_board[g1.first][g1.second] == *j &&
                current_board[g2.first][g2.second] == *j)
            {
                state = *j == 'x' ? x_win : y_win;
                return state;
            }
        }
    }
    return unknown;
}

bool game_in_progress(const board_t& current_board) {
    vector<bool> unplayed_present;
    std::for_each(current_board.begin(), current_board.end(), [&](const vector<char>& v){
        unplayed_present.push_back(std::any_of(v.begin(), v.end(), [](const char& c){
            return c == ' ';
        }));
    });
    return std::find(unplayed_present.begin(), unplayed_present.end(), true) != unplayed_present.end();
}
