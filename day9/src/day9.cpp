#include "common/common.h"

#include <iostream>

std::vector<std::vector<long>> Parse(std::vector<char>& input) {
	int current = 0;
	int line = 1;

	std::vector<std::vector<long>> result;

	while(current < input.size()) {
		std::vector<long> numbers;
		Common::parseNumberList(input, current, &numbers);
		Common::consumeNewlines(input, current, line);

		result.push_back(numbers);
	}

	return result;
}

long part1Line(std::vector<long>& line) {
	std::vector<std::vector<long>> opt;
	opt.push_back(line);

	for (int i = 0; i < line.size(); i++) {
		std::vector<long> current = *(opt.end() - 1);
		std::vector<long> diffs;
		for (int j = 1; j < current.size(); j++) {
			diffs.push_back(current[j] - current[j - 1]);
		}

		if (diffs.size() > 0) {
			opt.push_back(diffs);
		}
	}

	long total = 0;
	for (auto o : opt) {
		total += *(o.end() - 1);
	}

	return total;
}

void part1(std::vector<std::vector<long>>& input) {
	long total = 0;
	for (auto line : input) {
		total += part1Line(line);
	}

	std::cout << "Total: " << total << "\n";
}

long part2Line(std::vector<long>& line) {
	std::vector<std::vector<long>> opt;
	opt.push_back(line);

	for (int i = 0; i < line.size(); i++) {
		std::vector<long> current = *(opt.end() - 1);
		std::vector<long> diffs;
		for (int j = 1; j < current.size(); j++) {
			diffs.push_back(current[j] - current[j - 1]);
		}

		if (diffs.size() > 0) {
			opt.push_back(diffs);
		}
	}

	long total = 0;
	for (int i = opt.size() - 1; i >= 0; i--) {
		total = *(opt[i].begin()) - total;
	}

	return total;
}


void part2(std::vector<std::vector<long>>& input) {
	long total = 0;
	for (auto line : input) {
		total += part2Line(line);
	}

	std::cout << "Total: " << total << "\n";
}

int main(int argc, char *argv[]) { 
	std::vector<char> input = Common::ReadFile(argv[1]);

	auto result = Parse(input);

	// part1(result);
	part2(result);

    return 0; 
}
