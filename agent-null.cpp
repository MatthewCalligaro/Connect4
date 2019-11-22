// Copyright 2019 Matthew Calligaro

#include <string>
#include "agent-null.hpp"

void AgentNull::getMove(const Board& board, size_t& move) {
    move = board.getSuccessors()[0];
}

std::string AgentNull::getAgentName() const {
    return "Null";
}
