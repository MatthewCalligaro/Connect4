// Copyright 2019 Matthew Calligaro

#include "agent-null.hpp"
#include <string>

void AgentNull::getMove(const Board &board, size_t &move,
                        const std::chrono::system_clock::time_point &endTime) {
  move = board.getSuccessors()[0];
}

std::string AgentNull::getAgentName() const { return "Null"; }
