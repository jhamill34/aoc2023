#include "common/common.h"

#include <iostream>

struct Pull {
	int red;
	int blue;
	int green;
};

struct Game {
	int number;
	std::vector<Pull> pulls;
};

int parseNumber(std::vector<char>& input, int& current) {
	std::string digits = "";

	char ch = input[current];

	while (ch >= '0' && ch <= '9') {
		digits += ch;
		current++;
		ch = input[current];
	}

	return std::stoi(digits);
}

bool checkWord(std::vector<char>& buffer, int& start, const char * word, int wordLength) {
	if (start + wordLength >= buffer.size()) {
		return false;
	} 

	for (int i = 0; i < wordLength; i++) {
		if (buffer[start + i] != word[i]) {
			return false;
		}
	}

	start += wordLength;

	return true;
}

Pull parsePull(std::vector<char>& input, int& current) {
	Pull currentPull = { 0, 0, 0 };

	do {
		//,\s OR :\s
		current += 2;

		int amount = parseNumber(input, current);
		// \s
		current++;

		if (checkWord(input, current, "red", 3)) {
			currentPull.red = amount;
		} else if (checkWord(input, current, "blue", 4)) {
			currentPull.blue = amount;
		} else if (checkWord(input, current, "green", 5)) {
			currentPull.green = amount;
		}
	} while (input[current] == ',');

	return currentPull;
}

std::vector<Pull> parsePulls(std::vector<char>& input, int& current) {
	std::vector<Pull> pulls;

	do {
		Pull pull = parsePull(input, current);
		pulls.push_back(pull);
	} while(input[current] != '\n');

	return pulls;
}

Game parseGame(std::vector<char>& input, int& current) {
	Game game;
	checkWord(input, current, "Game ", 5);

	game.number = parseNumber(input, current);
	game.pulls = parsePulls(input, current);

	return game;
}

std::vector<Game> Parse(std::vector<char>& input) {
	std::vector<Game> games;

	int current = 0;
	char ch;

	while (current < input.size()) {
		Game game = parseGame(input, current);
		games.push_back(game);
		current++;
	}

	return games;
}

const int MAX_RED = 12;
const int MAX_GREEN = 13;
const int MAX_BLUE = 14;

void part1(std::vector<Game>& games) {
	int total = 0;

	for (auto game : games) {
		Pull max = { 0, 0, 0 };
		for (auto pull : game.pulls) {
			if (pull.red > max.red) {
				max.red = pull.red;
			}
			
			if (pull.blue > max.blue) {
				max.blue = pull.blue;
			}
			
			if (pull.green > max.green) {
				max.green = pull.green;
			}
		}

		if (max.red <= MAX_RED && max.green <= MAX_GREEN && max.blue <= MAX_BLUE) {
			total += game.number;
		}
	}

	std::cout << "Total " << total << std::endl;
} 

void part2(std::vector<Game>& games) {
	int total = 0;

	for (auto game : games) {
		Pull max = { 0, 0, 0 };
		for (auto pull : game.pulls) {
			if (pull.red > max.red) {
				max.red = pull.red;
			}
			
			if (pull.blue > max.blue) {
				max.blue = pull.blue;
			}
			
			if (pull.green > max.green) {
				max.green = pull.green;
			}
		}

		int power = max.red * max.green * max.blue;

		total += power;
	}

	std::cout << "Total " << total << std::endl;
}

int main(int argc, char *argv[]) { 
	std::vector<char> input = Common::ReadFile(argv[1]);
	std::vector<Game> games = Parse(input);

	// part1(games);
	part2(games);

    return 0; 
}
