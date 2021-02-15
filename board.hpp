#pragma once

#include <vector>
#include <array>
#include <random>
#include <utility>

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
	log(field data, std::array<field, 4>  next, int score, std::array<int, 4> next_score) {
		this->data = data;
		this->next = next;
		this->score = score;
		this->next_score = next_score;
	}
	field data;
	std::array<field, 4> next;
	int score;
	std::array<int, 4> next_score;
};

class board {
public:
	board();
	bool move(const direction d);
	bool move_random();
	void show() const;
	bool is_gameover() const;
	direction_mask get_mobility() const;
	bool put_random();
	bool undo();
	int get_turn() const;
	int get_score() const;
	int get_num_of_blank() const;
	int get_max() const;
	int get_cell(const int x, const int y) const;
private:
	field data;
	std::vector<log> history;
	std::array<field, 4> next;
	std::array<int, 4> next_score;
	bool set(const int x, const int y, const int num);
	int make_mobility();
	std::pair<field, int> get_next(const direction d) const;
	std::pair<field, int> marge(field fd) const;
	field slide(field fd) const;
	field horizontal_flip(field fd) const;
	field diagonal_flip(field fd) const;
	int get_sum(const field fd) const;
	int turn;
	int score;

	std::random_device seed;
	std::mt19937 rnd;
	const int initial_panel = 2;
};

} // namespace g2048
