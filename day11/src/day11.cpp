#include "common/common.h"

#include <iostream>
#include <set>

struct Galaxy {
	int id;
	long x, y;
};

long operator-(const Galaxy& l, const Galaxy& r) {
	long dx, dy;
	dx = std::abs(r.x - l.x);
	dy = std::abs(r.y - l.y);

	return dx + dy;
}

bool operator==(const Galaxy& l, const Galaxy& r) {
	return l.x == r.x && l.y == r.y;
}

std::vector<Galaxy> Parse(const std::vector<char>& input) {
	int current = 0;
	int line = 0;
	int column = -1;

	int columnLength = 0;
	std::vector<Galaxy> galaxies; 
	int count = 1;

	while (current < input.size()) {
		column++;

		switch(input[current]) {
			case '\n': 
				line++;
				columnLength = column;
				column = -1;
				break;
			case '#':
				galaxies.push_back(Galaxy {count++, column, line });
				break;
			case '.': 
				break;
			default:
				std::cout << "Unknown character\n";
				exit(1);
		}

		current++;
	}

	std::set<int> emptyCols;
	for (int i = 0; i < columnLength; i++) {
		emptyCols.insert(i);
	}

	std::set<int> emptyRows; 
	for (int i = 0; i < line; i++) {
		emptyRows.insert(i);
	}

	for (auto g : galaxies) {
		if (emptyCols.find(g.x) != emptyCols.end()) {
			emptyCols.erase(g.x);
		}

		if (emptyRows.find(g.y) != emptyRows.end()) {
			emptyRows.erase(g.y);
		}
	}

	for (auto c = emptyCols.rbegin(); c != emptyCols.rend(); c++) {
		auto giter = galaxies.begin();
		while (giter != galaxies.end()) {
			if (giter->x > *c) {
				giter->x += (1000000 - 1);
			}
			giter++;
		}
	}

	for (auto r = emptyRows.rbegin(); r != emptyRows.rend(); r++) {
		auto giter = galaxies.begin();
		while (giter != galaxies.end()) {
			if (giter->y > *r) {
				giter->y += (1000000 - 1);
			}
			giter++;
		}
	}

	return galaxies;
}

void part1(std::vector<Galaxy>& galaxies) {
	long total = 0;

	int count = 1;
	for (int i = 0; i < galaxies.size(); i++) {
		for (int j = i + 1; j < galaxies.size(); j++) {
			long diff = std::abs(galaxies[j] - galaxies[i]);
			std::cout << count << "\t";
			std::cout << galaxies[i].id << "(" << galaxies[i].x << "," << galaxies[i].y << ")\t";
			std::cout << galaxies[j].id << "(" << galaxies[j].x << "," << galaxies[j].y << ")\t";
			std::cout << diff << std::endl;
			total += diff;
			count++;
		}
	}

	std::cout << "Totals: " << total << std::endl;
}

int main(int argc, char *argv[]) { 
	std::vector<char> data = Common::ReadFile(argv[1]);

	auto galaxies = Parse(data);
	part1(galaxies);
	// part2(galaxies);

    return 0; 
}
