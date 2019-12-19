/**
 * \file agent-benchmark.hpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Declares the AgentBenchmark class
 */

#ifndef AGENT_BENCHMARK_HPP_
#define AGENT_BENCHMARK_HPP_

#include <random>
#include <string>
#include <unordered_map>
#include "agent-minimax.hpp"

/**
 * \class AgentBenchmark
 * \brief A minimax agent to be used as a benchmark to test other agents
 */
class AgentBenchmark : public AgentMinimax {
 public:
  AgentBenchmark();

  /**
   * \brief Creates a benchmark agent with a specified depth and heuristic eval
   * \param depth   The depth to which minimax search should occur
   * \param random  True for random heuristic eval, false for null heuristic
   */
  AgentBenchmark(size_t depth, bool random);

  void getMove(const Board &board, size_t &move,
               const std::chrono::system_clock::time_point &endTime) override;

  std::string getAgentName() const override;

 private:
  /** \brief True if the agent should use random heuristic eval */
  bool random_;

  /** \brief The random number generator used for random heuristic eval */
  std::default_random_engine generator_;

  float heuristic(const Board &board) override;
};

#endif  // AGENT_BENCHMARK_HPP_
