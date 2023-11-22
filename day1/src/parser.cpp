#include "parser.h"

#include <cmath>
#include <iostream>
#include <vector>

int handleRange(std::vector<char> data, size_t start, size_t end) {
	int val = 0;
	size_t length = end - start;

	for (size_t i = 0; i < length; i++) {
		char ch = data[end - i - 1];
		int digit = ch - '0';

		val += digit * pow(10, i);
	}

	return val;
}

std::vector<int> Parse(std::vector<char> data) {
	uint8_t place = 0;
	size_t start = 0;
	size_t current = 0;
	char ch;
	int val = 0;

	std::vector<int> result;

	while (current < data.size()) {
		ch = data[current];

		if (ch >= '0' && ch <= '9') {
			current++;
		} else if (ch == '\n') {
			if (start != current) {
				val += handleRange(data, start, current);
			} else {
				result.push_back(val);

				val = 0;
			}
			start = current + 1;
			current = start;
		}
	}

	return result;
}
