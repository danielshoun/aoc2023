#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../compat/compat.h"

int day4part1() {
	int c;
	int card_id = 1;
	int past_card_id = 0;
	int past_winning_numbers = 0;
	char* curr_num_str = malloc(0);
	int curr_winning_numbers_size = 0;
	int* curr_winning_numbers = malloc(0);
	int curr_points = 0;
	int sum = 0;

	FILE* file;
	fopen_s(&file, "./day4/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (c == ':') {
				past_card_id = 1;
			} else if (c == '|') {
				past_winning_numbers = 1;
			} else if (c == '\n') {
				if (strlen(curr_num_str) > 0) {
					int curr_num = strtol(curr_num_str, NULL, 10);
					for (int i = 0; i < curr_winning_numbers_size; i++) {
						int winning_number = curr_winning_numbers[i];
						if (curr_num == winning_number) {
							if (curr_points == 0) {
								curr_points += 1;
							} else {
								curr_points *= 2;
							}
						}
					}
				}
				card_id += 1;
				past_card_id = 0;
				past_winning_numbers = 0;
				free(curr_num_str);
				curr_num_str = malloc(0);
				free(curr_winning_numbers);
				curr_winning_numbers = malloc(0);
				curr_winning_numbers_size = 0;
				sum += curr_points;
				curr_points = 0;
			} else if (isdigit(c) && past_card_id == 1) {
				size_t curr_num_str_len = strlen(curr_num_str);
				char* new_num_str = malloc(curr_num_str_len + 1 + 1);
				strcpy_s(new_num_str, curr_num_str_len + 1, curr_num_str);
				new_num_str[curr_num_str_len] = c;
				new_num_str[curr_num_str_len + 1] = '\0';
				free(curr_num_str);
				curr_num_str = malloc(strlen(new_num_str) + 1);
				strcpy_s(curr_num_str, strlen(new_num_str) + 1, new_num_str);
				free(new_num_str);
			} else if (past_card_id == 1 && past_winning_numbers == 0 && strlen(curr_num_str) > 0) {
				curr_winning_numbers_size += 1;
				int* new_curr_winning_numbers = realloc(curr_winning_numbers, curr_winning_numbers_size * sizeof(int));
				new_curr_winning_numbers[curr_winning_numbers_size - 1] = strtol(curr_num_str, NULL, 10);
				curr_winning_numbers = new_curr_winning_numbers;
				free(curr_num_str);
				curr_num_str = malloc(0);
			} else if (past_winning_numbers == 1 && strlen(curr_num_str)) {
				int curr_num = strtol(curr_num_str, NULL, 10);
				for (int i = 0; i < curr_winning_numbers_size; i++) {
					int winning_number = curr_winning_numbers[i];
					if (curr_num == winning_number) {
						if (curr_points == 0) {
							curr_points += 1;
						} else {
							curr_points *= 2;
						}
					}
				}
				free(curr_num_str);
				curr_num_str = malloc(0);
			}
		}
	}

	printf("%i", sum);
	return 0;
}

int day4part2() {
	int c;
	int card_id = 1;
	int past_card_id = 0;
	int past_winning_numbers = 0;
	char* curr_num_str = malloc(0);
	int curr_winning_numbers_size = 0;
	int* curr_winning_numbers = malloc(0);
	int card_ids_to_copy_size = 0;
	int* card_ids_to_copy = malloc(0);
	int num_matches = 0;
	int sum = 0;

	FILE* file;
	fopen_s(&file, "./day4/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (c == ':') {
				past_card_id = 1;
			} else if (c == '|') {
				past_winning_numbers = 1;
			} else if (c == '\n') {
				if (strlen(curr_num_str) > 0) {
					int curr_num = strtol(curr_num_str, NULL, 10);
					for (int i = 0; i < curr_winning_numbers_size; i++) {
						int winning_number = curr_winning_numbers[i];
						if (curr_num == winning_number) {
							num_matches += 1;
						}
					}
				}

				sum += 1;
				for (int i = 1; i <= num_matches; i++) {
					card_ids_to_copy_size += 1;
					int* new_card_ids_to_copy = realloc(card_ids_to_copy, card_ids_to_copy_size * sizeof(int));
					new_card_ids_to_copy[card_ids_to_copy_size - 1] = card_id + i;
					card_ids_to_copy = new_card_ids_to_copy;
				}

				for (int i = 0; i < card_ids_to_copy_size; i++) {
					int possible_card_id = card_ids_to_copy[i];
					if (card_id == possible_card_id) {
						sum += 1;
						for (int j = 1; j <= num_matches; j++) {
							card_ids_to_copy_size += 1;
							int* new_card_ids_to_copy = realloc(card_ids_to_copy, card_ids_to_copy_size * sizeof(int));
							new_card_ids_to_copy[card_ids_to_copy_size - 1] = card_id + j;
							card_ids_to_copy = new_card_ids_to_copy;
						}
					}
				}


				card_id += 1;
				past_card_id = 0;
				past_winning_numbers = 0;
				free(curr_num_str);
				curr_num_str = malloc(0);
				free(curr_winning_numbers);
				curr_winning_numbers = malloc(0);
				curr_winning_numbers_size = 0;
				num_matches = 0;
			} else if (isdigit(c) && past_card_id == 1) {
				size_t curr_num_str_len = strlen(curr_num_str);
				char* new_num_str = malloc(curr_num_str_len + 1 + 1);
				strcpy_s(new_num_str, curr_num_str_len + 1, curr_num_str);
				new_num_str[curr_num_str_len] = c;
				new_num_str[curr_num_str_len + 1] = '\0';
				free(curr_num_str);
				curr_num_str = malloc(strlen(new_num_str) + 1);
				strcpy_s(curr_num_str, strlen(new_num_str) + 1, new_num_str);
				free(new_num_str);
			} else if (past_card_id == 1 && past_winning_numbers == 0 && strlen(curr_num_str) > 0) {
				curr_winning_numbers_size += 1;
				int* new_curr_winning_numbers = realloc(curr_winning_numbers, curr_winning_numbers_size * sizeof(int));
				new_curr_winning_numbers[curr_winning_numbers_size - 1] = strtol(curr_num_str, NULL, 10);
				curr_winning_numbers = new_curr_winning_numbers;
				free(curr_num_str);
				curr_num_str = malloc(0);
			} else if (past_winning_numbers == 1 && strlen(curr_num_str)) {
				int curr_num = strtol(curr_num_str, NULL, 10);
				for (int i = 0; i < curr_winning_numbers_size; i++) {
					int winning_number = curr_winning_numbers[i];
					if (curr_num == winning_number) {
						num_matches += 1;
					}
				}
				free(curr_num_str);
				curr_num_str = malloc(0);
			}
		}
	}

	printf("%i", sum);
	return 0;
}
