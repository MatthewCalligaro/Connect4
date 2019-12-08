// Copyright 2019 Matthew Calligaro

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

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;
using std::vector;

void singleGame() {
  std::shared_ptr<Agent> ax = std::make_shared<AgentBenchmark>(4, 0);
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

void LSARSA() {
  LSARSATrain LSARSA_0 = LSARSATrain(0, true, 100000);
  LSARSATrain LSARSA_1 = LSARSATrain(1, true, 100000);
  size_t WinsAndDraws = 0;
  size_t half = 10;
  for (size_t i = 0; i < half; i++) {
    vector<double> theta_0 = LSARSA_0.sarsaTrain();
    shared_ptr<Agent> a1 = make_shared<AgentMinimaxSARSA>(theta_0);
    shared_ptr<Agent> a2 = make_shared<AgentMinimax>();
    Game game(a1, a2);

    cout << a1->getAgentName() << " vs. " << a2->getAgentName() << endl;
    size_t winner = game.execute();

    cout << "----------------------------------------------------------------"
         << endl
         << "Final Board:" << endl;
    game.printBoard(cout);

    switch (winner) {
      case 0:
        cout << a1->getAgentName() << " (X Player) won" << endl;
        WinsAndDraws += 1;
        break;
      case 1:
        cout << a2->getAgentName() << " (O Player) won" << endl;
        break;
      case 2:
        cout << "Draw" << endl;
        WinsAndDraws += 1;
        break;
    }
  }
  for (size_t i = 0; i < half; i++) {
    vector<double> theta_1 = LSARSA_1.sarsaTrain();
    shared_ptr<Agent> a1 = make_shared<AgentMinimaxSARSA>(theta_1);
    shared_ptr<Agent> a2 = make_shared<AgentMinimax>();
    Game game(a2, a1);

    cout << a2->getAgentName() << " vs. " << a1->getAgentName() << endl;
    size_t winner = game.execute();

    cout << "----------------------------------------------------------------"
         << endl
         << "Final Board:" << endl;
    game.printBoard(cout);

    switch (winner) {
      case 0:
        cout << a2->getAgentName() << " (X Player) won" << endl;
        break;
      case 1:
        cout << a1->getAgentName() << " (O Player) won" << endl;
        WinsAndDraws += 1;
        break;
      case 2:
        cout << "Draw" << endl;
        WinsAndDraws += 1;
        break;
    }
  }
  cout << "Wins and Draws: " << WinsAndDraws << "/" << half * 2 << endl;
}

void MC() {
  MonteCarloTrain LSARSA_0 = MonteCarloTrain(0, 100000);
  MonteCarloTrain LSARSA_1 = MonteCarloTrain(1, 100000);
  size_t WinsAndDraws = 0;
  size_t half = 10;
  for (size_t i = 0; i < half; i++) {
    vector<double> theta_0 = LSARSA_0.mcTrain();
    shared_ptr<Agent> a1 = make_shared<AgentMinimaxSARSA>(theta_0);
    shared_ptr<Agent> a2 = make_shared<AgentMinimax>();
    Game game(a1, a2);

    cout << a1->getAgentName() << " vs. " << a2->getAgentName() << endl;
    size_t winner = game.execute();

    cout << "----------------------------------------------------------------"
         << endl
         << "Final Board:" << endl;
    game.printBoard(cout);

    switch (winner) {
      case 0:
        cout << a1->getAgentName() << " (X Player) won" << endl;
        WinsAndDraws += 1;
        break;
      case 1:
        cout << a2->getAgentName() << " (O Player) won" << endl;
        break;
      case 2:
        cout << "Draw" << endl;
        WinsAndDraws += 1;
        break;
    }
  }
  for (size_t i = 0; i < half; i++) {
    vector<double> theta_1 = LSARSA_1.mcTrain();
    shared_ptr<Agent> a1 = make_shared<AgentMinimaxSARSA>(theta_1);
    shared_ptr<Agent> a2 = make_shared<AgentMinimax>();
    Game game(a2, a1);

    cout << a2->getAgentName() << " vs. " << a1->getAgentName() << endl;
    size_t winner = game.execute();

    cout << "----------------------------------------------------------------"
         << endl
         << "Final Board:" << endl;
    game.printBoard(cout);

    switch (winner) {
      case 0:
        cout << a2->getAgentName() << " (X Player) won" << endl;
        break;
      case 1:
        cout << a1->getAgentName() << " (O Player) won" << endl;
        WinsAndDraws += 1;
        break;
      case 2:
        cout << "Draw" << endl;
        WinsAndDraws += 1;
        break;
    }
  }
  cout << "Wins and Draws: " << WinsAndDraws << "/" << half * 2 << endl;
}

void timeTrials(size_t minDepth, size_t maxDepth, std::string tag,
                bool verbose = false) {
  const size_t NUM_TRIALS = 25;
  const size_t TIME_LIMIT = 10000;

  // Dummy array to store X (benchmark agent) move times
  std::array<double, 42> xTimes;

  for (size_t depth = minDepth; depth <= maxDepth; ++depth) {
    // Open a csv file for output
    std::stringstream filename;
    filename << "data/" << depth << "-" << tag << ".csv";
    std::ofstream file(filename.str());

    // Initialize array to store O move times
    std::array<double, 42> trials[NUM_TRIALS];
    for (size_t i = 0; i < NUM_TRIALS; ++i) {
      for (double& move : trials[i]) {
        move = 0;
      }
    }

    if (verbose) {
      std::cout << ">> Depth " << depth << std::endl;
    }

    // Execute one game for each trial
    for (size_t i = 0; i < NUM_TRIALS; ++i) {
      std::shared_ptr<Agent> ax = std::make_shared<AgentBenchmark>(4, false);
      std::shared_ptr<Agent> ao = std::make_shared<AgentMinimax>(depth, 0.01);

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
    for (size_t i = 1; i <= NUM_TRIALS; ++i) {
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
      for (size_t trial = 0; trial < NUM_TRIALS; ++trial) {
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
  }
}

void winTrials(bool verbose=false) {
  const size_t NUM_TRIALS = 25;
  const size_t TIME_LIMIT = 2000;

  size_t xStats[3] = {0, 0, 0};
  for (size_t i = 0; i < NUM_TRIALS; ++i) {
    // TODO: Take these as parameters
    std::shared_ptr<Agent> ax = std::make_shared<AgentMCTS>();
    std::shared_ptr<Agent> ao = std::make_shared<AgentBenchmark>(4, false);

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
  for (size_t i = 0; i < NUM_TRIALS; ++i) {
    // TODO: Take these as parameters
    std::shared_ptr<Agent> ao = std::make_shared<AgentMCTS>();
    std::shared_ptr<Agent> ax = std::make_shared<AgentBenchmark>(4, false);

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

int main() {
  // singleGame();
  winTrials(true);
  // timeTrials(1, 12, "none", false);
  // LSARSA();
  // MC();
}
