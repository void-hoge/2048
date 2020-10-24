#include "board.hpp"
#include "ai.hpp"

#include <iostream>

using namespace g2048;

void test_multiple(const int count) {
	monte_carlo hoge_ai(1<<7, 6);
	int score = 0;
	for (int i = 0; i < count; i++) {
		board bd;
		while (hoge_ai.move(bd)) {
		}
		std::cout << "score:" << bd.get_score() << '\n';
		bd.show();
		score += bd.get_score();
	}
	std::cout << "average score:" << (double)score/count << '\n';
}

void test_single() {
	monte_carlo hoge_ai(1<<10, 8);
	// full_search hoge_ai(7);
	board bd;
	while (hoge_ai.move(bd)) {
		std::cout << "turn:" << bd.get_turn() << '\n';
		std::cout << "score:" << bd.get_score() << '\n';
		bd.show();
	}
}

int main() {
	// test_multiple(32);
	test_single();
	return 0;
}
