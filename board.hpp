// Copyright 2019 Matthew Calligaro

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <array>
#include <cstdint>
#include <ostream>
#include <vector>

using std::array;
using std::ostream;
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
  Board();
  Board(const Board &other) = default;
  ~Board() = default;
  Board &operator=(const Board &other) = default;

  size_t getTurn() const;
  bool isWon() const;
  bool isDraw() const;
  bool isValidMove(size_t move) const;
  vector<size_t> getSuccessors() const;
  array<size_t, 2> getThreatCount() const;
  ostream &print(ostream &os) const;

  void handleMove(size_t move);

 private:
  uint64_t masks_[2] = {0, 0};
  size_t turn_;

  static size_t isWon(uint64_t mask);
};

ostream &operator<<(ostream &os, const Board &board);

#endif  // BOARD_HPP_
