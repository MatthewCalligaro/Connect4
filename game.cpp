// Copyright 2019 Matthew Calligaro

#include <memory>
#include <iostream>
#include <ostream>
#include "game.hpp"

using std::cerr;
using std::endl;
using std::ostream;
using std::shared_ptr;

Game::Game(shared_ptr<Agent> xAgent, shared_ptr<Agent> oAgent) {
    agents_[0] = xAgent;
    agents_[1] = oAgent;
}

// TODO(MatthewCalligaro): Add time limit
size_t Game::execute() {
    size_t moves = 0;

    // Allow each agent to play on their turn until the game is won or a draw
    while (moves < 42 && !board_.isWon()) {
        size_t move = agents_[board_.getTurn()]->getMove(board_);
        if (!board_.isValidMove(move)) {
            size_t badMove = move;
            move = board_.getSuccessors()[0];
            cerr << agents_[board_.getTurn()]->getAgentName() << " made an " << 
                "invalid move (" << badMove << "). Using move " << move << 
                " instead."; 
        }
        board_.handleMove(move);
        ++moves;
    }

    // Return winner, or 2 if a draw
    if (moves == 42) {
        return 2;
    }
    return (moves + 1) % 2;
}

ostream& Game::printBoard(ostream& os) const {
    os << board_;
    return os;
}
