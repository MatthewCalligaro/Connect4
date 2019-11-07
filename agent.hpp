// Copyright 2019 Matthew Calligaro

#ifndef AGENT_HPP_
#define AGENT_HPP_

#include "board.hpp"

class Agent {
 public:
    virtual ~Agent() = default;
    virtual size_t getMove(Board board) = 0;
};

#endif  // AGENT_HPP_
