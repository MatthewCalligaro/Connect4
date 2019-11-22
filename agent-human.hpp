// Copyright 2019 Matthew Calligaro

#ifndef AGENT_HUMAN_HPP_
#define AGENT_HUMAN_HPP_

#include <string>
#include "agent.hpp"

class AgentHuman : public Agent {
 public:
  void getMove(const Board &board, size_t &move) override;
  std::string getAgentName() const override;
};

#endif  // AGENT_HUMAN_HPP_
