/**
 * \file agent-null.cpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Implements the AgentNull class
 */

#include "agent-null.hpp"
#include <string>

void AgentNull::getMove(const Board &board, size_t &move,
                        const std::chrono::system_clock::time_point &endTime) {
  move = board.getSuccessors()[0];
}

std::string AgentNull::getAgentName() const { return "Null"; }
