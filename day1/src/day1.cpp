#include "common/common.h"

#include <cstdio>

int main(int argc, char *argv[]) { 
	char *data = read_file(argv[1]);

	printf("%s\n", data);

	return 0; 
}
