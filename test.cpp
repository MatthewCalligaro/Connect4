/**
 * \file test.cpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Implements the Test class
 */

#include "test.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "agent-benchmark.hpp"
#include "agent-human.hpp"
#include "agent-mcts.hpp"
#include "agent-minimax.hpp"
#include "agent-minimaxSARSA.hpp"
#include "agent-null.hpp"
#include "game.hpp"
#include "mc-train.hpp"
#include "sarsa-train.hpp"

void Test::singleGame() {
  std::shared_ptr<Agent> ax = std::make_shared<AgentBenchmark>(4, false);
  std::shared_ptr<Agent> ao = std::make_shared<AgentMinimax>(12);
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

void Test::timeTrials(size_t numTrials, size_t minDepth, size_t maxDepth,
                      std::string tag, bool verbose) {
  const size_t TIME_LIMIT = 10000;

  // Dummy array to store X (benchmark agent) move times
  std::array<double, 42> xTimes;

  for (size_t depth = minDepth; depth <= maxDepth; ++depth) {
    // Open a csv file for output
    std::stringstream filename;
    filename << "data/" << depth << "-" << tag << ".csv";
    std::ofstream file(filename.str());

    // Initialize array to store O move times
    std::array<double, 42> *trials = new std::array<double, 42>[numTrials];
    for (size_t i = 0; i < numTrials; ++i) {
      for (double &move : trials[i]) {
        move = 0;
      }
    }

    if (verbose) {
      std::cout << ">> Depth " << depth << std::endl;
    }

    // Execute one game for each trial
    for (size_t i = 0; i < numTrials; ++i) {
      std::shared_ptr<Agent> ax = std::make_shared<AgentBenchmark>(4, false);
      std::shared_ptr<Agent> ao = std::make_shared<AgentMinimax>(depth);

      Game game(ax, ao, TIME_LIMIT);
      size_t winner = game.execute(xTimes, trials[i]);

      if (verbose) {
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
    }

    // Create CSV header
    for (size_t i = 1; i <= numTrials; ++i) {
      file << "Trial " << i << ",";
    }
    file << "Average" << std::endl;

    // Fill CSV with data
    double averageSum = 0;
    size_t averageCount = 0;
    double first5Sum = 0;
    for (size_t r = 0; r < 42; ++r) {
      double sum = 0;
      size_t count = 0;

      // Write each move time for move r
      for (size_t trial = 0; trial < numTrials; ++trial) {
        if (trials[trial][r] > 0) {
          file << trials[trial][r];
          sum += trials[trial][r];
          ++count;
        }
        file << ",";
      }

      if (count == 0) {
        break;
      }

      // Write average move time for move r
      file << sum / count << std::endl;
      averageSum += sum / count;
      ++averageCount;
      if (r < 5) {
        first5Sum += sum / count;
      }
    }

    // Write and print overall averages (all moves, first 5 moves)
    file << averageSum / averageCount << "," << first5Sum / 5 << std::endl;
    std::cout << first5Sum / 5 << std::endl;

    delete[] trials;
  }
}

void Test::winTrials(size_t numTrials, bool verbose) {
  const size_t TIME_LIMIT = 2000;

  size_t xStats[3] = {0, 0, 0};
  for (size_t i = 0; i < numTrials; ++i) {
    std::shared_ptr<Agent> ax = std::make_shared<AgentMCTS>();
    std::shared_ptr<Agent> ao = std::make_shared<AgentMinimax>(12);

    Game game(ax, ao, TIME_LIMIT);
    size_t winner = game.execute();
    ++xStats[winner];

    if (verbose) {
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
  }

  size_t oStats[3] = {0, 0, 0};
  for (size_t i = 0; i < numTrials; ++i) {
    std::shared_ptr<Agent> ao = std::make_shared<AgentMCTS>();
    std::shared_ptr<Agent> ax = std::make_shared<AgentMinimax>(12);

    Game game(ax, ao, TIME_LIMIT);
    size_t winner = game.execute();
    ++oStats[winner];

    if (verbose) {
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
  }

  std::cout << "X wins: " << xStats[0] << std::endl;
  std::cout << "X loses: " << xStats[1] << std::endl;
  std::cout << "X draws: " << xStats[2] << std::endl;
  std::cout << "O wins: " << oStats[1] << std::endl;
  std::cout << "O loses: " << oStats[0] << std::endl;
  std::cout << "O draws: " << oStats[2] << std::endl;
}

void Test::pairwiseDepthTrials(size_t minDepth, size_t maxDepth) {
  const size_t TIME_LIMIT = 2000;

  // Create CSV and CSV header
  std::ofstream file("data/pairwiseDepthTrials.csv");
  file << "O depth of:,";
  for (size_t oDepth = minDepth; oDepth <= maxDepth; ++oDepth) {
    file << oDepth << ",";
  }
  file << "X win sum" << std::endl;

  // Create arrays to store sum of wins as X and O for each depth
  int *xSums = new int[maxDepth - minDepth + 1];
  int *oSums = new int[maxDepth - minDepth + 1];
  for (size_t i = 0; i <= maxDepth - minDepth; ++i) {
    xSums[i] = 0;
    oSums[i] = 0;
  }

  // Perform all pairwise games
  for (size_t xDepth = minDepth; xDepth <= maxDepth; ++xDepth) {
    file << "X depth of " << xDepth << ",";
    for (size_t oDepth = minDepth; oDepth <= maxDepth; ++oDepth) {
      std::shared_ptr<Agent> ax = std::make_shared<AgentMinimax>(xDepth);
      std::shared_ptr<Agent> ao = std::make_shared<AgentMinimax>(oDepth);
      Game game(ax, ao, TIME_LIMIT);
      int winner = game.execute();

      switch (winner) {
        case 0:
          winner = 1;
          break;
        case 1:
          winner = -1;
          break;
        case 2:
          winner = 0;
          break;
      }

      xSums[xDepth - minDepth] += winner;
      oSums[oDepth - minDepth] += -winner;
      file << winner << ",";
    }
    file << xSums[xDepth - minDepth] << std::endl;
  }

  // Print Sums
  file << "O win sum,";
  for (size_t i = 0; i <= maxDepth - minDepth; ++i) {
    file << oSums[i] << ",";
  }
  file << std::endl << "Total win sum:,";
  for (size_t i = 0; i <= maxDepth - minDepth; ++i) {
    file << xSums[i] + oSums[i] << ",";
  }
  file << std::endl;
  delete[] xSums;
  delete[] oSums;
}
