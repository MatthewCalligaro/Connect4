// Copyright 2019 Matthew Calligaro

#ifndef AGENT_MCTS_HPP_
#define AGENT_MCTS_HPP_

#include <ostream>
#include <queue>
#include <string>
#include <vector>
#include "agent.hpp"

class AgentMCTS : public Agent {
 private:
  class Node;
  class Root;

 public:
  AgentMCTS() = default;
  void getMove(const Board& board, size_t& move,
               const std::chrono::system_clock::time_point& endTime) override;
  std::string getAgentName() const override;

 private:
  class Node {
    friend class Root;

   public:
    static const float C;

    Node() = delete;
    Node(const Node& other) = delete;
    Node(const Board& board, bool randomizeVisitOrder);
    ~Node();
    Node& operator=(const Node& other) = delete;

   protected:
    Board board_;
    std::queue<size_t> unvisited_;
    Node* children_[7];
    size_t numChildren_;
    float q_;
    size_t n_;

    float uct(size_t parentN, bool verbose = false) const;
    bool fullyExplored() const;
    size_t bestUCTChild() const;
    float traverse();
    float rollout();
  };

  class Root : public Node {
   public:
    Root() = delete;
    Root(const Root& other) = delete;
    explicit Root(const Board& board);
    ~Root() = default;
    Root& operator=(const Root& other) = delete;

    size_t iterate();
    std::ostream& printStats(std::ostream& os);

   private:
    std::vector<size_t> moves_;
    size_t bestChild_;
  };

  static float traverse(Node* node);
};

#endif  // AGENT_MCTS_HPP_
