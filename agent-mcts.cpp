// Copyright 2019 Matthew Calligaro

#include "agent-mcts.hpp"
#include <string>
#include <vector>

AgentMCTS::AgentMCTS() : root_{new Node(Board(0, 0))} {}

AgentMCTS::~AgentMCTS() { delete root_; }

void AgentMCTS::getMove(const Board &board, size_t &move,
                        const std::chrono::system_clock::time_point &endTime) {
  move = 0;
}

std::string AgentMCTS::getAgentName() const { return "MCTS"; }

float AgentMCTS::traverse(const Node* node) {
  if (!node->fullyExplored_) {
    traverse
  }

  return 0;
}

float AgentMCTS::rollout(const Node* node) {

}



/*******************************************************************************
 * MCTS::Node Implementation
 ******************************************************************************/

const float AgentMCTS::Node::C = 0.1;

AgentMCTS::Node::Node(const Board &board)
    : board_{board}, numChildren_{0}, q_{0}, n_{0}, fullyExplored_{false} {}

AgentMCTS::Node::~Node() {
  for (size_t i = 0; i < numChildren_; ++i) {
    delete children_[i];
  }
}

float AgentMCTS::Node::uct(size_t parentN) const {
  return q_ / n_ + C * sqrt(log(parentN) / n_);
}

void AgentMCTS::Node::fillChildren() {
  std::vector<size_t> sucs = board_.getSuccessors();
  numChildren_ = sucs.size();

  for (size_t i = 0; i < numChildren_; ++i) {
    Board sucBoard = board_;
    sucBoard.handleMove(sucs[i]);
    children_[i] = new Node(sucBoard);
  }
}
