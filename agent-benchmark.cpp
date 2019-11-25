// Copyright 2019 Matthew Calligaro

#include "agent-benchmark.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

AgentBenchmark::AgentBenchmark() : AgentBenchmark(4, 0, 0) {}

AgentBenchmark::AgentBenchmark(size_t depth, float threatWeight, float epsilon)
    : AgentMinimax(depth, threatWeight), epsilon_{epsilon} {}

// TODO(MatthewCalligaro): Make a random move with probability epsilon
void AgentBenchmark::getMove(
    const Board &board, size_t &move,
    const std::chrono::system_clock::time_point &endTime) {
  size_t turn = board.getTurn();
  vector<size_t> moves = board.getSuccessors();
  float bestSucMinimax = 0;

  size_t bestMove = 3;
  float alpha = -256;
  float beta = 256;
  bestSucMinimax = -256 + (turn * 512.0);

  // Find the best move
  for (size_t move : moves) {
    // Calculate the minimax of the successor state
    Board sucBoard = board;
    sucBoard.handleMove(move);
    float sucMinimax = DISCOUNT * minimax(sucBoard, firstDepth_ - 1, alpha, beta);

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
    
    // If we have surpassed the endTime given by the caller, yield to caller
    if (std::chrono::system_clock::now() >= endTime) {
      return;
    }
  }

  move = bestMove;
}

std::string AgentBenchmark::getAgentName() const { return "Benchmark"; }
