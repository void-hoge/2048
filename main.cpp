#include <iostream>
#include "board.hpp"
#include <string>

using namespace g2048;

int main() {
	std::cout << "2048 solving" << std::endl;
	board bd;
	while (bd.is_gameover() == false) {
		bd.show();
		hoge:
		std::string command = "";
		std::cout << ">>";
		std::cin >> command;
		if (command == "upper") {
			if(bd.move(upper) == false) {
				goto hoge;
			}
		}else if(command == "lower") {
			if(bd.move(lower) == false) {
				goto hoge;
			}
		}else if (command == "right") {
			if(bd.move(right) == false) {
				goto hoge;
			}
		}else if (command == "left") {
			if(bd.move(left) == false) {
				goto hoge;
			}
		}else {
			goto hoge;
		}
		bd.put_random();
	}
	return 0;
}
