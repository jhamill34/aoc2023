#include "common.h"

#include <fstream>
#include <iostream>

namespace Common {
	std::vector<char> ReadFile(const char *filename) {
		std::ifstream file(filename);

		std::istreambuf_iterator<char> start(file);
		std::istreambuf_iterator<char> end;

		std::vector<char> buffer(start, end);

		return buffer;
	}

	bool isAlpha(char ch) {
		return ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z';
	}

	bool isNumeric(char ch) {
		return ch >= '0' && ch <= '9';
	}

	bool isWhitespace(char ch) {
		return ch == ' ' || ch == '\t';
	}

	std::string parseIdentifier(std::vector<char>& input, int& current, bool includeDigits) {
		std::string identifier = "";

		while(isAlpha(input[current]) || (includeDigits && isNumeric(input[current]))) {
			identifier += input[current];
			current++;
		}

		return identifier;
	}

	void consumeSpace(const std::vector<char>& input, int& current) {
		while (isWhitespace(input[current])) {
			current++;
		}
	}

	void match(const std::vector<char>& input, int& current, int line, const char ch) {
		if (input[current] == ch) {
			current++;
			return;
		}

		std::cout << "Expected '" << ch << "' at position " << current << " line " << line << "\n";
		exit(1);
	}

	long parseNumber(const std::vector<char>& input, int& current) {
		std::string digits = "";
		bool isNegative = false;

		if (input[current] == '-') {
			isNegative = true;
			current++;
		}

		while (isNumeric(input[current])) {
			digits += input[current];
			current++;
		}

		if (isNegative) {
			return -std::stol(digits);
		} else {
			return std::stol(digits);
		}
	}

	void parseNumberList(std::vector<char>& input, int& current, std::vector<long>* numbers) {
		if (numbers == nullptr) {
			std::cout << "Null number container...\n";
			exit(1);
		}

		while (isNumeric(input[current]) || input[current] == '-') {
			numbers->push_back(parseNumber(input, current));
			consumeSpace(input, current);
		}
	}

	void consumeNewlines(const std::vector<char>& input, int& current, int& line) {
		consumeSpace(input, current);

		while (input[current] == '\n') {
			current++;
			line++;

			consumeSpace(input, current);
		}
	}

	void matchKeyword(std::vector<char>& input, int& current, int& line, const char* keyword) {
		int start = current;
		std::string word = parseIdentifier(input, current, false);

		if (word != keyword) {
			std::cout << "Expected \"" << keyword << "\" keyword at position " << start << " line " << line << "\n";
			exit(1);
		}
	}
}

