// Copyright 2019 Matthew Calligaro

#include "agent-mcts.hpp"
#include <random>
#include <string>
#include <vector>

AgentMCTS::AgentMCTS() : root_{new Node(Board(0, 0))} {}

AgentMCTS::~AgentMCTS() { delete root_; }

void AgentMCTS::getMove(const Board &board, size_t &move,
                        const std::chrono::system_clock::time_point &endTime) {
  move = 0;
}

std::string AgentMCTS::getAgentName() const { return "MCTS"; }

float AgentMCTS::traverse(Node* node) {
  float reward = 0;
  
  // If node is fully explored, traverse to one of its children
  if (node->fullyExplored()) {
    Node* bestChild = node->bestUCTChild();
    if (bestChild != nullptr) {
      reward = traverse(bestChild);
    } else {
      // If node is terminal, use its reward instead
      reward = node->board_.getReward();
    }
  } else {
    // If node is not fully explored, begin rollout here
    reward = node->rollout();
  }

  // Update q_ and n_ for this node
  node->q_ += reward;
  ++(node->n_);
  return reward;
}


/*******************************************************************************
 * MCTS::Node Implementation
 ******************************************************************************/

const float AgentMCTS::Node::C = 0.1;

AgentMCTS::Node::Node(const Board &board)
    : board_{board}, numChildren_{0}, q_{0}, n_{0} {
  std::vector<size_t> sucs = board_.getSuccessors();
  std::shuffle(sucs.begin(), sucs.end(), std::default_random_engine());
  for(size_t move : sucs) {
    unvisited_.push(move);
  }
}

AgentMCTS::Node::~Node() {
  for (size_t i = 0; i < numChildren_; ++i) {
    delete children_[i];
  }
}

float AgentMCTS::Node::uct(size_t parentN) const {
  return q_ * (-1 * board_.getTurn()) / n_ + C * sqrt(std::log(parentN) / n_);
}

bool AgentMCTS::Node::fullyExplored() const {
  return unvisited_.size() == 0;
}

AgentMCTS::Node* AgentMCTS::Node::bestUCTChild() const {
  Node* bestChild = nullptr;
  float bestUTC = -1;
  for (size_t i = 0; i < numChildren_; ++i) {
    size_t curUTC = children_[i]->uct(n_) > bestUTC;
    if (curUTC > bestUTC) {
      bestChild = children_[i];
      bestUTC = curUTC;
    }
  }

  return bestChild;
}

float AgentMCTS::Node::rollout() {
  // Choose an unvisited child from which to rollout
  Board curBoard = board_;
  curBoard.handleMove(unvisited_.front());
  unvisited_.pop();

  children_[numChildren_] = new Node(curBoard);
  ++numChildren_;

  // Play with a random uniform strategy to completion
  std::default_random_engine generator;
  while (!(curBoard.isWon() || curBoard.isDraw())) {
    std::vector<size_t> moves = curBoard.getSuccessors();
    std::uniform_int_distribution<size_t> dist(0, moves.size());
    curBoard.handleMove(moves[dist(generator)]);
  }

  return curBoard.getReward();
}
