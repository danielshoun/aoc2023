#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int all_zeroes(int* arr, int arr_size) {
	if (arr_size == 0) {
		return 0;
	}

	for (int i = 0; i < arr_size; i++) {
		if (arr[i] != 0) {
			return 0;
		}
	}

	return 1;
}

int day9part1() {
	int c;
	char* curr_num_str = malloc(1);
	curr_num_str[0] = '\0';
	int curr_history_size = 0;
	int* curr_history = malloc(0);
	int sum = 0;

	FILE* file;
	fopen_s(&file, "./day9/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (isdigit(c) || c == '-') {
				size_t curr_num_str_len = strlen(curr_num_str);
				char* new_num_str = malloc(curr_num_str_len + 1 + 1);
				strcpy_s(new_num_str, curr_num_str_len + 1, curr_num_str);
				new_num_str[curr_num_str_len] = c;
				new_num_str[curr_num_str_len + 1] = '\0';
				free(curr_num_str);
				curr_num_str = malloc(strlen(new_num_str) + 1);
				strcpy_s(curr_num_str, strlen(new_num_str) + 1, new_num_str);
				free(new_num_str);
			} else {
				curr_history_size += 1;
				int* new_history = realloc(curr_history, curr_history_size * sizeof(int));
				int new_num = strtol(curr_num_str, NULL, 10);
				new_history[curr_history_size - 1] = new_num;
				curr_history = new_history;
				free(curr_num_str);
				curr_num_str = malloc(1);
				curr_num_str[0] = '\0';

				if (c == '\n') {
					int difference_arrays_size = 1;
					int** difference_arrays = malloc(sizeof(int *));
					difference_arrays[0] = curr_history;
					int* difference_arrays_array_sizes = malloc(sizeof(int));
					difference_arrays_array_sizes[0] = curr_history_size;

					while (all_zeroes(difference_arrays[difference_arrays_size - 1],
					                  difference_arrays_array_sizes[difference_arrays_size - 1]) == 0) {
						int* curr_difference_array = difference_arrays[difference_arrays_size - 1];
						int difference_array_size = difference_arrays_array_sizes[difference_arrays_size - 1];
						int next_differences_size = 0;
						int* next_differences = malloc(0);
						for (int i = 1; i < difference_array_size; i++) {
							int new_difference = curr_difference_array[i] - curr_difference_array[i - 1];
							next_differences_size += 1;
							int* new_next_differences = realloc(next_differences, next_differences_size * sizeof(int));
							new_next_differences[next_differences_size - 1] = new_difference;
							next_differences = new_next_differences;
						}
						difference_arrays_size += 1;

						int** new_difference_arrays =
								realloc(difference_arrays, difference_arrays_size * sizeof(int *));
						new_difference_arrays[difference_arrays_size - 1] = next_differences;
						difference_arrays = new_difference_arrays;

						int* new_difference_arrays_array_sizes = realloc(
							difference_arrays_array_sizes, difference_arrays_size * sizeof(int));
						new_difference_arrays_array_sizes[difference_arrays_size - 1] = next_differences_size;
						difference_arrays_array_sizes = new_difference_arrays_array_sizes;
					}

					difference_arrays_array_sizes[difference_arrays_size - 1] += 1;
					int* new_zeroes_array = realloc(difference_arrays[difference_arrays_size - 1],
					                                difference_arrays_array_sizes[difference_arrays_size - 1] * sizeof(
						                                int));
					new_zeroes_array[difference_arrays_array_sizes[difference_arrays_size - 1] - 1] = 0;
					difference_arrays[difference_arrays_size - 1] = new_zeroes_array;

					int new_num = 0;
					for (int i = difference_arrays_size - 2; i >= 0; i--) {
						int* last_array = difference_arrays[i + 1];
						int last_array_size = difference_arrays_array_sizes[i + 1];
						int* curr_array = difference_arrays[i];
						int curr_array_size = difference_arrays_array_sizes[i];

						new_num = last_array[last_array_size - 1] + curr_array[curr_array_size - 1];

						if (i != 0) {
							difference_arrays_array_sizes[i] += 1;
							int* new_curr_array = realloc(curr_array, (curr_array_size + 1) * sizeof(int));
							new_curr_array[curr_array_size] = new_num;
							difference_arrays[i] = new_curr_array;
						}
					}

					sum += new_num;

					curr_history_size = 0;
					free(curr_history);
					curr_history = malloc(0);
				}
			}
		}
	}
	printf("%i", sum);
	return 0;
}

void reverse_array(int* array, int size) {
	for (int i = 0; i < size / 2; i++) {
		int temp = array[i];
		array[i] = array[size - 1 - i];
		array[size - 1 - i] = temp;
	}
}

int day9part2() {
	int c;
	char* curr_num_str = malloc(1);
	curr_num_str[0] = '\0';
	int curr_history_size = 0;
	int* curr_history = malloc(0);
	int sum = 0;

	FILE* file;
	fopen_s(&file, "./day9/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (isdigit(c) || c == '-') {
				size_t curr_num_str_len = strlen(curr_num_str);
				char* new_num_str = malloc(curr_num_str_len + 1 + 1);
				strcpy_s(new_num_str, curr_num_str_len + 1, curr_num_str);
				new_num_str[curr_num_str_len] = c;
				new_num_str[curr_num_str_len + 1] = '\0';
				free(curr_num_str);
				curr_num_str = malloc(strlen(new_num_str) + 1);
				strcpy_s(curr_num_str, strlen(new_num_str) + 1, new_num_str);
				free(new_num_str);
			} else {
				curr_history_size += 1;
				int* new_history = realloc(curr_history, curr_history_size * sizeof(int));
				int new_num = strtol(curr_num_str, NULL, 10);
				new_history[curr_history_size - 1] = new_num;
				curr_history = new_history;
				free(curr_num_str);
				curr_num_str = malloc(1);
				curr_num_str[0] = '\0';

				if (c == '\n') {
					int difference_arrays_size = 1;
					int** difference_arrays = malloc(sizeof(int *));
					reverse_array(curr_history, curr_history_size);
					difference_arrays[0] = curr_history;
					int* difference_arrays_array_sizes = malloc(sizeof(int));
					difference_arrays_array_sizes[0] = curr_history_size;

					while (all_zeroes(difference_arrays[difference_arrays_size - 1],
					                  difference_arrays_array_sizes[difference_arrays_size - 1]) == 0) {
						int* curr_difference_array = difference_arrays[difference_arrays_size - 1];
						int difference_array_size = difference_arrays_array_sizes[difference_arrays_size - 1];
						int next_differences_size = 0;
						int* next_differences = malloc(0);
						for (int i = 1; i < difference_array_size; i++) {
							int new_difference = curr_difference_array[i] - curr_difference_array[i - 1];
							next_differences_size += 1;
							int* new_next_differences = realloc(next_differences, next_differences_size * sizeof(int));
							new_next_differences[next_differences_size - 1] = new_difference;
							next_differences = new_next_differences;
						}
						difference_arrays_size += 1;

						int** new_difference_arrays =
								realloc(difference_arrays, difference_arrays_size * sizeof(int *));
						new_difference_arrays[difference_arrays_size - 1] = next_differences;
						difference_arrays = new_difference_arrays;

						int* new_difference_arrays_array_sizes = realloc(
							difference_arrays_array_sizes, difference_arrays_size * sizeof(int));
						new_difference_arrays_array_sizes[difference_arrays_size - 1] = next_differences_size;
						difference_arrays_array_sizes = new_difference_arrays_array_sizes;
					}

					difference_arrays_array_sizes[difference_arrays_size - 1] += 1;
					int* new_zeroes_array = realloc(difference_arrays[difference_arrays_size - 1],
					                                difference_arrays_array_sizes[difference_arrays_size - 1] * sizeof(
						                                int));
					new_zeroes_array[difference_arrays_array_sizes[difference_arrays_size - 1] - 1] = 0;
					difference_arrays[difference_arrays_size - 1] = new_zeroes_array;

					int new_num = 0;
					for (int i = difference_arrays_size - 2; i >= 0; i--) {
						int* last_array = difference_arrays[i + 1];
						int last_array_size = difference_arrays_array_sizes[i + 1];
						int* curr_array = difference_arrays[i];
						int curr_array_size = difference_arrays_array_sizes[i];

						new_num = last_array[last_array_size - 1] + curr_array[curr_array_size - 1];

						if (i != 0) {
							difference_arrays_array_sizes[i] += 1;
							int* new_curr_array = realloc(curr_array, (curr_array_size + 1) * sizeof(int));
							new_curr_array[curr_array_size] = new_num;
							difference_arrays[i] = new_curr_array;
						}
					}

					sum += new_num;

					curr_history_size = 0;
					free(curr_history);
					curr_history = malloc(0);
				}
			}
		}
	}
	printf("%i", sum);
	return 0;
}
