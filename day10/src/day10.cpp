#include "common/common.h"

#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <sstream>
#include <valarray>

struct Node {
	std::string id;
	int x;
	int y;
};

long operator*(const Node& l, const Node& r) {
	return l.x * r.y - r.x * l.y;
}

bool operator==(const Node& l, const Node& r) {
	return l.id == r.id;
}

bool operator<(const Node& l, const Node& r) {
	return l.id < r.id;
}

Node makeNode(int x, int y) {
	std::ostringstream builder;
	builder << x << "," << y;
	return { builder.str(), x, y };
}

typedef std::map<Node, std::set<Node>> graph_t;

struct Maze {
	graph_t graph;
	Node start;
};

Maze Parse(const std::vector<char>&input) {
	int current = 0, line = 0, column = -1;

	Maze maze;
	std::set<Node> children;
	while (current < input.size()) {
		column++;

		Node node = makeNode(column, line);
		bool skip = false;
		switch (input[current]) {
			case '\n':
				line++;
				column = -1;
				skip = true;
				break;
			case 'S':
				maze.start = node;
				break;
			case '.':
				skip = true;
				break;
			case '|':
				children = { makeNode(column, line - 1), makeNode(column, line + 1) };
				break;
			case '-':
				children = { makeNode(column - 1, line), makeNode(column + 1, line) };
				break;
			case 'L':
				children = { makeNode(column, line - 1), makeNode(column + 1, line) };
				break;
			case 'J':
				children = { makeNode(column, line - 1), makeNode(column - 1, line) };
				break;
			case '7':
				children = { makeNode(column, line + 1), makeNode(column - 1, line) };
				break;
			case 'F':
				children = { makeNode(column, line + 1), makeNode(column + 1, line) };
				break;
			default:
				std::cout << "Unknown character\n";
				exit(1);
		}

		if (!skip) {
			maze.graph[node] = children;
			children.clear();
		}
		
		current++;
	}

	std::set<Node> startChildren;
	for (auto nodes : maze.graph) {
		if (nodes.second.find(maze.start) != nodes.second.end()) {
			startChildren.insert(nodes.first);
		}
	}

	maze.graph[maze.start] = startChildren;

	return maze;
}

const char *MARKER = "---";
const Node MARKER_NODE = { MARKER, -1, -1 };

void part1(const Maze& maze) {
	std::queue<Node> q;
	std::set<Node> seen;

	q.push(maze.start);
	q.push(MARKER_NODE);

	Node current;

	int count = 0;
	while (!q.empty()) {
		current = q.front();
		if (current == MARKER_NODE) {
			count++;
			q.pop();
			if (!q.empty()) {
				q.push(MARKER_NODE);
			}
			continue;
		}

		if (seen.find(current) != seen.end()) {
			q.pop();
			continue;
		}
		
		std::cout << current.id << "\t" << count << std::endl;

		seen.insert(current);

		for (auto child : maze.graph.at(current)) {
			if (seen.find(child) == seen.end()) {
				q.push(child);
			}
		}

		q.pop();
	}
}

void part2(const Maze& maze) {
	// I cheated on this part and looked up the formulas for this. 
	// https://en.wikipedia.org/wiki/Shoelace_formula
	// https://en.wikipedia.org/wiki/Pick%27s_theorem
	std::stack<Node> q;
	std::set<Node> seen;

	q.push(maze.start);

	Node current;
	std::vector<Node> verticies;

	int count = 0;
	while (!q.empty()) {
		current = q.top();
		q.pop();

		if (seen.find(current) != seen.end()) {
			continue;
		}
		
		verticies.push_back(current);

		seen.insert(current);

		for (auto child : maze.graph.at(current)) {
			if (seen.find(child) == seen.end()) {
				q.push(child);
			}
		}

	}

	long area = 0;
	for (int i = 1; i < verticies.size(); i++) {
		area += verticies[i - 1] * verticies[i];
	}

	area += verticies[verticies.size() - 1] * verticies[0];
	area /= 2;

	area = std::abs(area);

	std::cout << "A = " << area << std::endl;
	std::cout << "b = " << verticies.size() << std::endl;

	int total = area - (verticies.size() / 2) + 1;
	std::cout << "i = " << total << std::endl;
}


int main(int argc, char *argv[]) { 
	std::vector<char> input = Common::ReadFile(argv[1]);
	auto maze = Parse(input);

	// part1(maze);
	part2(maze);
	
    return 0; 
}
