/**
 * \file agent-human.hpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Declares the AgentHuman class
 */

#ifndef AGENTS_AGENT_HUMAN_HPP_
#define AGENTS_AGENT_HUMAN_HPP_

#include <string>
#include "agent.hpp"

/**
 * \class AgentHuman
 * \brief An agent controlled by user input from the command line
 */
class AgentHuman : public Agent {
 public:
  void getMove(const Board &board, size_t &move,
               const std::chrono::system_clock::time_point &endTime) override;
  std::string getAgentName() const override;
};

#endif  // AGENTS_AGENT_HUMAN_HPP_
