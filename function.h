#pragma once

#define ERROR_FILE "Error opening the file\n"
#define ERROR_MEMORY "Memory allocation error\n"
#define SIZE_BUFFER 8


FILE* open_file_read(char*);
FILE* open_file_write(char*);
void Replacement(char*, char*, FILE*, FILE*);