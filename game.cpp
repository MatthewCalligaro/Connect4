/**
 * \file game.cpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Implements the Game class
 */

#include "game.hpp"
#include <chrono>
#include <future>
#include <iostream>
#include <list>
#include <memory>
#include <ostream>
#include <thread>

void threadHelper(std::shared_ptr<Agent> agent, Board board,
                  std::shared_ptr<size_t> move,
                  const std::chrono::system_clock::time_point &endTime) {
  agent->getMove(board, *move, endTime);
}

Game::Game(std::shared_ptr<Agent> xAgent, std::shared_ptr<Agent> oAgent,
           size_t turnTime)
    : turnTime_{turnTime}, move_{0} {
  agents_[0] = xAgent;
  agents_[1] = oAgent;
}

size_t Game::execute(bool verbose) {
  std::array<double, 42> xMoveTimes;
  std::array<double, 42> oMoveTimes;
  return execute(xMoveTimes, oMoveTimes, verbose);
}

size_t Game::execute(std::array<double, 42> &xMoveTimes,
                     std::array<double, 42> &oMoveTimes, bool verbose) {
  double totalTimes[2] = {0, 0};

  // Allow each agent to play on their turn until the game is won or a draw
  while (move_ < 42 && !board_.isWon()) {
    // Allow the agent to determine its move and measure the elapsed time
    std::chrono::high_resolution_clock::time_point start =
        std::chrono::high_resolution_clock::now();
    size_t move = getMove(board_.getTurn());
    std::chrono::high_resolution_clock::time_point end =
        std::chrono::high_resolution_clock::now();
    double elapsed =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count() /
        1000000000.0;

    // Record the elapsed time
    totalTimes[board_.getTurn()] += elapsed;
    if (board_.getTurn() == 1) {
      oMoveTimes[move_ / 2] = elapsed;
    } else {
      xMoveTimes[move_ / 2] = elapsed;
    }

    // Handle if board move was invalid
    if (!board_.isValidMove(move)) {
      // Explain why the move was not valid
      if (move == NO_MOVE) {
        std::cerr << agents_[board_.getTurn()]->getAgentName()
                  << " did not make a move in the time limit.  ";
      } else {
        std::cerr << agents_[board_.getTurn()]->getAgentName()
                  << " made an invalid move (" << move << ").  ";
      }

      // Use the default move instead
      move = board_.getSuccessors()[0];
      std::cerr << "Using move " << move << " instead." << std::endl;
    }

    if (verbose) {
      std::cout << agents_[board_.getTurn()]->getAgentName() << " ("
                << (board_.getTurn() ? "O" : "X") << " player) played " << move
                << " after " << elapsed << " seconds." << std::endl;
    }

    board_.handleMove(move);
    ++move_;
  }

  if (verbose) {
    std::cout << std::endl;
    std::cout << agents_[0]->getAgentName()
              << "(X player) average time: " << totalTimes[0] / (move_ / 2)
              << std::endl;
    std::cout << agents_[1]->getAgentName()
              << "(O player) average time: " << totalTimes[1] / (move_ / 2)
              << std::endl;
  }

  // Return winner, or 2 if a draw
  if (move_ == 42) {
    return 2;
  }
  return (move_ + 1) % 2;
}

std::ostream &Game::printBoard(std::ostream &os) const {
  os << board_;
  return os;
}

size_t Game::getMove(size_t agent) {
  std::shared_ptr<size_t> move(new size_t(NO_MOVE));
  std::chrono::system_clock::time_point endTime =
      std::chrono::system_clock::now() + std::chrono::milliseconds(turnTime_);

  // Run the agent's getMove function (via threadHelper) until at most endTime
  // and grab the value currently stored in move
  std::future<void> threadFuture = async(std::launch::async, threadHelper,
                                         agents_[agent], board_, move, endTime);
  threadFuture.wait_until(endTime);
  size_t output = *move;

  // For thread safety, wait until the agent finishes deciding its move
  // before returning, but return the value grabbed at endTime
  return output;
}
