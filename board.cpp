#include "board.hpp"
#include "bitmanipulations.hpp"
#include <iostream>
#include <iomanip>

namespace bm = bitmanipulations;

g2048::board::board() {
	rnd = std::mt19937(seed());
	for (auto &i: data) {
		for (auto &j: i) {
			j = 0;
		}
	}
	for (int i = 0; i < initial_panel; i++) {
		put_random();
	}
	get_mobility();
}

bool g2048::board::undo() {
	if (history.empty() == true) {
		return false;
	}
	data = history.end()->data;
	next = history.end()->next;
	history.pop_back();
	return true;
}

int g2048::board::get_sum(const field fd) const{
	int sum = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			sum += fd[i][j];
		}
	}
	return sum;
}

bool g2048::board::move(const direction d) {
	if (get_sum(next[d]) == 0) {
		return false;
	}
	switch (d) {
		case upper:
		case lower:
		case right:
		case left:{
			break;
		}
		default:{
			return false;
		}
	}

	history.push_back(log(data, next));
	data = next[d];
	put_random();
	get_mobility();
	return true;
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

int g2048::board::get_mobility() {
	int count = 4;
	for (direction i = 0; i < 4; i++) {
		next[i] = get_next(i);
		if (next[i] == data) {
			for (auto& tmp: next[i]) {
				tmp.fill(0);
			}
			count--;
		}
	}
	return count;
}

g2048::field g2048::board::get_next(const direction d) const {
	field fd = data;
	switch (d) {
		case upper: {
			fd = diagonal_flip(fd);
			fd = horizontal_flip(fd);
			break;
		}
		case lower: {
			fd = diagonal_flip(fd);
			break;
		}
		case right: {
			break;
		}
		case left: {
			fd = horizontal_flip(fd);
			break;
		}
	}

	fd = slide(fd);
	fd = marge(fd);
	fd = slide(fd);

	switch (d) {
		case upper: {
			fd = horizontal_flip(fd);
			fd = diagonal_flip(fd);
			break;
		}
		case lower: {
			fd = diagonal_flip(fd);
			break;
		}
		case right: {
			break;
		}
		case left: {
			fd = horizontal_flip(fd);
			break;
		}
	}
	return fd;
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

g2048::field g2048::board::marge(field fd) const{
	bool frag = false;
	for (auto &line: fd) {
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
	return fd;
}

g2048::field g2048::board::slide(field fd) const{
	bool frag = false;
	for (auto &line: fd) {
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
	return fd;
}

g2048::field g2048::board::horizontal_flip(field fd) const{
	for (auto &line: fd) {
		for (int i = 0; i < line.size()/2; i++) {
			std::swap(line[i], line[line.size()-i-1]);
		}
	}
	return fd;
}

g2048::field g2048::board::diagonal_flip(field fd) const{ // coordinate transform
	for (int i = 0; i < fd.size(); i++) {
		for (int j = i; j < fd[i].size(); j++) {
			std::swap(fd[i][j], fd[j][i]);
		}
	}
	return fd;
}
