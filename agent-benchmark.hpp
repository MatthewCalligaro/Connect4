// Copyright 2019 Matthew Calligaro

#ifndef AGENT_BENCHMARK_HPP_
#define AGENT_BENCHMARK_HPP_

#include <string>
#include <unordered_map>
#include "agent-minimax.hpp"

class AgentBenchmark : public AgentMinimax {
 public:
  AgentBenchmark();
  AgentBenchmark(size_t depth, float threatWeight, float epsilon);
  void getMove(const Board &board, size_t &move,
               const std::chrono::system_clock::time_point &endTime) override;
  std::string getAgentName() const override;

 private:
  float epsilon_;
};

#endif  // AGENT_BENCHMARK_HPP_
