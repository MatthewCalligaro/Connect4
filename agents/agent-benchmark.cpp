/**
 * \file agent-benchmark.cpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Implements the AgentBenchmark class
 */

#include "agent-benchmark.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <string>
#include <vector>

AgentBenchmark::AgentBenchmark() : AgentBenchmark(4, false) {}

AgentBenchmark::AgentBenchmark(size_t depth, bool random)
    : AgentMinimax(depth),
      random_{random},
      generator_(std::random_device()()) {}

void AgentBenchmark::getMove(
    const Board &board, size_t &move,
    const std::chrono::system_clock::time_point &endTime) {
  size_t turn = board.getTurn();
  std::vector<size_t> moves = board.getSuccessors();
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
    float sucMinimax =
        DISCOUNT * minimax(sucBoard, firstDepth_ - 1, alpha, beta);

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

float AgentBenchmark::heuristic(const Board &board) {
  std::uniform_real_distribution dist(-0.5, 0.5);

  if (random_) {
    return dist(generator_);
  }

  return 0;
}

std::string AgentBenchmark::getAgentName() const { return "Benchmark"; }
