// Copyright 2019 Aditya Khant
/**
 * \file agent-sarsa.hpp
 * \copyright Aditya Khant
 * \date December 2019
 * \brief Declares the Agent SARSA class
 */
#ifndef AGENTS_AGENT_SARSA_HPP_
#define AGENTS_AGENT_SARSA_HPP_

#include <string>
#include <vector>
#include "agent.hpp"

/**
 * \class AgentMinimaxSARSA
 * \brief An agent that can be used to perform Linear Q Learning 
 * and Linear Monte Carlo without Minimax
 */ 
class AgentSARSA : public Agent {
 public:
 /**
   * \brief Creates a Q Learning Agent with the learned depths
   * \param theta  The learned weights for the feature grid.
   */
  explicit AgentSARSA(vector<double> theta);
   /**
   * \brief gets Agent's next move by extracting features and learning weights. 
   */     
  void getMove(const Board &board, size_t &move,
               const std::chrono::system_clock::time_point &endTime) override;
  std::string getAgentName() const override;
  /** 
   * \brief Learned weights for the features
  */
  vector<double> theta;
};

#endif  // AGENTS_AGENT_SARSA_HPP_
