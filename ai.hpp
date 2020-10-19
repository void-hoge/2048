#pragma once

#include "board.hpp"
#include <random>

namespace g2048 {

class ai {
private:
	std::random_device seed;
	std::mt19937 rnd;
public:
	ai();
	bool move(board &bd);
};

} //namespace g2048
