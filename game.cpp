// Copyright 2019 Matthew Calligaro

#include <chrono>
#include <future>
#include <iostream>
#include <memory>
#include <ostream>
#include <thread>
#include "game.hpp"

using std::cerr;
using std::endl;
using std::future;
using std::ostream;
using std::promise;
using std::shared_ptr;
using std::thread;

Game::Game(shared_ptr<Agent> xAgent, shared_ptr<Agent> oAgent, 
    size_t turnTime) : turnTime_{turnTime} {
    agents_[0] = xAgent;
    agents_[1] = oAgent;
}

// TODO(MatthewCalligaro): Add time limit
size_t Game::execute() {
    size_t moves = 0;

    // Allow each agent to play on their turn until the game is won or a draw
    while (moves < 42 && !board_.isWon()) {
        size_t move = getMove(board_.getTurn());
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

size_t Game::getMove(size_t agent) {
    promise<void> timeout;
    size_t move = 7;

    // Create thread 
    thread getMoveThread(getMoveThreadFunction, move, agent, 
        timeout.get_future());

    // Wait for turn time
    std::this_thread::sleep_for(std::chrono::milliseconds(turnTime_));
    timeout.set_value();
    thread.join();

    return move;
}

void Game::getMoveThreadFunction(size_t& move, size_t agent, 
    future<void>& timeout) {
    
}
