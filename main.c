#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "day1/day1.h"
#include "day2/day2.h"

const static struct {
	const int day;
	const int part;

	int (*func)();
} function_map[] = {
	{1, 1, day1part1},
	{1, 2, day1part2},
	{2, 1, day2part1},
	{2, 2, day2part2}
};

int main(int argc, char** argv) {
	if (argc != 5) {
		printf("Incorrect number of arguments passed.");
		return -1;
	}

	int day = -1;
	int part = -1;

	const char* arg_to_set = "";

	for (int i = 1; i < argc; i++) {
		char* arg = argv[i];

		if (i % 2 != 0 && strcmp(arg, "--day") != 0 && strcmp(arg, "--part") != 0) {
			printf("Invalid argument passed: %s\n", arg);
			return -1;
		}

		if (i % 2 != 0) {
			arg_to_set = arg;
		} else {
			if (strcmp(arg_to_set, "--day") == 0) {
				day = strtol(arg, NULL, 10);
			} else {
				part = strtol(arg, NULL, 10);
			}
		}
	}

	if (day > 25 || day < 0) {
		printf("Invalid day passed.\n");
		return -1;
	}

	if (part > 2 || part < 1) {
		printf("Invalid part passed.\n");
		return -1;
	}

	int did_run = 0;

	for (int i = 0; i < sizeof(function_map) / sizeof(function_map[0]); i++) {
		if (day == function_map[i].day && part == function_map[i].part) {
			did_run = 1;
			const clock_t begin = clock();
			function_map[i].func();
			const clock_t end = clock();
			const double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
			printf("\nExecution time: %f seconds", time_spent);
		}
	}

	if (did_run == 0) {
		printf("Day %i Part %i not implemented yet.", day, part);
		return -1;
	}

	return 0;
}
