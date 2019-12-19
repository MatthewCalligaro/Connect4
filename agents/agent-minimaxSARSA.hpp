// Copyright 2019 Aditya Khant

#ifndef AGENTS_AGENT_MINIMAXSARSA_HPP_
#define AGENTS_AGENT_MINIMAXSARSA_HPP_

#include <string>
#include <vector>
#include "agent.hpp"

using std::vector;

class AgentMinimaxSARSA : public Agent {
 public:
  explicit AgentMinimaxSARSA(vector<double> theta);
  AgentMinimaxSARSA(size_t firstDepth, float discount, float threatWeight,
                    vector<double> theta);
  void getMove(const Board &board, size_t &move,
               const std::chrono::system_clock::time_point &endTime) override;
  std::string getAgentName() const override;

 private:
  size_t firstDepth_;
  float discount_;
  float threatWeight_;

  vector<double> theta;

  float minimax(Board board, size_t depth, float alpha, float beta);
  float heuristic(const Board &board) const;
};

#endif  // AGENTS_AGENT_MINIMAXSARSA_HPP_
