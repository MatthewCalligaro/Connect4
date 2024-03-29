/**
 * \file agent-human.cpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Implements the AgentHuman class
 */

#include "agent-human.hpp"
#include <iostream>
#include <string>

void AgentHuman::getMove(const Board &board, size_t &move,
                         const std::chrono::system_clock::time_point &endTime) {
  std::cout << board << std::endl;
  std::cout << "Enter the index of the column in which you would like to "
            << "play (a number from 0 to 6): ";

  size_t userMove;
  std::cin >> userMove;

  while (!board.isValidMove(userMove)) {
    std::cout << "That is not a valid move.  Please try again: ";
    std::cin >> userMove;
  }

  move = userMove;
}

std::string AgentHuman::getAgentName() const { return "Human"; }
