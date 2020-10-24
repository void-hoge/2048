#pragma once

#include "board.hpp"

#include <random>

namespace g2048 {

class ai {
protected:
	std::random_device seed;
	std::mt19937 rnd;
	const int max_serch_depth;
public:
	ai(int msd): max_serch_depth(msd) {
		rnd = std::mt19937(seed());
	};
	virtual bool move(board &bd) = 0;
};

class monte_carlo: public ai {
public:
	const int serch_count;
	monte_carlo(int sc, int msd): ai(msd), serch_count(sc) {};
	bool move(board &bd);
};

class full_serch: public ai {
private:
	void recursion(board &bd, const int limit, int &socre, int &leaf_count);
public:
	full_serch(int msd): ai(msd) {};
	bool move(board &bd);
};

} //namespace g2048
