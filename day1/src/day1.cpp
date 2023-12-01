#include "common/common.h"

#include <cstdio>
#include <iostream>

bool checkWord(std::vector<char>& buffer, int& start, const char * word, int wordLength) {
	if (start + wordLength >= buffer.size()) {
		return false;
	} 

	for (int i = 0; i < wordLength; i++) {
		if (buffer[start + i] != word[i]) {
			return false;
		}
	}

	return true;
}

std::vector<int> CollectCalibrationValuesPart2(std::vector<char>& input) {
	std::vector<int> results;
	std::string digits = "";

	int current = 0;

	while (current < input.size()) {
		char ch = input[current];

		if (ch == '\n') {
			std::string value = "";
			value += digits[0];
			value += digits[digits.size() - 1];

			results.push_back(std::stoi(value));
			digits = "";
		} else if (ch >= '0' && ch <= '9') {
			digits += ch;
		} else if (checkWord(input, current, "one", 3)) {
			digits += '1';
		} else if (checkWord(input, current, "two", 3)) {
			digits += '2';
		} else if (checkWord(input, current, "three", 5)) {
			digits += '3';
		} else if (checkWord(input, current, "four", 4)) {
			digits += '4';
		} else if (checkWord(input, current, "five", 4)) {
			digits += '5';
		} else if (checkWord(input, current, "six", 3)) {
			digits += '6';
		} else if (checkWord(input, current, "seven", 5)) {
			digits += '7';
		} else if (checkWord(input, current, "eight", 5)) {
			digits += '8';
		} else if (checkWord(input, current, "nine", 4)) {
			digits += '9';
		}

		current++;
	}

	return results;
}

std::vector<int> CollectCalibrationValuesPart1(std::vector<char>& input) {
	std::vector<int> results;
	std::string digits = "";

	for (auto ch : input) {
		if (ch == '\n') {
			std::string value = "";
			value += digits[0];
			value += digits[digits.size() - 1];
		
			results.push_back(std::stoi(value));
			digits = "";
		} else if (ch >= '0' && ch <= '9') {
			digits += ch;
		}
	}

	return results;
}

int main(int argc, char *argv[]) { 
	std::vector<char> input = Common::ReadFile(argv[1]);

	std::vector<int> values = CollectCalibrationValuesPart2(input);

	int total = 0;
	for (auto value : values) {
		total += value;
	}

	std::cout << total << std::endl;

    return 0; 
}
