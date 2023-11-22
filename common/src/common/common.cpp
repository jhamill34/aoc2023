#include "common.h"

#include <fstream>

namespace Common {
	std::vector<char> ReadFile(const char *filename) {
		std::ifstream file(filename);

		std::istreambuf_iterator<char> start(file);
		std::istreambuf_iterator<char> end;

		std::vector<char> buffer(start, end);

		return buffer;
	}
}

