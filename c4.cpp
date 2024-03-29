/**
 * \file c4.cpp
 * \copyright Matthew Calligaro, Aditya Khant
 * \date December 2019
 * \brief The entry point for the command line application
 */

#include <getopt.h>
#include <iostream>
#include "test.hpp"

/**
 * \brief Prints the program's usage information to standard out
 */
void printUsage() {
  std::cout << "Connect4: A command line Connect 4 implementation" << std::endl
            << "Copyright Matthew Calligaro, Aditya Khant December 2019"
            << std::endl
            << std::endl
            << "Usage: ./c4 [-t <test type>] [-n <number of trials>] [-d "
               "<depth>] [-v] [-h]"
            << std::endl
            << std::endl
            << "Options:" << std::endl
            << "-t: test type (single, time, win, winTrain, depth)" << std::endl
            << "-n: number of trials (positive integer number)" << std::endl
            << "-d: depth for minimax agents (positive integer number)"
            << std::endl
            << "-v: verbose" << std::endl
            << "-h: show this help message" << std::endl;
}

/**
 * \brief Parses command line arguments and executes the selected test
 */
int main(int argc, char **argv) {
  std::string testType = "single";
  size_t numTrials = 1;
  size_t depth = 4;
  bool verbose = false;
  int c;

  // Parse command line arguments
  while ((c = getopt(argc, argv, "t:n:d:vh")) != -1) {
    switch (c) {
      case 't':
        testType = optarg;
        break;
      case 'n':
        numTrials = atoi(optarg);
        break;
      case 'd':
        depth = atoi(optarg);
        break;
      case 'v':
        verbose = true;
        break;
      case 'h':
      case '?':
      default:
        printUsage();
        return 1;
    }
  }

  // If there are unparsed arguments, print usage and exit
  if (optind < argc) {
    printUsage();
    return 1;
  }

  // Execute the correct test specified by command line arguments
  if (testType == "single") {
    Test::singleGame();
  } else if (testType == "time") {
    Test::timeTrials(numTrials, 1, 12, "newtag", verbose);
  } else if (testType == "win") {
    Test::winTrials(numTrials, depth, verbose);
  } else if (testType == "winTrain") {
    Test::winTrialsWithTrain(numTrials, depth, verbose);
  } else if (testType == "depth") {
    Test::pairwiseDepthTrials(1, 12);
  } else {
    std::cerr << "test type was not recognized, enter 'h' for help"
              << std::endl;
    return 2;
  }

  return 0;
}
