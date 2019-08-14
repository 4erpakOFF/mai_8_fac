#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

#define _BSD_SOURCE
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

void print_file(char* path);
size_t file_size(FILE* file);
bool is_sep(char c);
void range(FILE* file, size_t file_size);
bool is_already_opened(char* path, bool is_from_parser);
void search(FILE* file, size_t file_size, char* pattern);
void erase(FILE* file, int position, int count);
void write_to_file (FILE* file, int position, char* text);

#endif
