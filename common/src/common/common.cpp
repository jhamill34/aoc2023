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
}

