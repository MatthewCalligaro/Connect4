// Copyright 2019 Matthew Calligaro

#include <string>
#include "agent-null.hpp"

size_t AgentNull::getMove(Board board) {
    return board.getSuccessors()[0];
}

std::string AgentNull::getAgentName() const {
    return "Null";
}
