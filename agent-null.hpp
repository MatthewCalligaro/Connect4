// Copyright 2019 Matthew Calligaro

#ifndef AGENT_NULL_HPP_
#define AGENT_NULL_HPP_

#include "agent.hpp"

class AgentNull : Agent {
 public:
    virtual size_t getMove(Board board);
};

#endif  // AGENT_NULL_HPP_
