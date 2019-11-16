// Copyright 2019 Matthew Calligaro

#ifndef AGENT_MINIMAX_HPP_
#define AGENT_MINIMAX_HPP_

#include <string>
#include "agent.hpp"

class AgentMinimax : public Agent {
 public:
    size_t getMove(Board board) override;
    std::string getAgentName() const override;
 private:
    static const size_t FIRST_DEPTH = 6;
    float minimax(Board board, size_t depth, float alpha, float beta);
};

#endif  // AGENT_MINIMAX_HPP_
