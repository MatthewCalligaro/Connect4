/**
 * \file agent-minimax.hpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Implements the AgentMinimax class
 */

#define AB_PRUNING 1
#define MEMOIZE 1
#define ITERATIVE_DEEPENING 0

#include "agent-minimax.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

AgentMinimax::AgentMinimax() : AgentMinimax(12) {}

AgentMinimax::AgentMinimax(size_t firstDepth) : firstDepth_{firstDepth} {}

void AgentMinimax::getMove(
    const Board &board, size_t &move,
    const std::chrono::system_clock::time_point &endTime) {
  size_t turn = board.getTurn();
  size_t legalMoves = board.getSuccessorsFast();
  float bestSucMinimax = 0;

#if ITERATIVE_DEEPENING
  for (size_t depth = firstDepth_; std::abs(bestSucMinimax) < MAX_DISCOUNT;
       ++depth) {
#else
  for (size_t depth = firstDepth_; depth <= firstDepth_; ++depth) {
#endif

    size_t bestMove = 3;
    float alpha = -256;
    float beta = 256;
    bestSucMinimax = -256 + (turn * 512.0);

    // Find the best move
    for (size_t moves = legalMoves, curMove = 3; moves;
         moves >>= 1, curMove = 6 - curMove - curMove / 3) {
      // Skip if this is not a legal move
      if (!(moves & 1)) {
        continue;
      }

      // Calculate the minimax of the successor state
      Board sucBoard = board;
      sucBoard.handleMove(curMove);
      float sucMinimax = DISCOUNT * minimax(sucBoard, depth - 1, alpha, beta);

      // If this successor is the best so far, update values
      if (!turn && sucMinimax > bestSucMinimax) {
        bestMove = curMove;
        bestSucMinimax = sucMinimax;
        alpha = std::max(alpha, bestSucMinimax);
      } else if (turn && sucMinimax < bestSucMinimax) {
        bestMove = curMove;
        bestSucMinimax = sucMinimax;
        beta = std::min(beta, bestSucMinimax);
      }

#if AB_PRUNING
      // If alpha > beta, do not explore any further
      if (alpha >= beta) {
        break;
      }
#endif

      // If we have surpassed the endTime given by the caller, yield to caller
      if (std::chrono::system_clock::now() >= endTime) {
        return;
      }
    }

    move = bestMove;
#if ITERATIVE_DEEPENING
    std::cout << "Reached depth of " << depth << std::endl;
#endif
  }
}

std::string AgentMinimax::getAgentName() const { return "Minimax"; }

float AgentMinimax::minimax(Board board, size_t depth, float alpha,
                            float beta) {
#if MEMOIZE
  // Check if the minimax value has already been calculated
  auto boardValue = memo_.find(board);
  if (boardValue != memo_.end()) {
    // std::cout << "memo lookup" << std::endl;
    return boardValue->second;
  }
#endif

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
  float bestSucMinimax = -256 + (turn * 512.0);
  for (size_t moves = board.getSuccessorsFast(), curMove = 3; moves;
       moves >>= 1, curMove = 6 - curMove - curMove / 3) {
    // Skip if this is not a legal move
    if (!(moves & 1)) {
      continue;
    }

    // Calculate the minimax of the successor state
    Board sucBoard = board;
    sucBoard.handleMove(curMove);
    float sucMinimax = DISCOUNT * minimax(sucBoard, depth - 1, alpha, beta);

    // If this successor is the best so far, update values
    if (!turn && sucMinimax > bestSucMinimax) {
      bestSucMinimax = sucMinimax;
      alpha = std::max(alpha, bestSucMinimax);
    } else if (turn && sucMinimax < bestSucMinimax) {
      bestSucMinimax = sucMinimax;
      beta = std::min(beta, bestSucMinimax);
    }

#if AB_PRUNING
    // If alpha > beta, do not explore any further
    if (alpha >= beta) {
      break;
    }
#endif
  }

#if MEMOIZE
  if (std::abs(bestSucMinimax) > MAX_DISCOUNT) {
    memo_[board] = bestSucMinimax;
  }
#endif

  return bestSucMinimax;
}

float AgentMinimax::heuristic(const Board &board) {
  std::array<size_t, 2> threatCount = board.getThreatCount();
  return threatCount[0] * threatCount[0] * THREAT_WEIGHT -
         threatCount[1] * threatCount[1] * THREAT_WEIGHT;
}
