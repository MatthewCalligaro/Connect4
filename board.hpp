/**
 * \file board.hpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Declares the Board class
 */

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

/**
 * \class Board
 * \brief An efficient implementation of a Connect 4 board
 */
class Board {
 public:
  /** \brief The order of moves returned by getSuccessors */
  static const size_t MOVE_ORDER[7];

  Board();
  Board(const Board &other) = default;
  Board(uint64_t xMask, uint64_t oMask);
  ~Board() = default;
  Board &operator=(const Board &other) = default;
  bool operator==(const Board &rhs) const;

  /**
   * \brief Determines the player whose turn it is
   * \returns 0 if it is X's turn, 1 if it is O's turn
   */
  size_t getTurn() const;

  /**
   * \brief Determines if either player has won the game
   * \returns True if the game has been won
   */
  bool isWon() const;

  /**
   * \brief Determines if the game has ended in a draw (board entirely filled)
   * \returns True if the game is at a draw
   */
  bool isDraw() const;

  /**
   * \brief Determines if a column index is a valid move for the board
   * \param move    The column of the potential move
   * \returns True if the move is valid
   */
  bool isValidMove(size_t move) const;

  /**
   * \brief Determines the reward of the current board
   * \returns 1 if X won, -1 if O won, and 0 otherwise
   */
  float getReward() const;

  /**
   * \brief Determines the valid moves from the current board state
   * \returns A vector containing the column indices of the valid moves
   */
  std::vector<size_t> getSuccessors() const;

  /**
   * \brief Determines the valid moves from the current board state (faster)
   * \returns A size_t in which the first 7 bits indicate which moves are valid
   * \note The bits correspond to the moves in MOVE_ORDER, so the 0th bit
   * corresponds to collumn 3, the 1st bit corresponds to column 2, and so on
   */
  size_t getSuccessorsFast() const;

  /**
   * \brief Calculates the number of threats for each player
   * \returns An array storing [X threats, O threats]
   * \note An X threat is any open space on the board for which there would be
   * four X tokens in a row if an X token was placed there
   */
  std::array<size_t, 2> getThreatCount() const;

  /**
   * \brief Returns the board formatted as a row-major 1D vector of chars
   * \returns The board formatted as a vector
   * \note X tokens are denoted as 'X', O tokens are denoted as 'O', and empty
   * spaces are denoted as '.'
   */
  vector<char> getBoardVector();

  /**
   * \brief Prints a board to an output stream
   * \param os    The output stream to which the board is printed
   * \returns The output stream which was passed in
   */
  std::ostream &print(std::ostream &os) const;

  /**
   * \brief Applies a move to the board in the given column
   * \param The column index in which the current player should play
   */
  void handleMove(size_t move);

 private:
  /** \brief The X and O bitmasks representing the pieces on the board */
  uint64_t masks_[2];

  /** \brief The player whose turn it is (0 for X, 1 for O) */
  size_t turn_;

  /**
   * \brief Determines whether a particular bitmask represents a win state
   * \param mask    The bitmask representing the pieces of one player
   * \returns 1 if the game is won for the player, 0 otherwise
   */
  static size_t isWon(uint64_t mask);

  friend struct BoardHasher;
};

/**
 * \brief Overloads the print operator to use the Board print function
 * \param os    The output stream to which the board is printed
 * \param board The board to print to the output stream
 * \returns The output stream which was passed in
 */
std::ostream &operator<<(std::ostream &os, const Board &board);

/**
 * \struct BoardHasher
 * \brief Implements a hash function for the Board class
 */
struct BoardHasher {
  size_t operator()(const Board &b) const;
};

#endif  // BOARD_HPP_
