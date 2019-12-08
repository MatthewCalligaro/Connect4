// Copyright 2019 Aditya Khant
#include "agent-sarsa.hpp"
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include "sarsa-train.hpp"

AgentSARSA::AgentSARSA(vector<double> theta) : theta{theta} {};
void AgentSARSA::getMove(const Board &board, size_t &move,
                         const std::chrono::system_clock::time_point &endTime) {
  std::tuple<size_t, double> actionTup = LSARSATrain::getAction(board, theta);
  size_t moveToSend = std::get<0>(actionTup);
  move = moveToSend;
}

std::string AgentSARSA::getAgentName() const { return "AgentSARSA"; }
