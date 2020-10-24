#include "ai.hpp"

#include <algorithm>
#include <iostream>

bool g2048::monte_carlo::move(board &bd) {
	if (bd.is_gameover()) {
		return false;
	}
	std::array<int, 4> score;
	score.fill(-1);
	direction_mask mobility = bd.get_mobility();
	if (__builtin_popcount(mobility) == 1) {
		bd.move(__builtin_ctz(mobility));
		return true;
	}else {
		while (mobility != 0) {
			int d = __builtin_ctz(mobility);
			mobility ^= (1<<d);
			bd.move(d);
			for (int i = 0; i < search_count; i++) {
				int j = 0;
				while ((j < max_search_depth) && bd.move_random()) {
					j++;
				}
				// score[i] += bd.get_max();
				// score[i] += j;
				// score[i] += bd.get_num_of_blank();
				score[d] += bd.get_score();
				for (int k = 0; k < j; k++) {
					bd.undo();
				}
			}
			bd.undo();
		}
		int n = 0, s = -1;
		for (int i = 0; i < 4; i++) {
			if (score[i] > s) {
				n = i;
				s = score[i];
			}
		}
		bd.move(n);
	}
	return true;
}

bool g2048::full_search::move(board &bd) {
	if (bd.is_gameover()) {
		return false;
	}
	std::array<int, 4> score;
	score.fill(-1);
	direction_mask mobility = bd.get_mobility();
	if (__builtin_popcount(mobility) == 1) {
		bd.move(__builtin_ctz(mobility));
		return true;
	}else {
		while (mobility != 0) {
			int leaf_count = 0;
			int d = __builtin_ctz(mobility);
			mobility ^= (1<<d);
			bd.move(d);
			recursion(bd, max_search_depth, score[d], leaf_count);
			bd.undo();
			score[d] /= leaf_count;
		}

		int n = 0, s = -1;
		for (int i = 0; i < 4; i++) {
			if (score[i] > s) {
				n = i;
				s = score[i];
			}
		}
		bd.move(n);
	}
	return true;
}

void g2048::full_search::recursion(board &bd, const int limit, int &score, int &leaf_count) {
	if (bd.is_gameover() || limit <= 0) {
		leaf_count++;
		// evaluation
		score += bd.get_score();
		return;
	}
	direction_mask mobility = bd.get_mobility();
	if (__builtin_popcount(mobility) == 1) {
		bd.move(__builtin_ctz(mobility));
		recursion(bd, limit-1, score, leaf_count);
		bd.undo();
	}else {
		while (mobility != 0) {
			int d = __builtin_ctz(mobility);
			mobility ^= (1<<d);
			bd.move(d);
			recursion(bd, limit-1, score, leaf_count);
			bd.undo();
		}
	}
}
