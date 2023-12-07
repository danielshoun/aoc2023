#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../compat/compat.h"

int day6part1() {
	int c;
	int* race_times = malloc(0);
	int race_times_size = 0;
	int* distance_records = malloc(0);
	int distance_records_size = 0;
	int on_distance_records = 0;
	char* curr_num_str = malloc(0);

	FILE* file;
	fopen_s(&file, "./day6/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (c == ' ' || c == '\n') {
				if (strlen(curr_num_str) > 0) {
					int curr_num = strtol(curr_num_str, NULL, 10);
					if (on_distance_records == 0) {
						race_times_size += 1;
						int* new_race_times = realloc(race_times, race_times_size * sizeof(int));
						new_race_times[race_times_size - 1] = curr_num;
						race_times = new_race_times;
					} else {
						distance_records_size += 1;
						int* new_distance_records = realloc(distance_records, distance_records_size * sizeof(int));
						new_distance_records[distance_records_size - 1] = curr_num;
						distance_records = new_distance_records;
					}
					if (c == '\n') {
						on_distance_records = 1;
					}
					free(curr_num_str);
					curr_num_str = malloc(0);
				}
			} else if (isdigit(c)) {
				size_t curr_num_str_len = strlen(curr_num_str);
				char* new_num_str = malloc(curr_num_str_len + 1 + 1);
				strcpy_s(new_num_str, curr_num_str_len + 1, curr_num_str);
				new_num_str[curr_num_str_len] = c;
				new_num_str[curr_num_str_len + 1] = '\0';
				free(curr_num_str);
				curr_num_str = malloc(strlen(new_num_str) + 1);
				strcpy_s(curr_num_str, strlen(new_num_str) + 1, new_num_str);
				free(new_num_str);
			}
		}

		int sum = 1;

		for (int i = 0; i < race_times_size; i++) {
			int race_time = race_times[i];
			int distance_record = distance_records[i];

			int num_ways_to_win = 0;
			for (int j = 1; j < race_time; j++) {
				int time_moving = race_time - j;
				int distance_moved = j * time_moving;
				if (distance_moved > distance_record) {
					num_ways_to_win += 1;
				}
			}
			sum *= num_ways_to_win;
		}

		printf("%i", sum);
	}
	return 0;
}

int day6part2() {
	int c;
	int64_t race_time = 0;
	int64_t distance_record = 0;
	int on_distance_records = 0;
	char* curr_num_str = malloc(0);

	FILE* file;
	fopen_s(&file, "./day6/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (c == '\n') {
				if (strlen(curr_num_str) > 0) {
					int64_t curr_num = strtol(curr_num_str, NULL, 10);
					if (on_distance_records == 0) {
						race_time = curr_num;
					} else {
						distance_record = curr_num;
					}
					on_distance_records = 1;
					free(curr_num_str);
					curr_num_str = malloc(0);
				}
			} else if (isdigit(c)) {
				size_t curr_num_str_len = strlen(curr_num_str);
				char* new_num_str = malloc(curr_num_str_len + 1 + 1);
				strcpy_s(new_num_str, curr_num_str_len + 1, curr_num_str);
				new_num_str[curr_num_str_len] = c;
				new_num_str[curr_num_str_len + 1] = '\0';
				free(curr_num_str);
				curr_num_str = malloc(strlen(new_num_str) + 1);
				strcpy_s(curr_num_str, strlen(new_num_str) + 1, new_num_str);
				free(new_num_str);
			}
		}

		int num_ways_to_win = 0;
		for (int64_t i = 1; i < race_time; i++) {
			int64_t time_moving = race_time - i;
			int64_t distance_moved = i * time_moving;
			if (distance_moved > distance_record) {
				num_ways_to_win += 1;
			}
		}

		printf("%i", num_ways_to_win);
	}
	return 0;
}
