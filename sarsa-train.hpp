// Copyright 2019 Aditya Khant

#ifndef SARSA_TRAIN_HPP_
#define SARSA_TRAIN_HPP_

#include <string>
#include <tuple>
#include <vector>
#include "board.hpp"

using std::vector;

class LSARSATrain {
 public:
  LSARSATrain(size_t turn, bool isQ, size_t NUM_EPISODES);
  ~LSARSATrain() = default;
  static const size_t VECTOR_SIZE = 9;
  size_t NUM_EPISODES = 10000;
  static double getQValue(Board board, vector<double> theta);
  static vector<size_t> extractFeatures(Board board);
  static size_t getPiece(int row, int col, vector<char> boardVec);
  size_t trainingFor = 0;
  bool isQ = true;
  vector<double> sarsaTrain(Board board);
  vector<double> sarsaTrain();
  static std::tuple<size_t, double> getAction(Board board,
                                              vector<double> theta);
  std::tuple<size_t, double> getEGreedyAction(Board board, vector<double> theta,
                                              double epsilon, bool q);
  double reward(Board board);

 private:
  size_t getSubstringCount(std::string mainStr, std::string subStr);
};

#endif  // SARSA_TRAIN_HPP_
