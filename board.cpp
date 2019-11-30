// Copyright 2019 Matthew Calligaro

#include "board.hpp"
#include <array>
#include <ostream>
#include <vector>

size_t const Board::MOVE_ORDER[7] = {3, 2, 4, 1, 5, 0, 6};

Board::Board() : masks_{0, 0}, turn_{0} {}

Board::Board(uint64_t xMask, uint64_t oMask) : masks_{xMask, oMask} {
  // Count x and o pieces to determine turn
  size_t xPieces = 0;
  for (size_t i = 0; i < 47; ++i) {
    xPieces += xMask & 1;
    xMask >>= 1;
  }

  size_t oPieces = 0;
  for (size_t i = 0; i < 47; ++i) {
    oPieces += xMask & 1;
    oMask >>= 1;
  }

  turn_ = xPieces > oPieces;
}

bool Board::operator==(const Board &rhs) const {
  return masks_[0] == rhs.masks_[0] && masks_[1] == rhs.masks_[1];
}

size_t Board::getTurn() const { return turn_; }

bool Board::isWon() const {
  // Check if player who most recently played won
  return isWon(masks_[!turn_]);
}

bool Board::isDraw() const {
  const uint64_t drawBoard =
      ((1UL << 48) - 1) ^ ((1 << 6) | (1 << 13) | (1 << 20) | (1 << 27) |
                           (1UL << 34) | (1UL << 41));
  return drawBoard == (masks_[0] | masks_[1]);
}

bool Board::isValidMove(size_t move) const {
  if (move > 6) {
    return false;
  }
  return !(((masks_[0] | masks_[1]) >> (move * 7 + 5)) & 1);
}

float Board::getReward() const { return isWon() * (turn_ * 2.0 - 1.0); }

std::vector<size_t> Board::getSuccessors() const {
  std::vector<size_t> sucs;
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

size_t Board::getSuccessorsFast() const {
  uint64_t invBoard = ~(masks_[0] | masks_[1]);
  return ((invBoard >> 26) & 1) | ((invBoard >> 18) & 2) |
         ((invBoard >> 31) & 4) | ((invBoard >> 9) & 8) |
         ((invBoard >> 36) & 16) | (invBoard & 32) | ((invBoard >> 41) & 64);
}

std::array<size_t, 2> Board::getThreatCount() const {
  std::array<size_t, 2> threatCount{{0, 0}};
  uint64_t board = masks_[0] | masks_[1];

  // For each column, cheack each empty spaces from the top down for threats
  for (int column = 0; column < 7; ++column) {
    for (int bit = 5 + column * 7; bit >= column * 7; --bit) {
      if ((board >> bit) & 1) {
        break;
      }
      threatCount[0] += isWon(masks_[0] | (1UL << bit));
      threatCount[1] += isWon(masks_[1] | (1UL << bit));
    }
  }
  return threatCount;
}

std::ostream &Board::print(std::ostream &os) const {
  const char chars[3] = {'.', 'X', 'O'};

  // Iterate through the board row by row left to right top to bottom
  size_t bit = 5;
  while (bit != 49) {
    os << chars[((masks_[0] >> bit) & 1) + 2 * ((masks_[1] >> bit) & 1)] << " ";
    if (bit > 41) os << std::endl;
    bit = (bit + 7) % 50;
  }

  // Print column indices along the bottom
  os << "0 1 2 3 4 5 6" << std::endl;

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
  masks_[turn_] |= (1UL << bit);
  turn_ = !turn_;
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
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

size_t BoardHasher::operator()(const Board &b) const {
  // Shift mask_[1] left by 16 bits so the top board bit becomes the MSB
  return b.masks_[0] ^ (b.masks_[1] << 16);
}
