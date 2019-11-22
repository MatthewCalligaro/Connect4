// Copyright 2019 Matthew Calligaro

#ifndef AGENT_MINIMAX_HPP_
#define AGENT_MINIMAX_HPP_

#include <string>
#include "agent.hpp"

class AgentMinimax : public Agent {
 public:
    AgentMinimax();
    AgentMinimax(size_t firstDepth, float discount, float threatWeight);
    void getMove(const Board& board, size_t& move) override;
    std::string getAgentName() const override;
 private:
    size_t firstDepth_;
    float discount_;
    float threatWeight_;

    float minimax(Board board, size_t depth, float alpha, float beta);
    float heuristic(const Board& board) const;
};

#endif  // AGENT_MINIMAX_HPP_
