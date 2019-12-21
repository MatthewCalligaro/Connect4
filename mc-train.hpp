/**
 * \file mc-train.hpp
 * \copyright Aditya Khant
 * \date December 2019
 * \brief Declares the Linear MC Training class
 */

#ifndef MC_TRAIN_HPP_
#define MC_TRAIN_HPP_

#include <string>
#include <tuple>
#include <vector>
#include "board.hpp"

/**
 * \class MonteCarloTrain
 * \brief A class that trains the weights on features extracted
 * from the board using Linear Q Learning
 */
class MonteCarloTrain {
 public:
  /**
   * \brief Creates a new Linear Monte Carlo training object
   * \param turn  Selects whether you are playing for player 0 or 1
   * \param NUM_EPISODES  number of episodes the training must go for
   */
  MonteCarloTrain(size_t turn, size_t NUM_EPISODES);
  ~MonteCarloTrain() = default;

  /** \brief size of the feature vector */
  static const size_t VECTOR_SIZE = 9;

  /** \brief default number of episodes to train on */
  size_t NUM_EPISODES = 10000;

  /** \brief Extracts features from the current board state */
  static std::vector<size_t> extractFeatures(Board board);

  /** \brief Locates a piece from a board row/board column */
  static size_t getPiece(int row, int col, std::vector<char> boardVec);

  /** \brief specifies what player we are learning for */
  size_t trainingFor = 0;

  /**
   * \brief Extracts features from the board and gets the Value by summing over
   * the value of active features. \param board The current Board state \param
   * theta The weights of the learned features \return  Value of the board state
   */
  static double getQValue(Board board, std::vector<double> theta);

  /** \brief Performs the actual training from a given board state */
  std::vector<double> mcTrain(Board board);

  /** \brief Performs training using Linear Q learning from an empty board */
  std::vector<double> mcTrain();

  /**
   * \brief gets the greedy action at a given board state
   * \param board Current Board State
   * \param theta Learned weights for feature
   * \return a tuple containing the greedy action and its Value
   */
  static std::tuple<size_t, double> getAction(Board board,
                                              std::vector<double> theta);

  /**
   * \brief gets the epsilon greedy action at a given board state
   * \param board Current Board State
   * \param theta Learned weights for feature
   * \param epsilon The probability of exploring instead of exploiting
   * \param q Flag to notify whether its Q or SARSA
   * \return a tuple containing the greedy action and its Q value
   */
  std::tuple<size_t, double> getEGreedyAction(Board board,
                                              std::vector<double> theta,
                                              double epsilon, bool q);

  /**
   * \brief Returns the reward for taking an action
   * \note Its +1 for winning, -1 for losing, 0 for draw, -0.02 per move
   */
  double reward(Board board);

 private:
  size_t getSubstringCount(std::string mainStr, std::string subStr);
};

#endif  // MC_TRAIN_HPP_
