#include "game.hpp"

Game::Game(Agent* xAgent, Agent* oAgent) {
    agents_[0] = xAgent;
    agents_[1] = oAgent;
}

Game::~Game() {
    delete agents_[0];
    delete agents_[1];
}

size_t Game::execute() {
    size_t moves = 0;

    // Allow each agent to play on their turn until the game is won or a draw
    while(moves < 42 && !board_.isWon()) {
        board_.handleMove(agents_[board_.getTurn()]->getMove(board_));
        ++moves;
    }

    // Return winner, or 2 if a draw
    if (moves == 42) {
        return 2;
    }
    return (moves + 1) % 2;
}
