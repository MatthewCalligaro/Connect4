#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "agent.hpp"

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
}

#endif // GAME_HPP