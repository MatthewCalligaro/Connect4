// Copyright 2019 Matthew Calligaro

#ifndef AGENT_MINIMAXSARSA_HPP_
#define AGENT_MINIMAXSARSA_HPP_

#include <string>
#include <vector>
#include "agent.hpp"

class AgentMinimaxSARSA : public Agent {
 public:
  AgentMinimaxSARSA(vector<double> theta);
  AgentMinimaxSARSA(size_t firstDepth, float discount, float threatWeight, vector<double> theta);
  void getMove(const Board &board, size_t &move) override;
  std::string getAgentName() const override;

 private:
  size_t firstDepth_;
  float discount_;
  float threatWeight_;

  vector<double> theta;

  float minimax(Board board, size_t depth, float alpha, float beta);
  float heuristic(const Board &board) const;
};

#endif  // AGENT_MINIMAX_HPP_
