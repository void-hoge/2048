#pragma once

#include <vector>
#include <array>
#include <vector>
#include <random>

namespace g2048 {

const int size = 4;
using direction = int;
const direction upper = 0b0001;
const direction lower = 0b0010;
const direction right = 0b0100;
const direction left  = 0b1000;

class board {
public:
	board();
	bool move(const direction d);
	void show();
private:
	std::array<std::array<int, size>, size> data;
	bool marge();
	bool slide();
	std::random_device seed;
	std::mt19937 rnd;
};

} // namespace g2048
