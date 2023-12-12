#include "common/common.h"

#include <ios>
#include <iostream>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <thread>

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

void parseSprings(const std::vector<char>& data, int& current, int line, std::string* states) {
	while (isState(data[current])) {
		states->push_back(data[current]);
		current++;
	}
}

struct SpringData {
	std::string states;
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

// TODO: cache the parameters of each iteration...
int isValid(const std::string& states, const std::vector<int>& summary, std::unordered_map<std::string, int>& cache, int n) {
	if (cache.find(states) != cache.end()) {
		return cache[states];
	}

	std::string subStr = states.substr(0, n);
	if (cache.find(subStr) != cache.end()) {
		int cached = cache[subStr];
		if (cached < 0) {
			cache[states.substr(0, n + 1)] = -1;
			cache[states] = -1;
			return -1;
		}
	}

	int state_idx = 0;
	int summary_idx = 0;

	int current_count = summary[summary_idx];
	while(state_idx < states.size()) {
		if (current_count < 0) {
			cache[states.substr(0, state_idx + 1)] = -1;
			cache[states] = -1;
			return -1;
		}

		if (states[state_idx] == '?') {
			cache[states.substr(0, state_idx + 1)] = state_idx;
			cache[states] = state_idx;
			return state_idx;
		}

		if (states[state_idx] == '.') {
			if (summary_idx < summary.size() && current_count == 0) {
				summary_idx++;
				if (summary_idx < summary.size()) {
					current_count = summary[summary_idx];
				}
			} else if (summary_idx < summary.size() && current_count != summary[summary_idx]) {
				cache[states.substr(0, state_idx + 1)] = -1;
				cache[states] = -1;
				return -1;
			}
		}

		if (states[state_idx] == '#') {
			if (summary_idx == summary.size()) {
				cache[states.substr(0, state_idx + 1)] = -1;
				cache[states] = -1;
				return -1;
			}
			current_count--;
		}
			
		state_idx++;
	}
			
	if (summary_idx < summary.size() && current_count == 0) {
		summary_idx++;
	}

	if (summary_idx != summary.size() || state_idx != states.size()) {
		cache[states.substr(0, state_idx + 1)] = -1;
		cache[states] = -1;
		return -1;
	}

	// cache[subStr] = n;
	cache[states] = states.size();
	return states.size();
}

long process(const SpringData& data) {
	std::stack<std::pair<int, char>> currentIndex;
	std::string collapsedState(data.states.begin(), data.states.end());
	std::unordered_map<std::string, int> cache;

	long count = 0;

	int i = 0;
	while (i < data.states.size() && data.states[i] != '?') {
		i++;
	}
	if (i < data.states.size()) {
		currentIndex.push({ i, '#'});
		currentIndex.push({ i, '.'});
	}

	std::pair<int, char> current;
	while (!currentIndex.empty()) {
		current = currentIndex.top();
		currentIndex.pop();

		collapsedState[current.first] = current.second;

		int valid = isValid(collapsedState, data.summary, cache, current.first);

		// std::cout << collapsedState << " " << current.first;
		if (valid < 0) {
			// std::cout << "\tINVALID\n";
			if (!currentIndex.empty()) {
				for (int i = currentIndex.top().first; i < current.first; i++) {
					collapsedState[i] = data.states[i];
				}
			}
			collapsedState[current.first] = data.states[current.first];
			continue;
		} else if (valid == collapsedState.size()) {
			// std::cout << "\tVALID\n";
			if (!currentIndex.empty()) {
				for (int i = currentIndex.top().first; i < current.first; i++) {
					collapsedState[i] = data.states[i];
				}
			}
			collapsedState[current.first] = data.states[current.first];
			continue;
		}

		// std::cout << std::endl;

		int nextIndex = current.first + 1;
		if (nextIndex < collapsedState.size()) {
			while (nextIndex < collapsedState.size() && collapsedState[nextIndex] != '?') {
				nextIndex++;
			}

			if (nextIndex < collapsedState.size()) {
				currentIndex.push({ nextIndex, '#'});
				currentIndex.push({ nextIndex, '.'});
			}
		}
	}

	for (auto e : cache) {
		if (e.second == collapsedState.size()) {
			count++;
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

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < summary_len; j++) {
			data.summary.push_back(data.summary[j]);
		}

		data.states.push_back('?');
		for (int j = 0; j < state_len; j++) {
			data.states.push_back(data.states[j]);
		}
	}
}


void part2(const std::vector<SpringData>& data) {
	std::cout << "WARNING, SLOW: This solution does not complete...\n";
	long total = 0;
	std::vector<std::thread> threads;

	for (int i = 0; i < 8; i++) {
		threads.push_back(std::thread([&data, &total, i] {
			for (int j = i; j < data.size(); j += 8) {
				auto spring = data[j];
				expand(spring);
				long c = process(spring);
				total += c;
				std::cout << j << "\t" << total << "\t" << c << "\n";
			}
		}));
	}

	for (auto& t : threads) {
		t.join();
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
