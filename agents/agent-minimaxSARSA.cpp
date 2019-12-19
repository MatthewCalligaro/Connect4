// Copyright 2019 Matthew Calligaro

#include "agent-minimaxSARSA.hpp"
#include <algorithm>
#include <array>
#include <string>
#include <vector>
#include "../mc-train.hpp"
#include "../sarsa-train.hpp"

using std::array;
using std::vector;

AgentMinimaxSARSA::AgentMinimaxSARSA(vector<double> theta)
    : AgentMinimaxSARSA(4, 0.99, 0.01, theta) {}

AgentMinimaxSARSA::AgentMinimaxSARSA(size_t firstDepth, float discount,
                                     float threatWeight, vector<double> theta)
    : firstDepth_{firstDepth},
      discount_{discount},
      threatWeight_{threatWeight},
      theta{theta} {}

void AgentMinimaxSARSA::getMove(
    const Board &board, size_t &move,
    const std::chrono::system_clock::time_point &endTime) {
  size_t turn = board.getTurn();
  size_t depth = firstDepth_;
  vector<size_t> moves = board.getSuccessors();
  size_t bestMove = 3;
  float bestSucMinimax = -256 + (turn * 512.0);
  float alpha = -256;
  float beta = 256;

  // Find the best move
  for (size_t move : moves) {
    // Calculate the minimax of the successor state
    Board sucBoard = board;
    sucBoard.handleMove(move);
    float sucMinimax = minimax(sucBoard, depth - 1, alpha, beta);

    // If this successor is the best so far, update values
    if (!turn && sucMinimax > bestSucMinimax) {
      bestMove = move;
      bestSucMinimax = sucMinimax;
      alpha = std::max(alpha, bestSucMinimax);
    } else if (turn && sucMinimax < bestSucMinimax) {
      bestMove = move;
      bestSucMinimax = sucMinimax;
      beta = std::min(beta, bestSucMinimax);
    }

    // If alpha > beta, do not explore any further
    if (alpha >= beta) {
      break;
    }
  }

  move = bestMove;
}

std::string AgentMinimaxSARSA::getAgentName() const { return "MinimaxSARSA"; }

float AgentMinimaxSARSA::minimax(Board board, size_t depth, float alpha,
                                 float beta) {
  size_t turn = board.getTurn();
  // Return 1 if X won, -1 if O won, or O if it is a draw
  if (board.isWon()) {
    return static_cast<float>(turn << 1) - 1;
  }
  if (board.isDraw()) {
    return 0;
  }

  // If we reached max depth, use our heuristic to estimate the minimax
  if (depth == 0) {
    return heuristic(board);
  }

  // Find the best successor
  vector<size_t> moves = board.getSuccessors();
  float bestSucMinimax = -256 + (turn * 512.0);
  for (size_t move : moves) {
    // Calculate the minimax of the successor state
    Board sucBoard = board;
    sucBoard.handleMove(move);
    float sucMinimax = discount_ * minimax(sucBoard, depth - 1, alpha, beta);

    // If this successor is the best so far, update values
    if (!turn && sucMinimax > bestSucMinimax) {
      bestSucMinimax = sucMinimax;
      alpha = std::max(alpha, bestSucMinimax);
    } else if (turn && sucMinimax < bestSucMinimax) {
      bestSucMinimax = sucMinimax;
      beta = std::min(beta, bestSucMinimax);
    }

    // If alpha > beta, do not explore any further
    if (alpha >= beta) {
      break;
    }
  }

  return bestSucMinimax;
}

float AgentMinimaxSARSA::heuristic(const Board &board) const {
  // return LSARSATrain::getQValue(board, theta);
  return MonteCarloTrain::getQValue(board, theta);
}
