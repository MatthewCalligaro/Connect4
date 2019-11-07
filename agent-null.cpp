// Copyright 2019 Matthew Calligaro

#include "agent-null.hpp"

size_t AgentNull::getMove(Board board) {
    return board.getSuccessors()[0];
}
