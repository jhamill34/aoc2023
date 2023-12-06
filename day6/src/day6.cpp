#include "common/common.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

struct RaceDefs {
	std::vector<long> times;
	std::vector<long> distances;
};

bool isAlpha(char ch) {
	return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
}

bool isNumeric(char ch) {
	return ch >= '0' && ch <= '9';
}

bool isWhitespace(char ch) {
	return ch == ' ' || ch == '\t';
}

std::string parseIdentifier(std::vector<char>& input, int& current) {
	std::string identifier = "";

	while(isAlpha(input[current])) {
		identifier += input[current];
		current++;
	}

	return identifier;
}

void consumeSpace(std::vector<char>& input, int& current) {
	while (isWhitespace(input[current])) {
		current++;
	}
}

void match(std::vector<char>& input, int& current, int line, char ch) {
	if (input[current] == ch) {
		current++;
		return;
	}

	std::cout << "Expected '" << ch << "' at position " << current << " line " << line << "\n";
	exit(1);
}

long parseNumber(std::vector<char>& input, int& current) {
	std::string digits = "";

	while (isNumeric(input[current])) {
		digits += input[current];
		current++;
	}

	return std::stol(digits);
}

void parseNumberList(std::vector<char>& input, int& current, std::vector<long>* numbers) {
	if (numbers == nullptr) {
		std::cout << "Null number container...\n";
		exit(1);
	}

	while (isNumeric(input[current])) {
		numbers->push_back(parseNumber(input, current));
		consumeSpace(input, current);
	}
}

void consumeNewlines(std::vector<char>& input, int& current, int& line) {
	consumeSpace(input, current);

	while (input[current] == '\n') {
		current++;
		line++;

		consumeSpace(input, current);
	}
}

void matchKeyword(std::vector<char>& input, int& current, int& line, const char* keyword) {
	int start = current;
	std::string word = parseIdentifier(input, current);

	if (word != keyword) {
		std::cout << "Expected \"" << keyword << "\" keyword at position " << start << " line " << line << "\n";
		exit(1);
	}
}

void ParseTimes(std::vector<char>& input, int& current, int& line, std::vector<long>* numbers) {
	matchKeyword(input, current, line, "Time");
	match(input, current, line, ':');
	consumeSpace(input, current);
	parseNumberList(input, current, numbers);
}

void ParseDistance(std::vector<char>& input, int& current, int& line, std::vector<long>* numbers) {
	matchKeyword(input, current, line, "Distance");
	match(input, current, line, ':');
	consumeSpace(input, current);
	parseNumberList(input, current, numbers);
}

RaceDefs Parse(std::vector<char>& input) {
	int current = 0;
	int line = 1;

	RaceDefs races;

	ParseTimes(input, current, line, &races.times);
	consumeNewlines(input, current, line);
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
