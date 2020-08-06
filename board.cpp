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
	put_random();
	put_random();
	put_random();
	put_random();
}

bool g2048::board::move(const direction d) {
	bool frag = false;
	switch (d) {
		case upper:
			diagonal_flip();
			horizontal_flip();
			break;
		case lower:
			diagonal_flip();
			break;
		case right:
			break;
		case left:
			horizontal_flip();
			break;
		default:
			return false;
	}

	if (slide() == true) {
		frag = true;
	}
	if (marge() == true) {
		frag = true;
		slide();
	}

	switch (d) {
		case upper:
			horizontal_flip();
			diagonal_flip();
			break;
		case lower:
			diagonal_flip();
			break;
		case right:
			break;
		case left:
			horizontal_flip();
			break;
	}
	return frag;
}

void g2048::board::show() const{
	int width = 5;
	std::cout << '+';
	for (int k = 0; k < data.size(); k++) {
		for (int l = 0; l < width; l++) {
			std::cout << '-';
		}
		std::cout << '+';
	}
	std::cout << '\n';
	for (auto i: data) {
		std::cout << '|';
		for (auto j: i) {
			if (j == 0) {
				std::cout << std::setw(width) << ' ' << '|';
			}else {
				std::cout << std::setw(width) << j << '|';
			}
		}
		std::cout << '\n';
		std::cout << '+';
		for (int k = 0; k < i.size(); k++) {
			for (int l = 0; l < width; l++) {
				std::cout << '-';
			}
			std::cout << '+';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

bool g2048::board::is_gameover() const {
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			if (data[i][j] == 0) {
				return false;
			}
		}
	}
	for (int i = 0; i < data.size()-1; i++) {
		for (int j = 0; j < data[i].size()-1; j++) {
			if (data[i][j] == data[i][j+1]) {
				return false;
			}
			if (data[i][j] == data[i+1][j]) {
				return false;
			}
		}
	}
	if (data[data.size()-1][data.size()-1] == data[data.size()-1][data.size()-2]) {
		return false;
	}
	if (data[data.size()-1][data.size()-1] == data[data.size()-2][data.size()-1]) {
		return false;
	}
	return true;
}

bool g2048::board::put_random() {
	std::vector<int> blank_x;
	std::vector<int> blank_y;
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			if (data[i][j] == 0) {
				blank_x.push_back(i);
				blank_y.push_back(j);
			}
		}
	}
	if (blank_x.size() == 0) {
		return false;
	}
	int pos = rnd()%blank_x.size();
	int n = rnd()%4;
	if (n == 0) {
		n = 4;
	}else {
		n = 2;
	}
	data[blank_x[pos]][blank_y[pos]] = n;
	return true;
}

bool g2048::board::set(const int x, const int y, const int num) {
	if ((x < 0) && (x >= g2048::size)) {
		return false;
	}
	if ((y < 0) && (y >= g2048::size)) {
		return false;
	}
	data[x][y] = num;
	return true;
}

bool g2048::board::marge() {
	bool frag = false;
	for (auto &line: data) {
		for (int i = line.size()-1; i > 0; i--) {
			if (line[i] == 0) {
				continue;
			}
			if (line[i] == line[i-1]) {
				frag = true;
				line[i] *= 2;
				line[i-1] = 0;
				i--;
			}
		}
	}
	return frag;
}

bool g2048::board::slide() {
	bool frag = false;
	for (auto &line: data) {
		for (int i = line.size()-1; i > 0; i--) {
			for (int c = 0; (c < 3)&&(line[i] == 0); c++) {
				for (int j = i; j > 0; j--) {
					if (line[j-1] != 0) {
						frag = true;
					}
					line[j] = line[j-1];
				}
				line[0] = 0;
			}
		}
	}
	return frag;
}

void g2048::board::horizontal_flip() {
	for (auto &line: data) {
		for (int i = 0; i < line.size()/2; i++) {
			std::swap(line[i], line[line.size()-i-1]);
		}
	}
}

void g2048::board::diagonal_flip() { // coordinate transform
	for (int i = 0; i < data.size(); i++) {
		for (int j = i; j < data[i].size(); j++) {
			std::swap(data[i][j], data[j][i]);
		}
	}
}
