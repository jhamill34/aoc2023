#include "common/common.h"
#include "parser.h"

#include <iostream>
#include <vector>

int main(int argc, char *argv[]) { 
	std::vector<char> buffer = Common::ReadFile(argv[1]);
	int score = Parse(buffer);

	std::cout << score << std::endl;

    return 0; 
}
