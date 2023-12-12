#pragma once

#include <vector>

namespace Common {
	std::vector<char> ReadFile(const char*);

	bool isAlpha(char ch);

	bool isNumeric(char ch);

	bool isWhitespace(char ch);

	std::string parseIdentifier(std::vector<char>& input, int& current, bool includeDigits);

	void consumeSpace(const std::vector<char>& input, int& current);

	void match(const std::vector<char>& input, int& current, int line, const char ch);

	long parseNumber(const std::vector<char>& input, int& current);

	void parseNumberList(std::vector<char>& input, int& current, std::vector<long>* numbers);

	void consumeNewlines(const std::vector<char>& input, int& current, int& line);

	void matchKeyword(std::vector<char>& input, int& current, int& line, const char* keyword);
}
