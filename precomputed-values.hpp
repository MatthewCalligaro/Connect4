// Copyright 2019 Matthew Calligaro

#ifndef PRECOMPUTED_VALUES_HPP_
#define PRECOMPUTED_VALUES_HPP_

#include <unordered_map>
#include "board.hpp"

extern std::unordered_map<Board, float, BoardHasher> precomp;

#endif  // PRECOMPUTED_VALUES_HPP_
