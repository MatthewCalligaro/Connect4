// Copyright 2019 Aditya Khant
/**
 * \file agent-minimaxSARSA.hpp
 * \copyright Aditya Khant
 * \date December 2019
 * \brief Declares the Minimax SARSA class
 */

#ifndef AGENTS_AGENT_MINIMAXSARSA_HPP_
#define AGENTS_AGENT_MINIMAXSARSA_HPP_

#include <string>
#include <vector>
#include "agent.hpp"

using std::vector;

/**
 * \class AgentMinimaxSARSA
 * \brief An agent that can be used to perform Linear Q Learning 
 * and Linear Monte Carlo with Minimax
 */ 
class AgentMinimaxSARSA : public Agent {
 public:
  /**
   * \brief Creates a minimax SARSA Agent with the learned depths
   * \param depth the Depth the agent should go to. 
   * \param theta  The learned weights for the feature grid.
   */
  AgentMinimaxSARSA(size_t depth, vector<double> theta);
  /**
   * \brief Creates a minimax + Q or MC Agent with the learned depths
   * \param firstDepth  The first maximum depth used by the agent
   * \param threatWeight  should be ignored
   * \param discount   should be ignored
   * \param theta  The learned weights for the feature grid.
   */ 
  AgentMinimaxSARSA(size_t firstDepth, float discount, float threatWeight,
                    vector<double> theta);
  /**
   * \brief gets Agent's next move by extracting features and learning weights. 
   */                   
  void getMove(const Board &board, size_t &move,
               const std::chrono::system_clock::time_point &endTime) override;
  std::string getAgentName() const override;

 private:
  size_t firstDepth_;
  float discount_;
  float threatWeight_;
  /** 
   * \brief Learned weights for the features
  */
  vector<double> theta;
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
   * \return The estimated Q value of the board
   */
  float heuristic(const Board &board) const;
};

#endif  // AGENTS_AGENT_MINIMAXSARSA_HPP_
