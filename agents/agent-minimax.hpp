/**
 * \file agent-minimax.hpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Declares the AgentMinimax class
 */

#ifndef AGENTS_AGENT_MINIMAX_HPP_
#define AGENTS_AGENT_MINIMAX_HPP_

#include <string>
#include <unordered_map>
#include "agent.hpp"

/**
 * \class AgentMinimax
 * \brief An agent using depth-limited heuristic eval minimax search
 * \note The agent has 3 flags which enable different optimizations:
 * AB_PRUNING: Use alpha-beta pruning
 * MEMOIZE: Use memoization
 * ITERATIVE_DEEPENING: Use iterative deepening search
 */
class AgentMinimax : public Agent {
 public:
  AgentMinimax();

  /**
   * \brief Creates a minimax agent with a specified first max depth
   * \param firstDepth    The first maximum depth used by the agent
   * \note If the IDS flag is true, the agent will repeat search with depth
   * greater than firstDepth until time is up.  If the IDS flag is false, the
   * agent will return after completing search with max depth of firstDepth.
   */
  explicit AgentMinimax(size_t firstDepth);

  void getMove(const Board &board, size_t &move,
               const std::chrono::system_clock::time_point &endTime) override;

  std::string getAgentName() const override;

 protected:
  /** \brief The amount to reduce the reward of subsequent states */
  static const float constexpr DISCOUNT = 0.999;

  /** \brief The maximum discount that a state can receive */
  static const float constexpr MAX_DISCOUNT = 0.95;  // less than DISCOUNT^42

  /** \brief The weight of a single threat in the heuristic eval function */
  static const float constexpr THREAT_WEIGHT = 0.001;

  /** \brief The first maximum depth at which to begin searching */
  size_t firstDepth_;

  /** \brief A memoization table storing minimax values of previous boards */
  std::unordered_map<Board, float, BoardHasher> memo_;

  /**
   * \brief Calculates the minimax value of a board state
   * \param board   The board state to evaluate
   * \param depth   The additional depth to search past this state
   * \param alpha   The largest max value seen so far (for ab-pruning)
   * \param beta    The smallest min value seen so far (for ab-pruning)
   * \return The minimax (or estimated minimax) value of the state
   */
  float minimax(Board board, size_t depth, float alpha, float beta);

  /**
   * \brief The heuristic evaluation function used to evaluate a board state
   * \param board   The board state to evaluate
   * \return The estimated minimax value of board
   */
  virtual float heuristic(const Board &board);
};

#endif  // AGENTS_AGENT_MINIMAX_HPP_
