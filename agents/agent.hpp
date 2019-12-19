/**
 * \file agent.hpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Declares the Agent class
 */

#ifndef AGENTS_AGENT_HPP_
#define AGENTS_AGENT_HPP_

#include <chrono>
#include <string>
#include "../board.hpp"

/**
 * \class Agent
 * \brief An abstract class defining a Connect 4 agent
 */
class Agent {
 public:
  virtual ~Agent() = default;

  /**
   * \brief Calculates the next move to be taken by the agent
   * \param board   The current state of the board
   * \param move    The column in which the agent decides to play (output)
   * \param endTime The agent should return before this time, or as ASAP after
   */
  virtual void getMove(
      const Board &board, size_t &move,
      const std::chrono::system_clock::time_point &endTime) = 0;

  /**
   * \brief Returns the name of the agent
   * \return The name of the agent
   */
  virtual std::string getAgentName() const = 0;
};

#endif  // AGENTS_AGENT_HPP_
