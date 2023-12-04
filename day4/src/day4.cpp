#include "common/common.h"
#include <iostream>

struct Card {
	int number;
	std::vector<int> winning;
	std::vector<int> selected;
};

void consumeSpace(std::vector<char>& input, int &current) {
	while (input[current] == ' ' || input[current] == '\t') {
		current++;
	}
}

int parseNumber(std::vector<char>& input, int& current) {
	std::string digits = "";

	while (input[current] >= '0' && input[current] <= '9') {
		digits += input[current];
		current++;
	}

	return std::stoi(digits);
}

int parseCardNumber(std::vector<char>& input, int& current) {
	// "Card"
	current += 4;

	consumeSpace(input, current);

	int num = parseNumber(input, current);

	// colon
	current += 1;

	return num;
}

void collectNumbers(std::vector<char>& input, int& current, std::vector<int> *numbers) {
	while (input[current] >= '0' && input[current] <= '9') {
		numbers->push_back(parseNumber(input, current));

		consumeSpace(input, current);
	}
}

std::vector<Card> Parse(std::vector<char>& input) {
	std::vector<Card> cards;
	Card c;

	int current = 0;

	while (current < input.size()) {

		c.number = parseCardNumber(input, current);
		consumeSpace(input, current);

		c.winning.clear();
		c.winning.reserve(5);
		collectNumbers(input, current, &c.winning);
	
		// pipe 
		current += 1;
		consumeSpace(input, current);

		c.selected.clear();
		c.selected.reserve(8);
		collectNumbers(input, current, &c.selected);

		cards.push_back(c);

		current++;
	}

	return cards;
}

int index_of(std::vector<int>& input, int value) {
	int i; 
	for (i = 0; i < input.size(); i++) {
		if (input[i] == value) {
			return i;
		}
	}

	return -1;
}

int num_winning(Card& card) {
	int n = 0;

	for (int val : card.selected) {
		if (index_of(card.winning, val) >= 0) {
			n++;
		} 
	}

	return n;
}

void part1(std::vector<Card>& cards) {
	int total = 0;
	int n, score;

	for (auto card : cards) {
		n = num_winning(card);

		if (n > 0) {
			score = 1 << (n - 1);
			total += score;
		}
	}

	std::cout << "Total: " << total << "\n";
} 

void part2(std::vector<Card>& cards) {
	int total = 0;
	int n, score;

	std::vector<int> counts;
	counts.resize(cards.size(), 1);
	
	int i, j;
	for (i = 0; i < cards.size(); i++) {
		n = num_winning(cards[i]);

		for (j = 0; j < n; j++) {
			counts[i + j + 1] += counts[i];
		}

		total += counts[i];
	}

	std::cout << "Total: " << total << "\n";
} 

int main(int argc, char *argv[]) { 
	std::vector<char> data = Common::ReadFile(argv[1]);
	auto cards = Parse(data);

	// part1(cards);
	part2(cards);

    return 0; 
}
