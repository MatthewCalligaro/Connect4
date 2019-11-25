// Copyright 2019 Matthew Calligaro

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "agent-human.hpp"
#include "agent-minimax.hpp"
#include "agent-null.hpp"
#include "game.hpp"

void singleGame() {
  std::shared_ptr<Agent> ax = std::make_shared<AgentNull>();
  std::shared_ptr<Agent> ao = std::make_shared<AgentMinimax>(12, 0.01);
  Game game(ax, ao, 2000);

  std::cout << ax->getAgentName() << " vs. " << ao->getAgentName() << std::endl;
  size_t winner = game.execute(true);

  std::cout
      << "----------------------------------------------------------------"
      << std::endl
      << "Final Board:" << std::endl;
  game.printBoard(std::cout);

  switch (winner) {
    case 0:
      std::cout << ax->getAgentName() << " (X Player) won" << std::endl;
      break;
    case 1:
      std::cout << ao->getAgentName() << " (O Player) won" << std::endl;
      break;
    case 2:
      std::cout << "Draw" << std::endl;
      break;
  }
}

void trials() {
  const size_t NUM_TRIALS = 10;
  const size_t DEPTH = 9;
  const size_t TIME_LIMIT = 10000;
  std::ofstream file("data/9deep-Memo.csv");

  std::shared_ptr<Agent> ax;
  std::shared_ptr<Agent> ao;

  std::array<double, 42> trials[NUM_TRIALS * 2];
  for (size_t i = 0; i < NUM_TRIALS * 2; ++i) {
    for (double& move : trials[i]) {
      move = 0;
    }
  }

  // Execute games
  for (size_t i = 0; i < NUM_TRIALS; ++i) {
    ax = std::make_shared<AgentMinimax>(4, 0);
    ao = std::make_shared<AgentMinimax>(DEPTH, 0.01);

    Game game(ax, ao, TIME_LIMIT);
    size_t winner = game.execute(trials[i], trials[i + NUM_TRIALS]);

    std::cout << "Trial " << i + 1 << ": ";
    switch (winner) {
      case 0:
        std::cout << ax->getAgentName() << " (X Player) won" << std::endl;
        break;
      case 1:
        std::cout << ao->getAgentName() << " (O Player) won" << std::endl;
        break;
      case 2:
        std::cout << "Draw" << std::endl;
        break;
    }
  }

  // Create CSV header
  file << ax->getAgentName() << " Trial 1,";
  for (size_t i = 2; i <= NUM_TRIALS; ++i) {
    file << "Trial " << i << ",";
  }
  file << ao->getAgentName() << " Trial 1,";
  for (size_t i = 2; i <= NUM_TRIALS; ++i) {
    file << "Trial " << i << ",";
  }
  file << std::endl;

  // Fill CSV with data
  for (size_t r = 0; r < 42; ++r) {
    for (size_t trial = 0; trial < NUM_TRIALS * 2; ++trial) {
      if (trials[trial][r] > 0) {
        file << trials[trial][r];
      }
      file << ",";
    }
    file << std::endl;
  }
}

int main() {
  singleGame();
  // trials();
}
