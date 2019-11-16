// Copyright 2019 Matthew Calligaro

#include <algorithm>
#include "agent-minimax.hpp"

size_t AgentMinimax::getMove(Board board) {
    size_t turn = board.getTurn();
    size_t depth = FIRST_DEPTH;
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

    return bestMove;
}

std::string AgentMinimax::getAgentName() const {
    return "Minimax";
}

float AgentMinimax::minimax(Board board, size_t depth, float alpha, 
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
        return 0;
    }

    // Find the best successor
    vector<size_t> moves = board.getSuccessors();
    float bestSucMinimax = -256 + (turn * 512.0);
    for (size_t move : moves) {
        // Calculate the minimax of the successor state
        Board sucBoard = board;
        sucBoard.handleMove(move);
        float sucMinimax = minimax(sucBoard, depth - 1, alpha, beta);

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
