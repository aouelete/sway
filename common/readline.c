#include "readline.h"
#include <stdlib.h>
#include <stdio.h>

char *read_line(FILE *file) {
	size_t length = 0, size = 128;
	char *string = malloc(size);
	if (!string) {
		return NULL;
	}
	while (1) {
		int c = getc(file);
		if (c == EOF || c == '\n' || c == '\0') {
			break;
		}
		if (c == '\r') {
			continue;
		}
		if (length == size) {
			char *new_string = realloc(string, size *= 2);
			if (!new_string) {
				free(string);
				return NULL;
			}
			string = new_string;
		}
		string[length++] = c;
	}
	if (length + 1 == size) {
		char *new_string = realloc(string, length + 1);
		if (!new_string) {
			free(string);
			return NULL;
		}
		string = new_string;
	}
	string[length] = '\0';
	return string;
}

char *read_line_buffer(FILE *file, char *string, size_t string_len) {
	size_t length = 0;
	if (!string) {
		return NULL;
	}
	while (1) {
		int c = getc(file);
		if (c == EOF || c == '\n' || c == '\0') {
			break;
		}
		if (c == '\r') {
			continue;
		}
		string[length++] = c;
		if (string_len <= length) {
			return NULL;
		}
	}
	if (length + 1 == string_len) {
		return NULL;
	}
	string[length] = '\0';
	return string;
}
