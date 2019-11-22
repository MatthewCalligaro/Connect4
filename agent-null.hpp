// Copyright 2019 Matthew Calligaro

#ifndef AGENT_NULL_HPP_
#define AGENT_NULL_HPP_

#include <string>
#include "agent.hpp"

class AgentNull : public Agent {
 public:
    void getMove(const Board& board, size_t& move) override;
    std::string getAgentName() const override;
};

#endif  // AGENT_NULL_HPP_
