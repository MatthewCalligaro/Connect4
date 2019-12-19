/**
 * \file precomputed-values.hpp
 * \copyright Matthew Calligaro
 * \date December 2019
 * \brief Declares a HashTable of precomputed 8-ply minimax values
 */

#ifndef PRECOMPUTED_VALUES_HPP_
#define PRECOMPUTED_VALUES_HPP_

#include <unordered_map>
#include "board.hpp"

/** \brief a HashTable of precomputed 8-ply minimax values */
extern std::unordered_map<Board, float, BoardHasher> precomp;

#endif  // PRECOMPUTED_VALUES_HPP_
