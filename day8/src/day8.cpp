#include "common/common.h"

#include <iostream>
#include <map>
#include <numeric>

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

bool allVisited(std::map<std::string, bool>& visited) {
	if (visited.size() == 0) {
		return false;
	}

	for (auto e : visited) {
		if (!e.second) {
			return false;
		}
	}

	return true;
}

void part2(CamelPouch pouch) {
	std::vector<std::string> startNodes;
	std::vector<int> loopSizes;

	for (auto e : pouch.graph) {
		if (*(e.first.end() - 1) == 'A') {
			startNodes.push_back(e.first);
		}
	}

	for (auto node : startNodes) {
		int count = 0;
		int i = 0; 
		std::string current = node;
		std::map<std::string, bool> visited;
		std::map<std::string, int> distances;

		while(!allVisited(visited)) {
			step(pouch, i, &current);
			count++;
			if (*(current.end() - 1) == 'Z') {
				if (visited.find(current) == visited.end()) {
					visited[current] = false;
				} else {
					visited[current] = true;
				}
			}

			if (distances[current] == 0) {
				distances[current] = count;
			}

			i = (i + 1) % pouch.steps.size();
		}

		// Some assertions of the assumptions to be able to use LCM
		if (visited.size() != 1) {
			std::cout << "End nodes should be unique for each start " << node << "\n";
			exit(1);
		}

		int startToEnd = distances[current];
		int loopLength = count - startToEnd;

		if (startToEnd != loopLength) {
			std::cout << "Expected the distance from start to end to be equal to loop length: " << node << "\n";
			std::cout << "count: " << count << "\n";
			std::cout << "startToEnd: " << startToEnd << "\n";
			std::cout << "loopLength: " << loopLength << "\n";
			exit(1);
		}

		loopSizes.push_back(loopLength);
	}


	// At this point we know our assertions for each starting node will be true. 
	// LCM only works if we can assume that the distance to the single end node is 
	// equal to a loop length effectively being the same thing. Now we model 
	// pure loops and treat this as the following classic math problem:
	// "Train A is on a track of length X and Train B is on a track of length Y traveling at the 
	// same speed both on a loop track. 
	//
	// How long will it take for both to reach their destinations at the same time?
	//
	// Answer: LCM(X, Y) * speeds"
	long lcm = loopSizes[0];
	for (int i = 1; i < loopSizes.size(); i++) {
		lcm = std::lcm(lcm, loopSizes[i]);
	}

	std::cout << "LCM: " << lcm << "\n";
}

int main(int argc, char *argv[]) { 
	std::vector<char> input = Common::ReadFile(argv[1]);
	auto pouch = Parse(input);

	// part1(pouch);	
	part2(pouch);	

    return 0; 
}
