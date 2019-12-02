#ifndef MC_TRAIN_
#define MC_TRAIN_

#include <tuple>
#include <vector>
#include "board.hpp"

class MonteCarloTrain {
  public:
    MonteCarloTrain(size_t turn, size_t NUM_EPISODES);
    ~MonteCarloTrain() = default;
    static const size_t VECTOR_SIZE = 9;
    size_t NUM_EPISODES = 10000;
    static vector<size_t> extractFeatures(Board board);
    static size_t getPiece(int row, int col, vector<char> boardVec);
    size_t trainingFor = 0;
    static double getQValue(Board board, vector<double> theta);
    vector<double> mcTrain(Board board);
    vector<double> mcTrain();
    static std::tuple<size_t, double> getAction(Board board, vector<double> theta);
    std::tuple<size_t, double> getEGreedyAction(Board board, vector<double> theta,
                                                double epsilon, bool q);
    double reward(Board board);

  private:
    size_t getSubstringCount(std::string mainStr, std::string subStr);

};


#endif