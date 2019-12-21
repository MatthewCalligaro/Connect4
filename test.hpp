/**
 * \file test.hpp
 * \copyright Matthew Calligaro, Aditya Khant
 * \date December 2019
 * \brief Declares the Test class
 */

#ifndef TEST_HPP_
#define TEST_HPP_

#include <string>

/**
 * \class Test
 * \brief Provides several static testing functions
 */
class Test {
 public:
  /**
   * \brief Plays a single game between two agents
   */
  static void singleGame();

  /**
   * \brief Performs time trials of the minimax agent at a variety of depths
   * \param numTrials   The numeber of games to play
   * \param minDepth    The lowest depth to test (inclusive)
   * \param maxDepth    The highest depth to test (inclusive)
   * \param tag         A string to denote the test in the output filenames
   * \param verbose     Print extra information as the trials complete
   */
  static void timeTrials(size_t numTrials, size_t minDepth, size_t maxDepth,
                         std::string tag, bool verbose = false);

  /**
   * \brief Play several games between two agents as both X and O
   * \param numTrials The number of trials to play in each configuration
   * \param depth     The depth to use for minimax-based agents
   * \param verbose   Print extra information as the trials complete
   */
  static void winTrials(size_t numTrials, size_t depth, bool verbose = false);

  /**
   * \brief Plays several games with agents that require training
   * \param numTrials The number of trials to play in each configuration
   * \param depth     The depth to use for minimax-based agents
   * \param verbose   Print extra information as the trials complete
   */
  static void winTrialsWithTrain(size_t numTrials, size_t depth,
                                 bool verbose = false);

  /**
   * \brief Play all pairwise games between minimax agents of a range of depths
   * \param minDepth    The lowest depth to test (inclusive)
   * \param maxDepth    The highest depth to test (inclusive)
   */
  static void pairwiseDepthTrials(size_t minDepth, size_t maxDepth);
};

#endif  // TEST_HPP_
