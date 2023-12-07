#include "common/common.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

struct RaceDefs {
	std::vector<long> times;
	std::vector<long> distances;
};

void ParseTimes(std::vector<char>& input, int& current, int& line, std::vector<long>* numbers) {
	Common::matchKeyword(input, current, line, "Time");
	Common::match(input, current, line, ':');
	Common::consumeSpace(input, current);
	Common::parseNumberList(input, current, numbers);
}

void ParseDistance(std::vector<char>& input, int& current, int& line, std::vector<long>* numbers) {
	Common::matchKeyword(input, current, line, "Distance");
	Common::match(input, current, line, ':');
	Common::consumeSpace(input, current);
	Common::parseNumberList(input, current, numbers);
}

RaceDefs Parse(std::vector<char>& input) {
	int current = 0;
	int line = 1;

	RaceDefs races;

	ParseTimes(input, current, line, &races.times);
	Common::consumeNewlines(input, current, line);
	ParseDistance(input, current, line, &races.distances);

	return races;
}

long quadraticFormula(long t, long d) {
	double front = t / 2.0;
	double back = std::sqrt(t * t - 4.0 * (d + 1)) / 2.0;

	long left = (long)std::ceil(front - back);
	long right = (long)std::floor(front + back);

	return right - left + 1;
}

void part1(RaceDefs& race) {
	long result = 1;
	long val;

	for (int i = 0; i < race.distances.size(); i++) {
		val = quadraticFormula(race.times[i], race.distances[i]);
		std::cout << val << "\n";
		result *= val;
	}

	std::cout << "Result: " << result << "\n";
}

void part2(RaceDefs& race) {
	long result = 1;
	long val;

	std::ostringstream timeDigits;
	std::ostringstream distanceDigits;

	for (int i = 0; i < race.distances.size(); i++) {
		timeDigits << race.times[i];
		distanceDigits << race.distances[i];
	}

	long time = std::stol(timeDigits.str());
	long distance = std::stol(distanceDigits.str());

	result = quadraticFormula(time, distance);

	std::cout << "Result: " << result << "\n";
}

int main(int argc, char *argv[]) { 
	std::vector<char> input = Common::ReadFile(argv[1]);

	auto raceDefs = Parse(input);

	// part1(raceDefs);
	part2(raceDefs);

    return 0; 
}
