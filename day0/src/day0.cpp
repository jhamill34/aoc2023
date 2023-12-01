#include "common/common.h"
#include "parser.h"

#include <iostream>
#include <algorithm>

int main(int argc, char *argv[]) {
	std::vector<char> buffer = Common::ReadFile(argv[1]);
	std::vector<int> result = Parse(buffer);

	int max = 0;
	for (int val : result) {
		if (val > max) {
			max = val;
		}
	}

	std::cout << "Max: " << max << std::endl;

	sort(result.begin(), result.end());

	int topThree = result[result.size() - 1] + result[result.size() - 2] + result[result.size() - 3];

	std::cout << "Top Three: " << topThree << std::endl;

	return 0;
}
