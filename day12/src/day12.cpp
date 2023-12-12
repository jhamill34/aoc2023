#include "common/common.h"

#include <ios>
#include <iostream>
#include <sstream>
#include <stack>
#include <set>
#include <unordered_set>

enum State {
	UNKNOWN,
	OPERATIONAL,
	DAMAGED,
};

std::ostream& operator<<(std::ostream& os, const State& state) {
	switch (state) {
		case UNKNOWN:
			os << "?";
			break;
		case OPERATIONAL:
			os << ".";
			break;
		case DAMAGED:
			os << "#";
			break;
		default:
			throw std::runtime_error("Unknown state");
	}

	return os;
}

void parseNumbers(const std::vector<char>& data, int& current, int line, std::vector<int>* numbers) {
	while (Common::isNumeric(data[current])) {
		numbers->push_back(Common::parseNumber(data, current));
		if (data[current] == ',') {
			current++;
		}
	}
}

bool isState(const char ch) {
	return ch == '#' || ch == '.' || ch == '?';
}

void parseSprings(const std::vector<char>& data, int& current, int line, std::vector<State>* states) {
	while (isState(data[current])) {
		switch (data[current]) {
			case '#':
				states->push_back(State::DAMAGED);
				break;
			case '.':
				states->push_back(State::OPERATIONAL);
				break;
			case '?':
				states->push_back(State::UNKNOWN);
				break;
			default:
				std::cout << "Unknown character " << data[current] << " on line " << line << "\n";
				exit(1);
		}

		current++;
	}
}

struct SpringData {
	std::vector<State> states;
	std::vector<int> summary;
};

std::vector<SpringData> Parse(const std::vector<char>& data) {
	int current = 0, line = 1;
	std::vector<SpringData> springs;

	while (current < data.size()) {
		SpringData spring;
		parseSprings(data, current, line, &spring.states);
		Common::consumeSpace(data, current);
		parseNumbers(data, current, line, &spring.summary);
		Common::consumeNewlines(data, current, line);

		springs.push_back(spring);
	}

	return springs;
}

void display(const std::vector<State>& states) {
	for (auto state : states) {
		std::cout << state;
	}
}

std::string statesToString(const std::vector<State>& states, int n) {
	std::ostringstream builder;
	for (int i = 0; i < n; i++) {
		builder << states[i];
	}

	return builder.str();
}

bool isValid(const std::vector<State>& states, const std::vector<int>& summary) {
	int state_idx = 0;
	int summary_idx = 0;

	int current_count = summary[summary_idx];
	while(state_idx < states.size()) {
		if (current_count < 0) {
			return false;
		}

		if (states[state_idx] == State::UNKNOWN) {
			return false;
		}

		if (states[state_idx] == State::OPERATIONAL) {
			if (summary_idx < summary.size() && current_count == 0) {
				summary_idx++;
				if (summary_idx < summary.size()) {
					current_count = summary[summary_idx];
				}
			} else if (summary_idx < summary.size() && current_count != summary[summary_idx]) {
				return false;
			}
		}

		if (states[state_idx] == State::DAMAGED) {
			if (summary_idx == summary.size()) {
				return false;
			}
			current_count--;
		}
			
		state_idx++;
	}
			
	if (summary_idx < summary.size() && current_count == 0) {
		summary_idx++;
	}

	if (summary_idx != summary.size() || state_idx != states.size()) {
		return false;
	}

	return true;
}

long process(const SpringData& data) {
	std::stack<std::pair<int, State>> currentIndex;
	std::vector<State> collapsedState;
	collapsedState.resize(data.states.size());

	long count = 0;

	switch (data.states[0]) {
		case UNKNOWN:
			currentIndex.push({ 0, State::DAMAGED });
			currentIndex.push({ 0, State::OPERATIONAL });
			break;
		case DAMAGED:
			currentIndex.push({ 0, State::DAMAGED });
			break;
		case OPERATIONAL:
			currentIndex.push({ 0, State::OPERATIONAL });
			break;
	}

	std::pair<int, State> current;
	while (!currentIndex.empty()) {
		current = currentIndex.top();
		currentIndex.pop();


		collapsedState[current.first] = current.second;

		int nextIndex = current.first + 1;

		if (nextIndex == collapsedState.size()) {
			if (isValid(collapsedState, data.summary)) {
				// display(collapsedState);
				// std::cout << std::endl;
				count++;
			}
		} else {
			switch (data.states[nextIndex]) {
				case UNKNOWN:
					currentIndex.push({ nextIndex, State::DAMAGED });
					currentIndex.push({ nextIndex, State::OPERATIONAL });
					break;
				case DAMAGED:
					currentIndex.push({ nextIndex, State::DAMAGED });
					break;
				case OPERATIONAL:
					currentIndex.push({ nextIndex, State::OPERATIONAL });
					break;
			}
		}
	}

	return count;
}

void part1(const std::vector<SpringData>& data) {
	long total = 0;
	for (auto spring : data) {
		long c = process(spring);
		total += c;
	}

	std::cout << "Total: " << total << "\n";
}

void expand(SpringData& data) {
	int summary_len = data.summary.size();
	int state_len = data.states.size();

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < summary_len; j++) {
			data.summary.push_back(data.summary[j]);
		}

		data.states.push_back(State::UNKNOWN);
		for (int j = 0; j < state_len; j++) {
			data.states.push_back(data.states[j]);
		}
	}
}

void part2(const std::vector<SpringData>& data) {
	std::cout << "WARNING, SLOW: This solution does not complete...\n";
	long total = 0;
	for (auto spring : data) {
		expand(spring);
		long c = process(spring);
		std::cout << c << std::endl;
		total += c;
	}

	std::cout << "Total: " << total << "\n";
}

int main(int argc, char *argv[]) { 
	std::vector<char> input = Common::ReadFile(argv[1]);

	auto springs = Parse(input);

#ifdef PART1
	part1(springs);
#endif
#ifdef PART2
	part2(springs);
#endif

    return 0; 
}
