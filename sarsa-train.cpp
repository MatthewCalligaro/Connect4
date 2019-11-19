#include <string>
#include <iostream>
#include <vector>
#include "sarsa-train.hpp"
#include <random>
#include <time.h>
#include <tuple>

using std::cout;
using std::endl;


vector<size_t> LSARSATrain::extractFeatures(Board board){
    //TODO: Implement Board -> Vector
    vector<size_t> output = vector<size_t>(VECTOR_SIZE);
    return output;
}

double LSARSATrain::reward(Board board){
    if (board.isDraw()){
        return 0;
    } else if (board.isWon()){
        if (board.getTurn() == 0){
            return -1;
        } else {
            return +1;
        }
    } else {
        return -0.02;
    }
}

double LSARSATrain::getQValue(Board board, vector<double> theta){
    double q = 0;
    vector<size_t> activeFeatures = extractFeatures(board);
    for (size_t i = 0; i < VECTOR_SIZE; ++i){
        q += activeFeatures[i]*theta[i];
    }
    return q;
}

vector<double> LSARSATrain::sarsaTrain(Board board){
    vector<double> theta = vector<double>(VECTOR_SIZE);
    const float EPSILON = 0.1;
    const float ALPHA = 0.9;
    Board boardCopy = board;

    srand((unsigned)time(NULL));
    double lower_bound = 0;
    double upper_bound = 1;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;
    for (size_t i = 0; i < VECTOR_SIZE; ++i){
        double a_random_double = unif(re);
        theta[i] = a_random_double;
    }
    for (size_t episode; episode < NUM_EPISODES; ++episode){
        cout << "Training episode " << episode << endl;
        std::tuple<size_t, double> actionTup = getEGreedyAction(boardCopy, theta, EPSILON);
        size_t action = std::get<0>(actionTup);
        double q_prime = std::get<1>(actionTup);
        while (!boardCopy.isDraw() && !boardCopy.isWon())
        {
            double q = getQValue(boardCopy, theta);
            boardCopy.handleMove(action);
            double r = reward(boardCopy);
            double delta = r + q_prime - q;
            vector<size_t> activeFeatures = extractFeatures(boardCopy);
            for (size_t i = 0; i < VECTOR_SIZE; ++i){
                if (activeFeatures[i] > 0){
                    theta[i] += delta;
                };
            }
            actionTup = getEGreedyAction(board, theta, EPSILON);
            action = std::get<0>(actionTup);
            q_prime = std::get<1>(actionTup);
        }
    }
    return theta;
}

std::tuple<size_t, double> LSARSATrain::getAction(Board board, vector<double> theta){
    vector<size_t> successors = board.getSuccessors();
    size_t max_move = successors[0];
    double max_val = -9999;
    for (size_t i = 0; i < successors.size(); ++i){
        Board sucBoard = board;
        sucBoard.handleMove(successors[i]);
        double q = getQValue(sucBoard, theta);
        if (q > max_val){
            max_val = q;
            max_move = successors[i];
        }
    }
    return std::make_tuple(max_move, max_val);
}

std::tuple<size_t, double> LSARSATrain::getEGreedyAction(Board board, vector<double> theta, double epsilon){
    vector<size_t> successors = board.getSuccessors();
    double lower_bound = 0;
    double upper_bound = 1;
    std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
    std::default_random_engine re;
    double a_random_double = unif(re);
    if (a_random_double < epsilon){
         std::uniform_int_distribution<int> distribution(0, successors.size()-1); 
         size_t pos = distribution(re);
         Board sucBoard = board;
         sucBoard.handleMove(pos);
         double q = getQValue(sucBoard, theta);
         return std::make_tuple(pos, q);
    } else {
        return getAction(board, theta);
    }
}