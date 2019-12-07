// Copyright 2019 Aditya Khant
#include "sarsa-train.hpp"
#include <time.h>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::array;

LSARSATrain::LSARSATrain(size_t turn, bool isQ, size_t NUM_EPISODES)
    : NUM_EPISODES{NUM_EPISODES}, trainingFor{turn}, isQ{isQ} {};

vector<size_t> LSARSATrain::extractFeatures(Board board) {
  array<size_t, 2> threatCount = board.getThreatCount();
  size_t score = 0;
  if (board.getTurn()) {
    score = threatCount[0] * 3 + threatCount[1];
  } else {
    score = threatCount[1] * 3 + threatCount[0];
  }

  vector<size_t> output = vector<size_t>(VECTOR_SIZE);
  for (size_t i = 0; i < 9; ++i) {
    if (i == score) {
      output[i] = 1;
    } else {
      output[i] = 0;
    }
  }

  // size_t scoreSelf = 0;
  // size_t scoreOpp = 0;
  // vector<char> boardVector = board.getBoardVector();
  // for (size_t i = 0; i < 6; ++i){
  //     size_t piece = getPiece(i, 3, boardVector);
  //     if (piece < 2){
  //         if (piece == board.getTurn()){
  //           ++scoreSelf;
  //         } else {
  //           ++scoreOpp;
  //         }
  //     }
  // }
  // score = scoreSelf*4 + scoreOpp;
  // for (size_t i = 9; i<25; ++i){
  //   if (i - 9 == score){
  //     output[i] = 1;
  //   } else {
  //     output[i] = 0;
  //   }
  // }

  return output;
}

size_t LSARSATrain::getSubstringCount(std::string mainStr, std::string subStr) {
  size_t occurrences = 0;
  std::string::size_type pos = 0;
  while ((pos = mainStr.find(subStr, pos)) != std::string::npos) {
    ++occurrences;
    ++pos;
  }
  return occurrences;
}

double LSARSATrain::reward(Board board) {
  if (board.isDraw()) {
    return 0;
  } else if (board.isWon()) {
    if (board.getTurn() == trainingFor) {
      return -1;
    } else {
      return 1;
    }
  } else {
    return -0.02;
  }
}

double LSARSATrain::getQValue(Board board, vector<double> theta) {
  double q = 0;
  vector<size_t> activeFeatures = extractFeatures(board);
  for (size_t i = 0; i < VECTOR_SIZE; ++i) {
    q += activeFeatures[i] * theta[i];
  }
  return q;
}

vector<double> LSARSATrain::sarsaTrain() {
  Board board = Board();
  return sarsaTrain(board);
}

vector<double> LSARSATrain::sarsaTrain(Board board) {
  vector<double> theta = vector<double>(VECTOR_SIZE);
  const float EPSILON = 0.1;
  const float ALPHA = 0.3;
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
    // double a_random_double = unif(re);
    // theta[i] = a_random_double;
    theta[i] = 0.5;
  }
  // std::ostringstream oss2;
  // std::copy(theta.begin(), theta.end()-1,
  //       std::ostream_iterator<float>(oss2, ","));
  // oss2 << theta.back();
  // std::cout << oss2.str() << std::endl <<std::endl;

  for (size_t episode = 0; episode < NUM_EPISODES; ++episode) {
    // if (episode % 1000000 == 0){
    //   cout << "Training episode " << episode << endl;
    // }
    std::tuple<size_t, double> actionTup =
        getEGreedyAction(boardCopy, theta, EPSILON, true);
    size_t action = std::get<0>(actionTup);
    double q_prime = std::get<1>(actionTup);
    while (!boardCopy.isDraw() && !boardCopy.isWon()) {
      double q = getQValue(boardCopy, theta);
      boardCopy.handleMove(action);
      if (boardCopy.getTurn() != trainingFor) {
        double r = reward(boardCopy);
        double delta = r + GAMMA * (q_prime)-q;
        vector<size_t> activeFeatures = extractFeatures(boardCopy);
        for (size_t i = 0; i < VECTOR_SIZE; ++i) {
          if (activeFeatures[i] > 0) {
            theta[i] += ALPHA * delta;
          }
        }
      }
      actionTup = getEGreedyAction(board, theta, EPSILON, true);
      action = std::get<0>(actionTup);
      q_prime = std::get<1>(actionTup);
    }
  }
  std::ostringstream oss;
  std::copy(theta.begin(), theta.end() - 1,
            std::ostream_iterator<float>(oss, ","));
  oss << theta.back();
  std::cout << oss.str() << std::endl;
  return theta;
}

std::tuple<size_t, double> LSARSATrain::getAction(Board board,
                                                  vector<double> theta) {
  vector<size_t> successors = board.getSuccessors();
  size_t max_move = successors[0];
  double max_val = -9999;
  for (size_t i = 0; i < successors.size(); ++i) {
    Board sucBoard = board;
    sucBoard.handleMove(successors[i]);
    double q = getQValue(sucBoard, theta);
    if (q > max_val) {
      max_val = q;
      max_move = successors[i];
    }
  }
  return std::make_tuple(max_move, max_val);
}

std::tuple<size_t, double> LSARSATrain::getEGreedyAction(Board board,
                                                         vector<double> theta,
                                                         double epsilon,
                                                         bool q) {
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

size_t LSARSATrain::getPiece(int row, int col, vector<char> boardVec) {
  char c = boardVec[row * 7 + col];
  if (c == 'X') {
    return 0;
  } else if (c == 'O') {
    return 1;
  } else {
    return 2;
  }
}
