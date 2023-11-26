#include "parser.h"

#include <iostream>

int Parse(const std::vector<char>& buffer) {
	size_t current = 0;

	int score = 0;

	while (current < buffer.size()) {
		int op = buffer[current] - 'A';
		int me = buffer[current + 2] - 'X';

		score += me + 1;

		int winner = (3 + me - op) % 3;

		if (winner == 1) {
			score += 6;
		} else if (winner == 0) {
			score += 3;
		}

		current += 4;
	}

	return score;
}

