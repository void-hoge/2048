#pragma once

#include "board.hpp"
#include <random>

namespace g2048 {

class ai {
private:
	std::random_device seed;
	std::mt19937 rnd;
	const int num = 1<<8;
	int hoge;
public:
	ai();
	bool move(board &bd);
};

} //namespace g2048
