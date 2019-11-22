// Copyright 2019 Matthew Calligaro

#include <array>
#include <vector>
#include <ostream>
#include "board.hpp"

using std::vector;
using std::array;
using std::ostream;
using std::endl;

Board::Board() : turn_{0} {}

size_t Board::getTurn() const {
    return turn_;
}

bool Board::isWon() const {
    // Check if player who most recently played won
    return isWon(masks_[!turn_]);
}

bool Board::isDraw() const {
    const uint64_t drawBoard = ((1L << 48) - 1) ^ ((1 << 6) | (1 << 13) |
        (1 << 20) | (1 << 27) | (1L << 34) | (1L << 41));
    return drawBoard == (masks_[0] | masks_[1]);
}

bool Board::isValidMove(size_t move) const {
    if (move > 6) {
        return false;
    }
    return !(((masks_[0] | masks_[1]) >> (move * 7 + 5)) & 1);
}

vector<size_t> Board::getSuccessors() const {
    vector<size_t> sucs;
    uint64_t invBoard = ~(masks_[0] | masks_[1]);

    // We can play in any column in which the top bit is open
    if ((invBoard >> 26) & 1) {
        sucs.push_back(3);
    }
    if ((invBoard >> 19) & 1) {
        sucs.push_back(2);
    }
    if ((invBoard >> 33) & 1) {
        sucs.push_back(4);
    }
    if ((invBoard >> 12) & 1) {
        sucs.push_back(1);
    }
    if ((invBoard >> 40) & 1) {
        sucs.push_back(5);
    }
    if ((invBoard >> 5) & 1) {
        sucs.push_back(0);
    }
    if ((invBoard >> 47) & 1) {
        sucs.push_back(6);
    }

    return sucs;
}

array<size_t, 2> Board::getThreatCount() const {
    array<size_t, 2> threatCount{ {0, 0} };
    uint64_t board = masks_[0] | masks_[1];

    // For each column, cheack each empty spaces from the top down for threats
    for (int column = 0; column < 7; ++column) {
        for (int bit = 5 + column * 7; bit >= column * 7; --bit) {
            if ((board >> bit) & 1) {
                break;
            }
            threatCount[0] += isWon(masks_[0] | (1L << bit));
            threatCount[1] += isWon(masks_[1] | (1L << bit));
        }
    }
    return threatCount;
}

ostream& Board::print(ostream& os) const {
    const char chars[3] = {'.', 'X', 'O'};

    // Iterate through the board row by row left to right top to bottom
    size_t bit = 5;
    while (bit != 49) {
        os << chars[((masks_[0] >> bit) & 1) + 2 * ((masks_[1] >> bit) & 1)]
            << " ";
        if (bit > 41) os << endl;
        bit = (bit + 7) % 50;
    }

    // Print column indices along the bottom
    os << "0 1 2 3 4 5 6" << endl;

    return os;
}

void Board::handleMove(size_t move) {
    // Find the lowest open bit in the column chosen by move
    uint64_t board = masks_[0] | masks_[1];
    size_t bit = move * 7;
    while ((board >> bit) & 1) {
        ++bit;
    }

    // Place a piece at bit in the correct mask and toggle turn_
    masks_[turn_] |= (1L << bit);
    turn_ = !turn_;
}

ostream& operator<<(ostream& os, const Board& board) {
    return board.print(os);
}

// Source: Fhourstones Benchmark by John Tromp
// https://github.com/qu1j0t3/fhourstones
size_t Board::isWon(uint64_t mask) {
    // check \ diagonal
    uint64_t y = mask & (mask >> 6);
    if (y & (y >> 2 * 6)) {
        return 1;
    }

    // check horizontal
    y = mask & (mask >> 7);
    if (y & (y >> 2 * 7)) {
        return 1;
    }

    // check / diagonal
    y = mask & (mask >> 8);
    if (y & (y >> 2 * 8)) {
        return 1;
    }

    // check vertical
    y = mask & (mask >> 1);
    if (y & (y >> 2)) {
        return 1;
    }

    return 0;
}
