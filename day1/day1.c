#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int day1part1() {
	int c;
	int line_first_digit = -1;
	int line_last_digit = -1;
	int sum = 0;
	FILE* file;
	fopen_s(&file, "./day1/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (isdigit(c)) {
				if (line_first_digit == -1) {
					line_first_digit = c;
				} else {
					line_last_digit = c;
				}
			} else if (c == '\n') {
				if (line_last_digit == -1) {
					line_last_digit = line_first_digit;
				}

				const char digits[2] = {line_first_digit, line_last_digit};

				sum += strtol(digits, NULL, 10);

				line_first_digit = -1;
				line_last_digit = -1;
			}
		}
	}
	printf("%i", sum);
	return 0;
}

const static struct {
	const char* num_string;
	const int digit;
} num_string_map[] = {
	{"one", '1'},
	{"two", '2'},
	{"three", '3'},
	{"four", '4'},
	{"five", '5'},
	{"six", '6'},
	{"seven", '7'},
	{"eight", '8'},
	{"nine", '9'},
};

int day1part2() {
	int c;
	int line_first_digit = -1;
	int line_last_digit = -1;
	char* current_str = malloc(0);
	int sum = 0;
	FILE* file;
	fopen_s(&file, "./day1/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (isdigit(c)) {
				if (line_first_digit == -1) {
					line_first_digit = c;
				} else {
					line_last_digit = c;
				}
				current_str[0] = 0;
			} else if (isalpha(c)) {
				size_t len = strlen(current_str);
				char* new_str = malloc(len + 1 + 1);
				strcpy_s(new_str, len + 1, current_str);
				new_str[len] = c;
				new_str[len + 1] = '\0';
				free(current_str);
				current_str = malloc(strlen(new_str) + 1);
				strcpy_s(current_str, strlen(new_str) + 1, new_str);
				free(new_str);
				len = strlen(current_str);

				for (int i = 0; i < sizeof(num_string_map) / sizeof(num_string_map[0]); i++) {
					const char* num_string = num_string_map[i].num_string;
					const size_t num_string_len = strlen(num_string);

					if (len >= num_string_len && 0 == strcmp(current_str + (len - num_string_len), num_string)) {
						if (line_first_digit == -1) {
							line_first_digit = num_string_map[i].digit;
						} else {
							line_last_digit = num_string_map[i].digit;
						}
					}
				}
			} else if (c == '\n') {
				if (line_last_digit == -1) {
					line_last_digit = line_first_digit;
				}

				const char digits[2] = {line_first_digit, line_last_digit};

				sum += strtol(digits, NULL, 10);

				line_first_digit = -1;
				line_last_digit = -1;
				current_str[0] = 0;
			}
		}
	}
	free(current_str);
	printf("%i", sum);
	return 0;
}
