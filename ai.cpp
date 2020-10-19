#include "ai.hpp"
#include <iostream>

g2048::ai::ai() {
	rnd = std::mt19937(seed());
}

bool g2048::ai::move(board &bd) {
	for (int i = 0; i < 10; i++) {
		std::cout << rnd() << '\n';
	}
	return true;
}
