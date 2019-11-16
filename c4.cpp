// Copyright 2019 Matthew Calligaro

#include <iostream>
#include "agent-null.hpp"
#include "agent-human.hpp"
#include "game.hpp"

using std::cout;
using std::endl;

int main() {
    Agent* a1 = new AgentHuman();
    Agent* a2 = new AgentNull();
    Game game(a1, a2);

    cout << a1->getAgentName() << " vs. " << a2->getAgentName() << endl;
    size_t winner = game.execute();

    switch(winner) {
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
