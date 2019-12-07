// Copyright 2019 Matthew Calligaro

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <array>
#include <cstdint>
#include <ostream>
#include <vector>

using std::vector;

// Bitboard encoding
// .  .  .  .  .  .  .  TOP
// 5 12 19 26 33 40 47
// 4 11 18 25 32 39 46
// 3 10 17 24 31 38 45
// 2  9 16 23 30 37 44
// 1  8 15 22 29 36 43
// 0  7 14 21 28 35 42  BOTTOM

class Board {
 public:
  static const size_t MOVE_ORDER[7];

  Board();
  Board(const Board &other) = default;
  Board(uint64_t xMask, uint64_t oMask);
  ~Board() = default;
  Board &operator=(const Board &other) = default;
  vector<char> getBoardVector();
  bool operator==(const Board &rhs) const;
  
  size_t getTurn() const;
  bool isWon() const;
  bool isDraw() const;
  bool isValidMove(size_t move) const;
  float getReward() const;
  std::vector<size_t> getSuccessors() const;
  size_t getSuccessorsFast() const;
  std::array<size_t, 2> getThreatCount() const;
  std::ostream &print(std::ostream &os) const;

  void handleMove(size_t move);

 private:
  uint64_t masks_[2];
  size_t turn_;

  static size_t isWon(uint64_t mask);

  friend struct BoardHasher;
};

std::ostream &operator<<(std::ostream &os, const Board &board);

struct BoardHasher {
  size_t operator()(const Board &b) const;
};

#endif  // BOARD_HPP_
