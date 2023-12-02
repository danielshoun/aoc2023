//
// Created by micro on 12/1/2023.
//
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_RED = 12;
const int MAX_GREEN = 13;
const int MAX_BLUE = 14;

int day2part1() {
	int c;
	int game_id = 1;
	int past_game_id = 0;
	char* curr_num_str = malloc(0);
	char* curr_color = malloc(0);
	int curr_game_is_possible = 1;
	int sum = 0;

	FILE* file;
	fopen_s(&file, "./day2/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (c == ':') {
				past_game_id = 1;
			} else if (past_game_id == 1) {
				if (c == ',' || c == ';') {
					curr_num_str[0] = 0;
					curr_color[0] = 0;
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
				} else if (isalpha(c)) {
					size_t curr_color_len = strlen(curr_color);
					char* new_color = malloc(curr_color_len + 1 + 1);
					strcpy_s(new_color, curr_color_len + 1, curr_color);
					new_color[curr_color_len] = c;
					new_color[curr_color_len + 1] = '\0';
					free(curr_color);
					curr_color = malloc(strlen(new_color) + 1);
					strcpy_s(curr_color, strlen(new_color) + 1, new_color);
					free(new_color);

					if (strcmp(curr_color, "red") == 0) {
						if (strtol(curr_num_str, NULL, 10) > MAX_RED) {
							curr_game_is_possible = 0;
						}
					} else if (strcmp(curr_color, "green") == 0) {
						if (strtol(curr_num_str, NULL, 10) > MAX_GREEN) {
							curr_game_is_possible = 0;
						}
					} else if (strcmp(curr_color, "blue") == 0) {
						if (strtol(curr_num_str, NULL, 10) > MAX_BLUE) {
							curr_game_is_possible = 0;
						}
					}
				} else if (c == '\n') {
					if (curr_game_is_possible == 1) {
						sum += game_id;
					}
					game_id += 1;
					past_game_id = 0;
					curr_num_str[0] = 0;
					curr_color[0] = 0;
					curr_game_is_possible = 1;
				}
			}
		}
	}
	free(curr_num_str);
	free(curr_color);
	printf("%i", sum);
	return 0;
}

int day2part2() {
	int c;
	int game_id = 1;
	int past_game_id = 0;
	char* curr_num_str = malloc(0);
	char* curr_color = malloc(0);
	int curr_max_red = 0;
	int curr_max_green = 0;
	int curr_max_blue = 0;
	int sum = 0;

	FILE* file;
	fopen_s(&file, "./day2/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (c == ':') {
				past_game_id = 1;
			} else if (past_game_id == 1) {
				if (c == ',' || c == ';') {
					curr_num_str[0] = 0;
					curr_color[0] = 0;
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
				} else if (isalpha(c)) {
					size_t curr_color_len = strlen(curr_color);
					char* new_color = malloc(curr_color_len + 1 + 1);
					strcpy_s(new_color, curr_color_len + 1, curr_color);
					new_color[curr_color_len] = c;
					new_color[curr_color_len + 1] = '\0';
					free(curr_color);
					curr_color = malloc(strlen(new_color) + 1);
					strcpy_s(curr_color, strlen(new_color) + 1, new_color);
					free(new_color);

					if (strcmp(curr_color, "red") == 0) {
						if (strtol(curr_num_str, NULL, 10) > curr_max_red) {
							curr_max_red = strtol(curr_num_str, NULL, 10);
						}
					} else if (strcmp(curr_color, "green") == 0) {
						if (strtol(curr_num_str, NULL, 10) > curr_max_green) {
							curr_max_green = strtol(curr_num_str, NULL, 10);
						}
					} else if (strcmp(curr_color, "blue") == 0) {
						if (strtol(curr_num_str, NULL, 10) > curr_max_blue) {
							curr_max_blue = strtol(curr_num_str, NULL, 10);
						}
					}
				} else if (c == '\n') {
					sum += (curr_max_red * curr_max_green * curr_max_blue);

					game_id += 1;
					past_game_id = 0;
					curr_num_str[0] = 0;
					curr_color[0] = 0;
					curr_max_red = 0;
					curr_max_green = 0;
					curr_max_blue = 0;
				}
			}
		}
	}
	free(curr_num_str);
	free(curr_color);
	printf("%i", sum);
	return 0;
}
