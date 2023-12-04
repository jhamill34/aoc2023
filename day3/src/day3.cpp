#include "common/common.h"
#include <iostream>
#include <string>

struct Position {
	int x;
	int y;
};

struct Symbol {
	char sym;
	Position pos;
};

struct PartNumber {
	Position start;
	Position end;
	int value;
};

struct Engine {
	std::vector<Symbol> symbols;
	std::vector<PartNumber> parts;
};

PartNumber parseNumber(std::vector<char>& input, int &current, int& x, int y) {
	int startX = x;
	int start = current;

	std::string digits = "";

	while (input[current] >= '0' && input[current] <= '9') {
		digits += input[current];
		current++;
		x++;
	}

	int number = std::stoi(digits);

	return { { startX, y }, { x, y + 1 }, number };
}

void consumeSpace(std::vector<char>& input, int& current, int& x) {
	while (input[current] == '.') {
		current++;
		x++;
	}
}

Engine Parse(std::vector<char>& input) {
	int current = 0;
	int x = 0;
	int y = 0;

	Engine engine;

	while (current < input.size()) {
		char ch = input[current];

		if (ch == '.') {
			consumeSpace(input, current, x);
		} else if (ch == '\n') {
			x = 0;
			y++;
			current++;
		} else if (ch >= '0' && ch <= '9') {
			engine.parts.push_back(parseNumber(input, current, x, y));
		} else {
			engine.symbols.push_back({ ch, { x, y }});

			current++;
			x++;
		}
	}

	return engine;
}

bool isAdjacent(PartNumber& part, Position sym) {
	// part.start.y <= sym.y && sym.y < part.end.y
	if (part.start.y - 1 > sym.y || sym.y >= part.end.y + 1) {
		return false;
	}

	if (part.start.x - 1 > sym.x || sym.x >= part.end.x + 1) {
		return false;
	}

	return true;
}

bool isValidPart(PartNumber& part, std::vector<Symbol>& symbols) {
	for (auto s : symbols) {
		if (isAdjacent(part, s.pos)) {
			return true;
		}
	}

	return false;
}

void part1(Engine& engine) {
	int total = 0;
	for (auto part : engine.parts) {
		if (isValidPart(part, engine.symbols)) {
			total += part.value;
		}
	}

	std::cout << "Total: " << total << std::endl;
}

void part2(Engine& engine) {
	int total = 0;

	for (auto sym : engine.symbols) {
		if (sym.sym == '*') {
			int adj = 1;
			int adjCount = 0;
			for (auto part : engine.parts) {
				if (isAdjacent(part, sym.pos)) {
					adjCount++;

					if (adjCount > 2) {
						break;
					}

					adj *= part.value;
				}
			}

			if (adjCount == 2) {
				total += adj;
			}
		}
	}

	std::cout << "Total: " << total << std::endl;
}

int main(int argc, char *argv[]) { 
	std::vector<char> data = Common::ReadFile(argv[1]);

	auto engine = Parse(data);

	// part1(engine);
	part2(engine);

    return 0; 
}
