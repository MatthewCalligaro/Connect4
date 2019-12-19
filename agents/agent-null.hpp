/**
 * \file agent-null.hpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Declares the AgentNull class
 */

#ifndef AGENTS_AGENT_NULL_HPP_
#define AGENTS_AGENT_NULL_HPP_

#include <string>
#include "agent.hpp"

/**
 * \class AgentNull
 * \brief The simplest C4 agent which always takes the first avialible move
 */
class AgentNull : public Agent {
 public:
  void getMove(const Board &board, size_t &move,
               const std::chrono::system_clock::time_point &endTime) override;
  std::string getAgentName() const override;
};

#endif  // AGENTS_AGENT_NULL_HPP_
