/**
 * \file board.hpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Declares the Game class
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include <future>
#include <list>
#include <memory>
#include <ostream>
#include "agent.hpp"
#include "board.hpp"

class Game {
 public:
  Game() = delete;
  Game(const Game &other) = default;

  /**
   * \brief Creates a new game with the specified agents and time limit
   * \param xAgent    The agent playing as X (first move)
   * \param oAgent    The agent playing as O (second move)
   * \param turnTime  The maximum time in miliseconds an agent can take per turn
   */
  Game(std::shared_ptr<Agent> xAgent, std::shared_ptr<Agent> oAgent,
       size_t turnTime = 2000);

  ~Game() = default;
  Game &operator=(const Game &other) = default;

  /**
   * \brief Allows the agents to play the game to completion
   * \param verbose   If true, print information as the game progresses
   * \returns The winner (0 if X won, 1 if O won, or 2 if a draw)
   */
  size_t execute(bool verbose = false);

  /**
   * \brief Allows the agents to play the game to completion
   * \param xMoveTimes  A place to store the time for each move by the X agent
   * \param oMoveTimes  A place to store the time for each move by the O agent
   * \param verbose     If true, print information as the game progresses
   * \returns The winner (0 if X won, 1 if O won, or 2 if a draw)
   */
  size_t execute(std::array<double, 42> &xMoveTimes,
                 std::array<double, 42> &oMoveTimes, bool verbose = false);

  /**
   * \brief Prints the current board state of the game
   * \param os    The output stream to which the board is printed
   * \returns the output stream which was passed in
   */
  std::ostream &printBoard(std::ostream &os) const;

 private:
  /** \brief A magic number encoding when the agent did not chose a move */
  static const size_t NO_MOVE = 15942;

  /** \brief The current board state */
  Board board_;

  /** \brief The X and O agents */
  std::shared_ptr<Agent> agents_[2];

  /** \brief The maximum time in miliseconds an agent can take per turn */
  size_t turnTime_;

  /** \brief The agent allowed to take the next move (0 for X, 1 for O) */
  size_t move_;

  /**
   * \brief Allows an agent to determine its next move
   * \param agent   The agent taking the move
   * \returns the column move (column index) taken by the agent
   */
  size_t getMove(size_t agent);
};

#endif  // GAME_HPP_
