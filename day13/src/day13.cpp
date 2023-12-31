#include "common/common.h"

#include <iostream>

enum TileType {
	ASH,
	ROCK
};

typedef std::vector<TileType> row_t;
typedef std::vector<row_t> map_t;

row_t parseRow(const std::vector<char>& input, int& current, int& line) {
	row_t row;

	while (input[current] == '.' || input[current] == '#') {
		switch (input[current]) {
			case '#':
				row.push_back(ROCK);
				break;
			case '.':
				row.push_back(ASH);
				break;
			default:
				std::cout << "Unknown character: " << input[current] << "\n";
				exit(1);
		}
		current++;
	}

	return row;
}

map_t parseMap(const std::vector<char>& input, int& current, int& line) {
	map_t map;

	while (input[current] == '.' || input[current] == '#') {
		map.push_back(parseRow(input, current, line));
		Common::match(input, current, line, '\n');
	}

	return map;
}

std::vector<map_t> Parse(const std::vector<char>& data) {
    int current = 0, line = 0;

	std::vector<map_t> maps;

    while (current < data.size()) {
		maps.push_back(parseMap(data, current, line));
		Common::consumeNewlines(data, current, line);
    }

	return maps;
}

bool isRowSymmetric(const map_t& map, const int row, const int center) {
	int a = center, b = center + 1;

	for (; a >= 0 && b < map[row].size(); a--, b++) {
		if (map[row][a] != map[row][b]) {
			return false;
		}
	}

	return true;
}

bool isColSymmetric(const map_t& map, const int col, const int center) {
	int a = center, b = center + 1;

	for (; a >= 0 && b < map.size(); a--, b++) {
		if (map[a][col] != map[b][col]) {
			return false;
		}
	}

	return true;
}

long findColSym(const map_t& map) {
	for (int i = 0; i < map[0].size() - 1; i++) {
		int symCount = 0;
		for (int j = 0; j < map.size(); j++) {
			if (isRowSymmetric(map, j, i)) {
				symCount++;
			}
		}

		if (symCount == map.size()) {
			// std::cout << "Column Symmetric at " << i + 1 << "\n";
			return (i + 1);
		}
	}

	return 0;
}

long findRowSym(const map_t& map) {
	for (int i = 0; i < map.size() - 1; i++) {
		int symCount = 0;
		for (int j = 0; j < map[0].size(); j++) {
			if (isColSymmetric(map, j, i)) {
				symCount++;
			}
		}

		if (symCount == map[0].size()) {
			// std::cout << "Row Symmetric at " << i + 1 << "\n";
			return (100 * (i + 1));
		}
	}

	return 0;
}

long findSym(const map_t& map) {
	long val = findColSym(map);
	if (val == 0) {
		val = findRowSym(map);
	}

	return val;
}

void part1(const std::vector<map_t>& maps) {
	long total = 0;
	for (auto map : maps) {
		total += findSym(map);
	}

	std::cout << "Total: " << total << "\n";
}

long fix(map_t& map) {
	long original = findSym(map);
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if (map[i][j] == ROCK) {
				map[i][j] = ASH;
				long val = findRowSym(map);
				if (val == 0 || val == original) {
					val = findColSym(map);
				}
				map[i][j] = ROCK;
				if (val > 0 && val != original) {
					return val;
				}
			} else {
				map[i][j] = ROCK;
				long val = findColSym(map);
				if (val == 0 || val == original) {
					val = findRowSym(map);
				}
				map[i][j] = ASH;
				if (val > 0 && val != original) {
					return val;
				}
			}
		}
	}

	return 0;
}

void part2(const std::vector<map_t>& maps) {
	std::cout << "WARNING: Not working...\n";
	long total = 0;
	for (auto map : maps) {
		long val = fix(map);
		total += val;
	}

	std::cout << "Total: " << total << "\n";
}

int main(int argc, char *argv[]) { 
    std::cout << "Welcome to day 13!\n";
    std::vector<char> data = Common::ReadFile(argv[1]);

    auto maps = Parse(data);

#ifdef PART1 
    part1(maps);
#endif

#ifdef PART2
    part2(maps);
#endif

    return 0; 
}
