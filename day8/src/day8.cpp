#include "common/common.h"

#include <iostream>
#include <map>

const char* START_NODE = "AAA";
const char* END_NODE = "ZZZ";

enum Direction {
	Left,
	Right,
};

struct CamelPouch {
	std::vector<Direction> steps;
	std::map<std::string, std::vector<std::string>> graph;
};

void parseSteps(std::vector<char>& input, int& current, std::vector<Direction>* steps) {
	while (input[current] != '\n') {
		if (input[current] == 'L') {
			steps->push_back(Direction::Left);
		} else if (input[current] == 'R') {
			steps->push_back(Direction::Right);
		} else {
			std::cout << "Expected 'L' or 'R' on steps line at position " << current << "\n";
			exit(1);
		}

		current++;
	}
}

void parseNode(
		std::vector<char>& input,
		int& current,
		int& line,
		std::map<std::string, std::vector<std::string>>* graph
) {
	// We're going to assume that there are no duplicates on the 
	// left side of the equals sign...
	std::string node, left, right;

	node = Common::parseIdentifier(input, current, true);

	Common::consumeSpace(input, current);
	Common::match(input, current, line, '=');
	Common::consumeSpace(input, current);
	Common::match(input, current, line, '(');
	Common::consumeSpace(input, current);

	left = Common::parseIdentifier(input, current, true);

	Common::consumeSpace(input, current);
	Common::match(input, current, line, ',');
	Common::consumeSpace(input, current);

	right = Common::parseIdentifier(input, current, true);

	Common::consumeSpace(input, current);
	Common::match(input, current, line, ')');

	std::vector<std::string> children = { left, right };
	graph->insert_or_assign(node, children);
}

CamelPouch Parse(std::vector<char>& input) {
	int current = 0;
	int line = 1;

	CamelPouch pouch;

	parseSteps(input, current, &pouch.steps);

	Common::consumeNewlines(input, current, line);

	while (current < input.size()) {
		parseNode(input, current, line, &pouch.graph);
		Common::consumeNewlines(input, current, line);
	}

	return pouch;
}

void step(CamelPouch& pouch, int i, std::string* node) {
	Direction d = pouch.steps[i];

	switch (d) {
		case Direction::Left:
			// std::cout << "Step to the LEFT\n";
			*node = pouch.graph[*node][0];
			break;
		
		case Direction::Right:
			// std::cout << "Step to the RIGHT\n";
			*node = pouch.graph[*node][1];
			break;
			
		default:
			std::cout << "Unexpected direction...\n";
			exit(1);
	}
}

void part1(CamelPouch pouch) {
	int counter = 0;
	std::string current = START_NODE;

	int i = 0;
	while (current != END_NODE) {
		step(pouch, i, &current);
		counter++;
		i = (i + 1) % pouch.steps.size();
	}

	std::cout << "Total Steps: " << counter << "\n";
}

bool areAllDone(std::vector<std::string>& nodes) {
	for (auto node : nodes) {
		if (*(node.end() - 1) != 'Z') {
			return false;
		}
	}

	return true;
}

void part2(CamelPouch pouch) {
	// TODO: Something to do with LCM and loop sizes....
}


int main(int argc, char *argv[]) { 
	std::vector<char> input = Common::ReadFile(argv[1]);
	auto pouch = Parse(input);

	// part1(pouch);	
	part2(pouch);	

    return 0; 
}
