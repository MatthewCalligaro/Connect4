// Copyright 2019 Matthew Calligaro

#ifndef AGENT_HUMAN_HPP_
#define AGENT_HUMAN_HPP_

#include "agent.hpp"

class AgentHuman : public Agent {
 public:
    virtual size_t getMove(Board board);
};

#endif  // AGENT_HUMAN_HPP_
