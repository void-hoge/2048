#include "ai.hpp"
#include <iostream>
#include <algorithm>

g2048::ai::ai() {
	rnd = std::mt19937(seed());
	hoge = 0;
}

bool g2048::ai::move(board &bd) {
	if (bd.is_gameover()) {
		return false;
	}
	std::array<int, 4> score;
	score.fill(0);
	direction_mask mobility = bd.get_mobility();
	for (int i = 0; i < 4; i++) {
		if ((mobility & (1<<i)) == 0) {
			score[i] = -100;
		}else{
			bd.move(i);
			for (int l = 0; l < num; l++) {
				int j = 0;
				while ((j < 5) && bd.move_random()) {
					j++;
				}
				// score[i] += bd.get_max();
				score[i] += bd.get_score();
				// score[i] += j;
				for (int k = 0; k < j; k++) {
					bd.undo();
				}
				// bd.show();
			}
			bd.undo();
		}
	}
	int n, s = -100;
	for (int i = 0; i < 4; i++) {
		std::cout << i << ":" << score[i] << '\n';
		if (score[i] > s) {
			n = i;
			s = score[i];
		}
	}
	std::cout << "selected: " << n << '\n';
	bd.move(n);
	return true;
}
