// Copyright 2019 Aditya Khant

#ifndef AGENTS_AGENT_SARSA_HPP_
#define AGENTS_AGENT_SARSA_HPP_

#include <string>
#include <vector>
#include "agent.hpp"

class AgentSARSA : public Agent {
 public:
  explicit AgentSARSA(vector<double> theta);
  void getMove(const Board &board, size_t &move,
               const std::chrono::system_clock::time_point &endTime) override;
  std::string getAgentName() const override;
  vector<double> theta;
};

#endif  // AGENTS_AGENT_SARSA_HPP_
