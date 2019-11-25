// Copyright 2019 Matthew Calligaro

#ifndef GAME_HPP_
#define GAME_HPP_

#include <future>
#include <list>
#include <memory>
#include <ostream>
#include "agent.hpp"
#include "board.hpp"

class Game {
 public:
  Game() = delete;
  Game(const Game &other) = default;
  Game(std::shared_ptr<Agent> xAgent, std::shared_ptr<Agent> oAgent,
       size_t turnTime = 2000);
  ~Game() = default;
  Game &operator=(const Game &other) = default;

  size_t execute(bool verbose = false);
  size_t execute(std::shared_ptr<std::list<double>[]> moveTimes,
                 bool verbose = false);
  std::ostream &printBoard(ostream &os) const;

 private:
  static const size_t NO_MOVE = 15942;
  Board board_;
  std::shared_ptr<Agent> agents_[2];
  size_t turnTime_;

  size_t getMove(size_t agent);
};

#endif  // GAME_HPP_
