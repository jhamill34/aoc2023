#include "common/common.h"
#include <algorithm>
#include <iostream>

#define HAND_SIZE 5
#define CARD_TYPES 13

bool cardComp(uint8_t a, uint8_t b) { return a > b; }

struct Hand {
	int bid;
	uint8_t cards[HAND_SIZE];
	int rank;
};

int handRank1(uint8_t cards[]) {
	uint8_t options[CARD_TYPES] = {0};

	for (int i = 0; i < HAND_SIZE; i++) {
		options[cards[i]]++;
	}

	uint8_t *front = options;
	uint8_t *back = options + CARD_TYPES;

	std::sort(front, back, cardComp);

	if (*front == 5) {
		return 0; // 5 of a kind
	} else if (*front == 4) {
		return 1; // 4 of a kind
	} else if (*front == 3 && *(front + 1) == 2) {
		return 2; // full house
	} else if (*front == 3 && *(front + 1) == 1) {
		return 3; // 3 of a kind
	} else if (*front == 2 && *(front + 1) == 2) {
		return 4; // 2 pair
	} else if (*front == 2 && *(front + 1) == 1) {
		return 5; // 1 pair
	} else {
		return 6; // high card
	}
}

int handRank2(uint8_t cards[]) {
	uint8_t options[CARD_TYPES] = {0};

	for (int i = 0; i < HAND_SIZE; i++) {
		options[cards[i]]++;
	}

	uint8_t *front = options + 1;
	uint8_t *back = options + CARD_TYPES;

	std::sort(front, back, cardComp);

	uint8_t jokerCount = *options;

	if (*front + jokerCount == 5) {
		return 0; // 5 of a kind
	} else if (*front + jokerCount == 4) {
		return 1; // 4 of a kind
	} else if (*front + jokerCount == 3 && *(front + 1) == 2) {
		return 2; // full house
	} else if (*front + jokerCount == 3 && *(front + 1) == 1) {
		return 3; // 3 of a kind
	} else if (*front + jokerCount == 2 && *(front + 1) == 2) {
		return 4; // 2 pair
	} else if (*front + jokerCount == 2 && *(front + 1) == 1) {
		return 5; // 1 pair
	} else {
		return 6; // high card
	}
}

bool handComp(Hand a, Hand b) {
	if (a.rank == b.rank) {
		int i = 0;
		while(a.cards[i] == b.cards[i]) {
			i++;
		}

		return a.cards[i] < b.cards[i];
	}

	return a.rank > b.rank;
}

uint8_t cardRank2(char ch) {
	if (ch == 'J') {
		return 0;
	}

	if (ch >= '2' && ch <= '9') {
		return ch - '2' + 1;
	}

	uint8_t upper = '9' - '2';
	if (ch == 'T') {
		return upper + 2;
	}
	
	if (ch == 'Q') {
		return upper + 3;
	}
	
	if (ch == 'K') {
		return upper + 4;
	}
	
	if (ch == 'A') {
		return upper + 5;
	}

	std::cout << "Invalid card: " << ch << "\n";
	exit(1);
}

uint8_t cardRank1(char ch) {
	if (ch >= '2' && ch <= '9') {
		return ch - '2';
	}

	uint8_t upper = '9' - '2';
	if (ch == 'T') {
		return upper + 1;
	}
	
	if (ch == 'J') {
		return upper + 2;
	}
	
	if (ch == 'Q') {
		return upper + 3;
	}
	
	if (ch == 'K') {
		return upper + 4;
	}
	
	if (ch == 'A') {
		return upper + 5;
	}

	std::cout << "Invalid card: " << ch << "\n";
	exit(1);
}

Hand ParseHand1(std::vector<char>&data, int& current, int& line) {
	Hand hand;

	for (int i = 0; i < HAND_SIZE; i++) {
		hand.cards[i] = cardRank1(data[current]);
		current++;
	}

	hand.rank = handRank1(hand.cards);

	Common::consumeSpace(data, current);
	hand.bid = Common::parseNumber(data, current);

	return hand;
}

std::vector<Hand> Parse1(std::vector<char> &data) {
	int current = 0;
	int line = 1;

	std::vector<Hand> hands;

	while (current < data.size()) {
		hands.push_back(ParseHand1(data, current, line));

		Common::consumeNewlines(data, current, line);
	}

	return hands;
}

Hand ParseHand2(std::vector<char>&data, int& current, int& line) {
	Hand hand;

	for (int i = 0; i < HAND_SIZE; i++) {
		hand.cards[i] = cardRank2(data[current]);
		current++;
	}

	hand.rank = handRank2(hand.cards);

	Common::consumeSpace(data, current);
	hand.bid = Common::parseNumber(data, current);

	return hand;
}

std::vector<Hand> Parse2(std::vector<char> &data) {
	int current = 0;
	int line = 1;

	std::vector<Hand> hands;

	while (current < data.size()) {
		hands.push_back(ParseHand2(data, current, line));

		Common::consumeNewlines(data, current, line);
	}

	return hands;
}

int main(int argc, char *argv[]) { 
	std::vector<char> data = Common::ReadFile(argv[1]);

	std::vector<Hand> hands;

#ifdef PART1 
	hands = Parse1(data);
#endif

#ifdef PART2
	hands = Parse2(data);
#endif

	std::stable_sort(hands.begin(), hands.end(), handComp);

	int total = 0;
	for (int i = 0; i < hands.size(); i++) {
		total += ((i + 1) * hands[i].bid);
	}

	std::cout << "Total winnings: " << total << "\n";

    return 0; 
}
