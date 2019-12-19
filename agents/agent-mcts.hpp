/**
 * \file agent-mcts.hpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Declaresthe  AgentMCTS class
 */

#ifndef AGENTS_AGENT_MCTS_HPP_
#define AGENTS_AGENT_MCTS_HPP_

#include <ostream>
#include <queue>
#include <random>
#include <string>
#include <vector>
#include "agent-benchmark.hpp"
#include "agent.hpp"

/**
 * \class AgentMCTS
 * \brief An agent which uses Monte Carlo Tree Search
 */
class AgentMCTS : public Agent {
 private:
  class Node;
  class Root;

 public:
  void getMove(const Board& board, size_t& move,
               const std::chrono::system_clock::time_point& endTime) override;
  std::string getAgentName() const override;

 private:
  /**
   * \class Node
   * \brief Represents a node in the MCTS tree
   */
  class Node {
    friend class Root;

   public:
    /** \brief The value of the turning parameter C used in the UCT equation */
    static const float C;

    Node() = delete;
    Node(const Node& other) = delete;
    Node(const Board& board, bool randomizeVisitOrder);
    ~Node();
    Node& operator=(const Node& other) = delete;

   protected:
    /** \brief The board state which the node represents */
    Board board_;

    /** \brief The children of the node which have not yet been visited */
    std::queue<size_t> unvisited_;

    /** \brief Pointers to the children of the node */
    Node* children_[7];

    /** \brief The number of children of the node */
    size_t numChildren_;

    /** \brief The total sum of rewards from rollouts which touched this node */
    float q_;

    /** \brief The total number of rollouts which touched this node */
    size_t n_;

    /**
     * \brief Calculates the UCT value of the node
     * \param parentN   The n value of the parent of this node
     * \returns The UCT value for the node
     * \note The UCT value is adjusted based on player so that more positive is
     * always better, even though the min player prefers negative reward
     */
    float uct(size_t parentN) const;

    /**
     * \brief Determines whether all the children of the node have been visited
     * \returns True if all of the children of this node have been visited
     */
    bool isFullyExplored() const;

    /**
     * \brief Determines the child with the highest UCT value
     * \returns The index of the child with the highest UCT value
     */
    size_t bestUCTChild() const;

    /**
     * \brief Traverses to the best UCT child and updates all statistics
     * \returns The reward of the subsequent rollout
     */
    float traverse();

    /**
     * \brief Performs a rollout starting at this node
     * \returns The value (reward) of the state at which the rollout terminates
     */
    float rollout();
  };

  /**
   * \class Root
   * \brief Represents the root of the MCTS tree
   */
  class Root : public Node {
   public:
    Root() = delete;
    Root(const Root& other) = delete;
    explicit Root(const Board& board);
    ~Root() = default;
    Root& operator=(const Root& other) = delete;

    /**
     * \brief Performs a traversal from the root and updates all statistics
     * \returns The current best move after the rollout has completed
     */
    size_t iterate();

    /**
     * \brief Prints a summary of the MCTS statistics for this turn
     * \param os    The output stream to which to print the statistics
     * \returns The output stream which was passed in
     */
    std::ostream& printStats(std::ostream& os);

   private:
    /** \brief The valid moves which can be taken from this board state */
    std::vector<size_t> moves_;

    /** \brief The child with the highest n value (the move to return) */
    size_t bestChild_;
  };

  /** \brief The agent used to choose moves during rollouts */
  static AgentBenchmark ROLLOUT_AGENT;
};

#endif  // AGENTS_AGENT_MCTS_HPP_
