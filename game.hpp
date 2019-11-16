// Copyright 2019 Matthew Calligaro

#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>
#include <ostream>
#include "agent.hpp"
#include "board.hpp"

using std::shared_ptr;
using std::ostream;

class Game {
 public:
    Game() = delete;
    Game(const Game& other) = default;
    Game(shared_ptr<Agent> xAgent, shared_ptr<Agent> oAgent);
    ~Game() = default;
    Game& operator=(const Game& other) = default;

    size_t execute();
    ostream& printBoard(ostream& os) const;
    
 private:
    Board board_;
    shared_ptr<Agent> agents_[2];
};

#endif  // GAME_HPP_
