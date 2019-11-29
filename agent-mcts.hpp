// Copyright 2019 Matthew Calligaro

#ifndef AGENT_MCTS_HPP_
#define AGENT_MCTS_HPP_

#include <string>
#include "agent.hpp"

class AgentMCTS : public Agent {
 public:
  AgentMCTS();
  ~AgentMCTS();
  void getMove(const Board& board, size_t& move,
               const std::chrono::system_clock::time_point& endTime) override;
  std::string getAgentName() const override;

 private:
  struct Node {
    static const float C;

    Node() = delete;
    Node(const Node& other) = delete;
    Node(const Board& board);
    ~Node();
    Node& operator=(const Node& other) = delete;

    float uct(size_t parentN) const;
    void fillChildren();

    Board board_;
    Node* children_[7];
    size_t numChildren_;
    float q_;
    size_t n_;
    bool fullyExplored_;
  };

  static float traverse(const Node* node);
  static float rollout(const Node* node);

  Node* root_;
};

#endif  // AGENT_MCTS_HPP_
