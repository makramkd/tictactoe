#include <iostream>
#include <string>

#include "game.h"

using std::cout;

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage: tictactoe <letter> <algorithm>\n";
        cout << "letter: 'x' or 'o'. If 'o', you play second.\n";
        cout << "algorithm: 'random' or 'minimax'.\n";
        return EXIT_SUCCESS;
    }
    
    std::string letter(argv[1]);
    std::string algorithm(argv[2]);
    if (letter != "x" && letter != "o") {
        cout << "Letter must be 'x' or 'o'\n";
        return EXIT_FAILURE;
    }
    if (algorithm != "random" && algorithm != "minimax") {
        cout << "Algorithms supported are 'random' and 'minimax'\n";
        return EXIT_FAILURE;
    }
    
    auto game = tictac::game_t(letter == "x" ? 'o' : 'x');
    game.play();
}
