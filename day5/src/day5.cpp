#include "common/common.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ratio>
#include <set>

struct SourceDestRange {
	long source;
	long dest;
	long range;
};

struct SourceDestMap {
	std::string name;
	std::vector<SourceDestRange> ranges;
};

struct Farm {
	std::vector<long> seeds;
	std::map<std::string, SourceDestMap> maps;
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

void ParseSeeds(std::vector<char>& input, int& current, int& line, std::vector<long>* seeds) {
	matchKeyword(input, current, line, "seeds");
	match(input, current, line,  ':');
		
	consumeSpace(input, current);
	parseNumberList(input, current, seeds);
	consumeNewlines(input, current, line);
}

SourceDestRange ParseRange(std::vector<char>& input, int& current, int& line) {
	SourceDestRange range;

	std::vector<long> values;
	parseNumberList(input, current, &values);

	if (values.size() != 3) {
		std::cout << "Not enough numbers on line " << line << "\n";
		exit(1);
	}

	range.dest = values[0];
	range.source = values[1];
	range.range = values[2];

	return range;
}

void ParseMapInto(std::vector<char>& input, int& current, int& line, std::map<std::string, SourceDestMap>& map) {
	SourceDestMap destMap;

	std::string source = parseIdentifier(input, current);
	match(input, current, line, '-');
	matchKeyword(input, current, line, "to");
	match(input, current, line, '-');

	destMap.name = parseIdentifier(input, current);
	consumeSpace(input, current);
	matchKeyword(input, current, line, "map");
	match(input, current, line, ':');
	consumeNewlines(input, current, line);

	while(isNumeric(input[current])) {
		destMap.ranges.push_back(ParseRange(input, current, line));
		consumeNewlines(input, current, line);
	}

	map[source] = destMap;
}

Farm Parse(std::vector<char>& input) {
	int current = 0;
	int line = 1;

	Farm farm;

	ParseSeeds(input, current, line, &farm.seeds);
	while (current < input.size()) {
		ParseMapInto(input, current, line, farm.maps);
	}

	return farm;
}

long lookup(long source, SourceDestMap map) {
	for (auto range : map.ranges) {
		if (source >= range.source && source < range.source + range.range) {
			return (source - range.source) + range.dest;
		}
	}

	return source;
}

long walk(long source, std::map<std::string, SourceDestMap>& maps) {
	std::string current = "seed";
	long currentValue = source;
	while (maps.find(current) != maps.end()) {
		currentValue = lookup(currentValue, maps[current]);
		current = maps[current].name;
	}

	return currentValue;
}

void part1(Farm farm) {
	long min = -1;

	for (auto seed : farm.seeds) {
		long currentValue = walk(seed, farm.maps);

		if (min < 0 || currentValue < min) {
			min = currentValue;
		}
	}

	std::cout << "Smallest: " << min << std::endl;
}

void part2(Farm farm) {
	long min = -1;

	auto iter = farm.seeds.begin();

	while (iter != farm.seeds.end()) {
		long start = *iter;
		long end = start + *(iter + 1);

		long previous = -1;
		for (long i = end - 1; i >=  start; i--) {
			long currentValue = walk(i, farm.maps);

			if (min < 0 || currentValue < min) {
				min = currentValue;
			}

			previous = currentValue;
		}

		iter += 2;
	}
	
	std::cout << "Smallest: " << min << std::endl;
}


int main(int argc, char *argv[]) { 
	std::vector<char> data = Common::ReadFile(argv[1]);
	auto farm = Parse(data);
	// part1(farm);
	part2(farm);

    return 0; 
}
