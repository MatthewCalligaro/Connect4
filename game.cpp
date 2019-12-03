// Copyright 2019 Matthew Calligaro

#include "game.hpp"
#include <chrono>
#include <future>
#include <iostream>
#include <memory>
#include <ostream>
#include <thread>
#include <utility>

using std::async;
using std::cerr;
using std::endl;
using std::future;
using std::ostream;
using std::promise;
using std::shared_ptr;
using std::chrono::milliseconds;
using std::chrono::system_clock;

void threadHelper(shared_ptr<Agent> agent, Board board,
                  shared_ptr<size_t> move) {
  agent->getMove(board, *move);
}

Game::Game(shared_ptr<Agent> xAgent, shared_ptr<Agent> oAgent, size_t turnTime)
    : turnTime_{turnTime} {
  agents_[0] = xAgent;
  agents_[1] = oAgent;
}

size_t Game::execute() {
  size_t moves = 0;

  // Allow each agent to play on their turn until the game is won or a draw
  while (moves < 42 && !board_.isWon()) {
    size_t move = getMove(board_.getTurn());
    if (!board_.isValidMove(move)) {
      // Explain why the move was not valid
      if (move == NO_MOVE) {
        cerr << agents_[board_.getTurn()]->getAgentName()
             << " did not make a move in the time limit.  ";
      } else {
        cerr << agents_[board_.getTurn()]->getAgentName()
             << " made an invalid move (" << move << ").  ";
      }

      // Use the default move instead
      move = board_.getSuccessors()[0];
      cerr << "Using move " << move << " instead.";
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

ostream &Game::printBoard(ostream &os) const {
  os << board_;
  return os;
}

size_t Game::getMove(size_t agent) {
  shared_ptr<size_t> move(new size_t(NO_MOVE));
  system_clock::time_point endTime =
      system_clock::now() + milliseconds(turnTime_);

  // Run the agents getMove function (via threadHelper) until at most endTime
  future<void> threadFuture = async(threadHelper, agents_[agent], board_, move);
  threadFuture.wait_until(endTime);

  // Return whatever value the agent placed in move by this time
  return *move;
}
