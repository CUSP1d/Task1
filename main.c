#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h> // для int64_t
#include <inttypes.h> // для правильного вывода int64_t в printf

#include "function.h"

int main(int argc, char* argv[]) {
	FILE* input, *output;
	input = open_file_read(argv[1]);
	output = open_file_write(argv[2]);
	Replacement(argv[3], argv[4], input, output);
	printf("The replacement was successful\n");
	fclose(input);
	fclose(output);
	return 0;
}