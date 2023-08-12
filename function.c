#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

FILE* open_file_read(char* name) {
	FILE* input;
	if (fopen_s(&input, name, "r")) {
		printf(ERROR_FILE);
		exit(1);
	}
	return input;
}
FILE* open_file_write(char* name) {
	FILE* output;
	if (fopen_s(&output, name, "w")) {
		printf(ERROR_FILE);
		exit(1);
	}
	return output;
}

void Replacement(char* pod, char* zam, FILE* input, FILE* output) {
	int FlagMemory = 0, FlagSimvol = 0;
	int SizePod = strlen(pod), SizeZam = strlen(zam);
	int index = 0;
	int CountCoincidence = 0;
	int CountBits = 0;
	char buf[SIZE_BUFFER];
	int indexCheck = 0;
	int* key = (int*)malloc(strlen(pod) * sizeof(int));
	int* valueLen = (int*)malloc(strlen(pod) * sizeof(int));
	int countCoin = 0;
	for (int i = 1; i < strlen(pod); ++i) {
		if (pod[indexCheck] == pod[i]) {
			indexCheck++;
		}
		else {
			if (indexCheck != 0) {
				key[countCoin] = i;
				valueLen[countCoin] = indexCheck;
				countCoin++;
				indexCheck = 0;
			}
		}
	}
	while (1) {
		CountBits = fread(buf, 1, SIZE_BUFFER, input);
		if (CountBits == 0) {
			break;
		}
		for (int i = 0; i < CountBits; ++i) {
			char bufI = buf[i];
			char podIndex = pod[index];
			if (buf[i] == pod[index]) {
				int flag = 0;
				for (int k = index; i < CountBits; ++i, ++k) {
					if (k == SizePod) {
						break;
					}
					if (buf[i] == pod[k]) {
						CountCoincidence++;
					}
					else {
						flag = 1;
						break;
					}
				}
				if (CountCoincidence == SizePod) {
					fwrite(zam, 1, SizeZam, output);
					printf("%s", zam);
					CountCoincidence = 0;
					index = 0;
					FlagMemory = 0;
				}
				else if (CountCoincidence < SizePod && flag == 0) {
					index += (CountCoincidence-index);
					FlagMemory = 1;
					break;
				}
				else if (flag == 1) {
					int curIndex = index + 1;
					index = 0;
					int backLen = 0;
						for (int k = 0; k < countCoin; ++k) {
							if (curIndex == key[k]) {
								index = valueLen[k] + 1;
								backLen = valueLen[k] + 1;
								break;
							}
						}
						fwrite(pod, 1, CountCoincidence - backLen + 1, output);
						for (int k = 0; k < CountCoincidence;++k) {
							printf("%c", pod[k]);
						}
					CountCoincidence = backLen;
					
					FlagMemory = 0;
				}
			}
			else {
				fwrite(buf + i, 1, 1, output);
				printf("%c", buf[i]);
			}
			if (FlagSimvol == 1) {
				fwrite(buf + i, 1, 1, output);
				printf("%c", buf[i]);
				FlagSimvol = 0;
			}
		}
	}
	printf("\n");
}