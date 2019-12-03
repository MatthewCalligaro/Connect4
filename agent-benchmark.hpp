// Copyright 2019 Matthew Calligaro

#ifndef AGENT_BENCHMARK_HPP_
#define AGENT_BENCHMARK_HPP_

#include <random>
#include <string>
#include <unordered_map>
#include "agent-minimax.hpp"

class AgentBenchmark : public AgentMinimax {
 public:
  AgentBenchmark();
  AgentBenchmark(size_t depth, bool random);
  void getMove(const Board &board, size_t &move,
               const std::chrono::system_clock::time_point &endTime) override;
  std::string getAgentName() const override;

 private:
  bool random_;
  std::default_random_engine generator_;

  float heuristic(const Board &board) override;
};

#endif  // AGENT_BENCHMARK_HPP_
