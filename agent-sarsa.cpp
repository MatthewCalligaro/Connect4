
#include <vector>
#include <string>
#include <sstream>
#include <tuple>
#include "agent-sarsa.hpp"
#include "sarsa-train.hpp"

AgentSARSA::AgentSARSA(vector<double> theta) : theta{theta} {};
void AgentSARSA::getMove(const Board &board, size_t &move){
    std::tuple<size_t, double> actionTup = LSARSATrain::getAction(board, theta);
    size_t moveToSend = std::get<0>(actionTup);
    move = moveToSend;
};

std::string AgentSARSA::getAgentName() const {
    return "AgentSARSA";
}

