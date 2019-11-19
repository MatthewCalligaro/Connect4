// Copyright 2019 Matthew Calligaro

#ifndef AGENT_HPP_
#define AGENT_HPP_

#include <string>
#include "board.hpp"

class Agent {
 public:
    virtual ~Agent() = default;
    virtual size_t getMove(Board board) = 0;
    virtual std::string getAgentName() const = 0;
};

#endif  // AGENT_HPP_
