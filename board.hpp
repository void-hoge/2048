#pragma once

#include <vector>
#include <array>
#include <random>

namespace g2048 {

const int size = 4;
using direction_mask = int;
const direction_mask upper_mask = 0b0001;
const direction_mask lower_mask = 0b0010;
const direction_mask right_mask = 0b0100;
const direction_mask left_mask  = 0b1000;

using direction = int;
const direction upper = 0;
const direction lower = 1;
const direction right = 2;
const direction left = 3;

using field = std::array<std::array<int, size>, size>;

class log {
public:
	log(field data, std::array<field, 4>  next):data(data), next(next) {}
	field data;
	std::array<field, 4> next;
};

class board {
public:
	board();
	bool move(const direction d);
	void show() const;
	bool is_gameover() const;
	bool put_random();
	bool undo();
private:
	field data;
	std::vector<log> history;
	std::array<field, 4> next;
	bool set(const int x, const int y, const int num);
	int get_mobility();
	field get_next(const direction d) const;
	field marge(field fd) const;
	field slide(field fd) const;
	field horizontal_flip(field fd) const;
	field diagonal_flip(field fd) const;
	int get_sum(const field fd) const;

	std::random_device seed;
	std::mt19937 rnd;
	const int initial_panel = 2;
};

} // namespace g2048
