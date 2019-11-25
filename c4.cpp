// Copyright 2019 Matthew Calligaro

#include <iostream>
#include <memory>
#include "agent-human.hpp"
#include "agent-minimax.hpp"
#include "agent-null.hpp"
#include "agent-sarsa.hpp"
#include "game.hpp"

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

int main() {
  LSARSATrain LSARSA_0 = LSARSATrain(0, true);
  vector<double> theta_0 = LSARSA_0.sarsaTrain();
  AgentSARSA SarsaAgent = AgentSARSA(theta_0);
  shared_ptr<Agent> a1 = make_shared<AgentSARSA>(theta_0);
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
      break;
    case 1:
      cout << a2->getAgentName() << " (O Player) won" << endl;
      break;
    case 2:
      cout << "Draw" << endl;
      break;
  }
}
