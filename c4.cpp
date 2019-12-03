// Copyright 2019 Matthew Calligaro

#include <iostream>
#include <memory>
#include "agent-human.hpp"
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

int main() {
  //  LSARSA();
  MC();
}
