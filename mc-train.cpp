/**
 * \file mc-train.cpp
 * \copyright Aditya Khant
 * \date December 2019
 * \brief Implements the MonteCarloTrain class
 */

#include "mc-train.hpp"
#include <time.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using std::array;
using std::cout;
using std::endl;
using std::vector;

MonteCarloTrain::MonteCarloTrain(size_t turn, size_t NUM_EPISODES)
    : NUM_EPISODES{NUM_EPISODES}, trainingFor{turn} {};

vector<size_t> MonteCarloTrain::extractFeatures(Board board) {
  array<size_t, 2> threatCount = board.getThreatCount();
  size_t score = 0;
  score = threatCount[0] * 3 + threatCount[1];

  vector<size_t> output = vector<size_t>(VECTOR_SIZE);
  for (size_t i = 0; i < 9; ++i) {
    output[i] = i==score;
  }


  return output;
}

double MonteCarloTrain::reward(Board board) {
  if (board.isDraw()) {
    return 0;
  } else if (board.isWon()) {
    if (!board.getTurn()) {
      return -1;
    } else {
      return 1;
    }
  } else {
    if (!board.getTurn()) {
    return -0.02;
    } else {
      return 0.02;
    }
  }
}

double MonteCarloTrain::getQValue(Board board, vector<double> theta) {
  double q = 0;
  vector<size_t> activeFeatures = extractFeatures(board);
  for (size_t i = 0; i < VECTOR_SIZE; ++i) {
    q += activeFeatures[i] * theta[i];
  }
  return q;
}

vector<double> MonteCarloTrain::mcTrain() {
  Board board = Board();
  return mcTrain(board);
}

vector<double> MonteCarloTrain::mcTrain(Board board) {
  vector<double> theta = vector<double>(VECTOR_SIZE);
  vector<size_t> counts = vector<size_t>(VECTOR_SIZE);
  const float EPSILON = 0.3;
  const float ALPHA = 0.0005;
  const float GAMMA = 0.9;
  Board boardCopy = board;
  //
  srand((unsigned)time(NULL));
  double lower_bound = 0;
  double upper_bound = 1;
  std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
  std::default_random_engine re;
  re.seed((unsigned)time(NULL));
  for (size_t i = 0; i < VECTOR_SIZE; ++i) {
    theta[i] = 0;
    counts[i] = 0;
  }
  for (size_t episode = 0; episode < NUM_EPISODES; ++episode) {
    boardCopy = board; 
    vector<std::tuple<vector<size_t>, double>> episodeVector =
        vector<std::tuple<vector<size_t>, double>>();
    while (!boardCopy.isDraw() && !boardCopy.isWon()) {
        std::tuple<size_t, double> actionTup =
            getEGreedyAction(boardCopy, theta, EPSILON, true);
        size_t action = std::get<0>(actionTup);
        boardCopy.handleMove(action);
        double r = reward(boardCopy) ;
        vector<size_t> activeFeatures = extractFeatures(boardCopy);
        auto stepTup = std::make_tuple(activeFeatures, r);
        episodeVector.push_back(stepTup);

    }
    for (size_t i = 0; i < episodeVector.size(); ++i) {
      double r = 0;
      for (size_t j = i; j < episodeVector.size(); ++j) {
        std::tuple<vector<size_t>, double> epJ = episodeVector[j];
        double rTot = std::get<1>(epJ);
        r += pow(GAMMA, (j - i)) * rTot;
      }
   
      std::tuple<vector<size_t>, double> epI = episodeVector[i];
      auto currState = std::get<0>(epI);
      for (size_t j = 0; j < VECTOR_SIZE; ++j) {
        if (currState[j] > 0) {
          counts[j] += 1;
          theta[j] = ALPHA * (counts[j] * theta[j] + r);
        }
      }
    }
  }
    for (size_t i = 0; i < VECTOR_SIZE; ++i){
    std::cout << theta[i] << ",";
  }
  std::cout << std::endl;
  return theta;
}

std::tuple<size_t, double> MonteCarloTrain::getAction(Board board,
                                                  vector<double> theta) {
  vector<size_t> successors = board.getSuccessors();
  size_t max_move = successors[0];
  double max_val = -9999;
  if (board.getTurn()){
    for (size_t i = 0; i < successors.size(); ++i) {
      Board sucBoard = board;
      sucBoard.handleMove(successors[i]);
      double q = getQValue(sucBoard, theta);
      if (q > max_val) {
        max_val = q;
        max_move = successors[i];
      }
    }
  } else {
    max_move = successors[0];
    max_val = 9999;
    for (size_t i = 0; i < successors.size(); ++i) {
      Board sucBoard = board;
      sucBoard.handleMove(successors[i]);
      double q = getQValue(sucBoard, theta);
      if (q < max_val) {
        max_val = q;
        max_move = successors[i];
      }
    }

  }
 
  return std::make_tuple(max_move, max_val);
}

std::tuple<size_t, double> MonteCarloTrain::getEGreedyAction(
    Board board, vector<double> theta, double epsilon, bool q) {
  vector<size_t> successors = board.getSuccessors();
  double lower_bound = 0;
  double upper_bound = 1;
  std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
  std::default_random_engine re;
  re.seed((unsigned)time(NULL));
  double a_random_double = unif(re);
  std::tuple<size_t, double> actionTup = getAction(board, theta);
  double maxq = std::get<1>(actionTup);
  if (a_random_double < epsilon) {
    std::uniform_int_distribution<int> distribution(0, successors.size() - 1);
    size_t pos = distribution(re);
    Board sucBoard = board;
    sucBoard.handleMove(pos);
    double qval = 0;
    if (q) {
      qval = maxq;
    } else {
      qval = getQValue(sucBoard, theta);
    }
    return std::make_tuple(pos, qval);
  } else {
    return getAction(board, theta);
  }
}
