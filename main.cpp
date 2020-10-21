#include <iostream>
#include "board.hpp"
#include "ai.hpp"
#include <string>

using namespace g2048;

int main() {
	// std::cout << "2048 solving" << std::endl;
	board bd;
	ai hoge_ai;
	bd.show();
	while (hoge_ai.move(bd)) {
		std::cout << "turn:" << bd.get_turn() << '\n';
		std::cout << "total score:" << bd.get_score() << '\n';
		bd.show();
	}
	// while (bd.is_gameover() == false) {
	// 	bd.show();
	// 	hoge:
	// 	std::string command = "";
	// 	std::cout << ">>";
	// 	std::cin >> command;
	// 	if (command == "upper") {
	// 		if(bd.move(upper) == false) {
	// 			goto hoge;
	// 		}
	// 	}else if(command == "lower") {
	// 		if(bd.move(lower) == false) {
	// 			goto hoge;
	// 		}
	// 	}else if (command == "right") {
	// 		if(bd.move(right) == false) {
	// 			goto hoge;
	// 		}
	// 	}else if (command == "left") {
	// 		if(bd.move(left) == false) {
	// 			goto hoge;
	// 		}
	// 	}else {
	// 		goto hoge;
	// 	}
	// }
	return 0;
}
