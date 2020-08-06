#include "board.hpp"
#include <iostream>
#include <iomanip>

g2048::board::board() {
	rnd = std::mt19937(seed());
	for (auto &i: data) {
		for (auto &j: i) {
			j = 0;
		}
	}
}

void g2048::board::show() {
	for (auto &i: data) {
		for (auto &j: i) {
			std::cout << std::setw(5) << j << ' ';
		}
		std::cout << '\n';
	}
}

bool g2048::board::marge() {
	return true;
}
