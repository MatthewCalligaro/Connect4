// Copyright 2019 Matthew Calligaro

#ifndef GAME_HPP_
#define GAME_HPP_

#include "agent.hpp"
#include "board.hpp"

class Game {
 public:
    Game() = delete;
    Game(const Game& other) = default;
    Game(Agent* xAgent, Agent* oAgent);
    ~Game();
    Game& operator=(const Game& other) = default;

    size_t execute();
 private:
    Board board_;
    Agent* agents_[2];
};

#endif  // GAME_HPP_
