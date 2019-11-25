// Copyright 2019 Matthew Calligaro

#ifndef AGENT_MINIMAX_HPP_
#define AGENT_MINIMAX_HPP_

#include <string>
#include <unordered_map>
#include "agent.hpp"

class AgentMinimax : public Agent {
 public:
  AgentMinimax();
  AgentMinimax(size_t firstDepth, float threatWeight);
  void getMove(const Board &board, size_t &move,
               const std::chrono::system_clock::time_point &endTime) override;
  std::string getAgentName() const override;

 protected:
  static const float constexpr DISCOUNT = 0.999;
  static const float constexpr MAX_DISCOUNT = 0.95;  // less than DISCOUNT^42

  size_t firstDepth_;
  float threatWeight_;
  std::unordered_map<Board, float, BoardHasher> memo;

  float minimax(Board board, size_t depth, float alpha, float beta);
  float heuristic(const Board &board) const;
};

#endif  // AGENT_MINIMAX_HPP_
