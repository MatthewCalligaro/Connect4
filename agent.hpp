#ifndef AGENT_HPP
#define AGENT_HPP

#include "board.hpp"

class Agent {
public:
    virtual ~Agent() = default;
    virtual size_t getMove(Board board) = 0;
};

#endif // AGENT_HPP
