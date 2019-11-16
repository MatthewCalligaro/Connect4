// Copyright 2019 Matthew Calligaro

#include <iostream>
#include "agent-human.hpp"

size_t AgentHuman::getMove(Board board) {
    std::cout << board << std::endl;
    std::cout << "Enter the index of the column in which you would like to" <<
        "play (a number from 0 to 6): ";
    
    size_t move;
    std::cin >> move;

    // TODO(MatthewCalligaro): Handle non-numerical inputs
    while (!board.isValidMove(move)) {
        std::cout << "That is not a valid move.  Please try again: ";
        std::cin >> move;
    }

    return move;
}

std::string AgentHuman::getAgentName() const {
    return "Human";
}
