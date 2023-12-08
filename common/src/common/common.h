#pragma once

#include <vector>

namespace Common {
	std::vector<char> ReadFile(const char*);

	bool isAlpha(char ch);

	bool isNumeric(char ch);

	bool isWhitespace(char ch);

	std::string parseIdentifier(std::vector<char>& input, int& current, bool includeDigits);

	void consumeSpace(std::vector<char>& input, int& current);

	void match(std::vector<char>& input, int& current, int line, char ch);

	long parseNumber(std::vector<char>& input, int& current);

	void parseNumberList(std::vector<char>& input, int& current, std::vector<long>* numbers);

	void consumeNewlines(std::vector<char>& input, int& current, int& line);

	void matchKeyword(std::vector<char>& input, int& current, int& line, const char* keyword);
}
