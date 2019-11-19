#ifndef SARSA_TRAIN_
#define SARSA_TRAIN_

#include <vector>
#include <tuple>
#include "board.hpp"

class LSARSATrain {
    static const size_t VECTOR_SIZE = 42;
    static const size_t NUM_EPISODES = 500;
    static double getQValue(Board board, vector<double> theta);
    static vector<size_t> extractFeatures(Board board);
    vector<double> sarsaTrain(Board board);
    std::tuple<size_t, double> getAction(Board board, vector<double> theta);
    std::tuple<size_t, double> getEGreedyAction(Board board, vector<double> theta, double epsilon);
    double reward(Board board);
};

#endif