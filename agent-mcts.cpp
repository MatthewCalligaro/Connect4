// Copyright 2019 Matthew Calligaro

#include "agent-mcts.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

AgentBenchmark AgentMCTS::RAND_AGENT(3, true);

void AgentMCTS::getMove(const Board& board, size_t& move,
                        const std::chrono::system_clock::time_point& endTime) {
  Root root(board);
  while (std::chrono::system_clock::now() < endTime) {
    move = root.iterate();
  }

  root.printStats(std::cout);
}

std::string AgentMCTS::getAgentName() const { return "MCTS"; }

/*******************************************************************************
 * AgentMCTS::Node Implementation
 ******************************************************************************/

const float AgentMCTS::Node::C = 1;

AgentMCTS::Node::Node(const Board& board, bool randomizeVisitOrder)
    : board_{board}, numChildren_{0}, q_{0}, n_{0} {
  std::vector<size_t> sucs = board_.getSuccessors();

  if (randomizeVisitOrder) {
    std::shuffle(
        sucs.begin(), sucs.end(),
        std::default_random_engine(
            std::chrono::system_clock::now().time_since_epoch().count()));
  }

  for (size_t move : sucs) {
    unvisited_.push(move);
  }
}

AgentMCTS::Node::~Node() {
  for (size_t i = 0; i < numChildren_; ++i) {
    delete children_[i];
  }
}

float AgentMCTS::Node::uct(size_t parentN) const {
  return q_ * (-1.0 + 2.0 * board_.getTurn()) / n_ +
         C * sqrt(std::log(parentN) / n_);
}

bool AgentMCTS::Node::fullyExplored() const { return unvisited_.size() == 0; }

size_t AgentMCTS::Node::bestUCTChild() const {
  size_t bestChild;
  float bestUCT = -2;
  for (size_t i = 0; i < numChildren_; ++i) {
    float curUCT = children_[i]->uct(n_);
    if (curUCT > bestUCT) {
      bestChild = i;
      bestUCT = curUCT;
    }
  }

  return bestChild;
}

float AgentMCTS::Node::traverse() {
  float reward = 0;

  if (fullyExplored()) {
    if (numChildren_ == 0) {
      // If node is terminal, use its reward
      reward = board_.getReward();
    } else {
      reward = children_[bestUCTChild()]->traverse();
    }
  } else {
    // If node is not fully explored, begin rollout here
    reward = rollout();
  }

  // Update q_ and n_
  q_ += reward;
  ++n_;
  return reward;
}

float AgentMCTS::Node::rollout() {
  // Choose an unvisited child from which to rollout
  Board curBoard = board_;
  curBoard.handleMove(unvisited_.front());
  unvisited_.pop();

  children_[numChildren_] = new Node(curBoard, true);
  ++numChildren_;

  // Play with a random uniform strategy to completion
  std::default_random_engine generator(
      std::chrono::system_clock::now().time_since_epoch().count());

  size_t move;
  while (!(curBoard.isWon() || curBoard.isDraw())) {
    RAND_AGENT.getMove(curBoard, move,
                       std::chrono::system_clock::time_point::max());
    curBoard.handleMove(move);
  }

  children_[numChildren_ - 1]->q_ += curBoard.getReward();
  ++(children_[numChildren_ - 1]->n_);
  return curBoard.getReward();
}

/*******************************************************************************
 * AgentMCTS::Root Implementation
 ******************************************************************************/

AgentMCTS::Root::Root(const Board& board)
    : Node(board, false), moves_{board.getSuccessors()}, bestChild_{0} {
  // Perform initial rollout on each child
  for (size_t i = 0; i < moves_.size(); ++i) {
    q_ += rollout();
    ++n_;
  }
}

size_t AgentMCTS::Root::iterate() {
  size_t child = bestUCTChild();
  q_ += children_[child]->traverse();
  ++n_;

  // bestChild_ is the child with the highest N
  if (children_[child]->n_ > children_[bestChild_]->n_) {
    bestChild_ = child;
  }

  return moves_[bestChild_];
}

std::ostream& AgentMCTS::Root::printStats(std::ostream& os) {
  for (size_t i = 0; i < numChildren_; ++i) {
    os << "Child " << i << " (move " << moves_[i]
       << "): n_=" << children_[i]->n_ << " q_=" << children_[i]->q_
       << " uct=" << children_[i]->uct(n_) << std::endl;
  }
  os << ">> Best Child: " << bestChild_ << " (move " << moves_[bestChild_]
     << ")" << std::endl;
  os << ">> Total Explorations: " << n_ << std::endl << std::endl;
  return os;
}
