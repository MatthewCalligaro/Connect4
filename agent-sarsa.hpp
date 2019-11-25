#ifndef AGENT_SARSA_HPP_
#define AGENT_SARSA_HPP_

#include <string>
#include <vector>
#include "agent.hpp"
#include "sarsa-train.hpp"

class AgentSARSA : public Agent {
  public: 
  AgentSARSA(vector<double> theta);
  void getMove(const Board &board, size_t &move) override;
  std::string getAgentName() const override;
  vector<double> theta;

};

#endif  // AGENT_MINIMAX_HPP_
