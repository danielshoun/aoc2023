#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../compat/compat.h"

struct MovePath {
	char* src;
	char* dests[2];
};

int day8part1() {
	int c;

	int instructions_size = 0;
	int* instructions = malloc(0);
	int past_instructions = 0;

	int chars_in_line = 0;
	char line_alpha_str[10] = "\0\0\0\0\0\0\0\0\0\0";

	int move_paths_size = 0;
	struct MovePath* move_paths = malloc(0);

	FILE* file;
	fopen_s(&file, "./day8/input.txt", "r");
	if (file) {
		while((c = getc(file)) != EOF) {
			if (past_instructions == 0) {
				if (c == 'L') {
					instructions_size += 1;
					int* new_instructions = realloc(instructions, instructions_size * sizeof(int));
					new_instructions[instructions_size - 1] = 0;
					instructions = new_instructions;
				} else if (c == 'R') {
					instructions_size += 1;
					int* new_instructions = realloc(instructions, instructions_size * sizeof(int));
					new_instructions[instructions_size - 1] = 1;
					instructions = new_instructions;
				} else if (c == '\n') {
					past_instructions = 1;
				}
			} else {
				if (isalpha(c) || isdigit(c)) {
					line_alpha_str[chars_in_line] = c;
					chars_in_line += 1;
				} else if (c == '\n' && chars_in_line > 0) {
					char* src = malloc(4);
					strncpy(src, line_alpha_str, 3);
					src[3] = '\0';
					char* left_dest = malloc(4);
					strncpy(left_dest, line_alpha_str + 3, 3);
					left_dest[3] = '\0';
					char* right_dest = malloc(4);
					strncpy(right_dest, line_alpha_str + 6, 3);
					right_dest[3] = '\0';
					struct MovePath new_move_path = {
						src,
						{left_dest, right_dest}
					};

					move_paths_size += 1;
					struct MovePath* new_move_paths = realloc(move_paths, move_paths_size * sizeof(struct MovePath));
					new_move_paths[move_paths_size - 1] = new_move_path;
					move_paths = new_move_paths;

					chars_in_line = 0;
				}
 			}
		}

		char* curr_node = malloc(4);
		strcpy_s(curr_node, 3, "AAA");
		curr_node[3] = '\0';
		int sum = 0;
		int instruction_index = 0;
		while(strcmp(curr_node, "ZZZ") != 0) {
			if (instruction_index == instructions_size) {
				instruction_index = 0;
			}

			int instruction = instructions[instruction_index];
			for (int i = 0; i < move_paths_size; i++) {
				struct MovePath move_path = move_paths[i];
				if (strcmp(curr_node, move_path.src) == 0) {
					printf("Moving From %s to %s (%i)\n", curr_node, move_path.dests[instruction], instruction);
					curr_node = move_path.dests[instruction];
					break;
				}
			}

			sum += 1;
			instruction_index += 1;
		}

		printf("%i", sum);
	}
	return 0;
}

int all_end_in_z(struct MovePath* nodes, int nodes_size) {
	for (int i = 0; i < nodes_size; i++) {
		struct MovePath node = nodes[i];
		if (node.src[2] != 'Z') return 0;
	}
	return 1;
}

int day8part2() {
	int c;

	int instructions_size = 0;
	int* instructions = malloc(0);
	int past_instructions = 0;

	int chars_in_line = 0;
	char line_alpha_str[10] = "\0\0\0\0\0\0\0\0\0\0";

	int move_paths_size = 0;
	struct MovePath* move_paths = malloc(0);

	FILE* file;
	fopen_s(&file, "./day8/input.txt", "r");
	if (file) {
		while((c = getc(file)) != EOF) {
			if (past_instructions == 0) {
				if (c == 'L') {
					instructions_size += 1;
					int* new_instructions = realloc(instructions, instructions_size * sizeof(int));
					new_instructions[instructions_size - 1] = 0;
					instructions = new_instructions;
				} else if (c == 'R') {
					instructions_size += 1;
					int* new_instructions = realloc(instructions, instructions_size * sizeof(int));
					new_instructions[instructions_size - 1] = 1;
					instructions = new_instructions;
				} else if (c == '\n') {
					past_instructions = 1;
				}
			} else {
				if (isalpha(c) || isdigit(c)) {
					line_alpha_str[chars_in_line] = c;
					chars_in_line += 1;
				} else if (c == '\n' && chars_in_line > 0) {
					char* src = malloc(4);
					strncpy(src, line_alpha_str, 3);
					src[3] = '\0';
					char* left_dest = malloc(4);
					strncpy(left_dest, line_alpha_str + 3, 3);
					left_dest[3] = '\0';
					char* right_dest = malloc(4);
					strncpy(right_dest, line_alpha_str + 6, 3);
					right_dest[3] = '\0';
					struct MovePath new_move_path = {
						src,
						{left_dest, right_dest}
					};

					move_paths_size += 1;
					struct MovePath* new_move_paths = realloc(move_paths, move_paths_size * sizeof(struct MovePath));
					new_move_paths[move_paths_size - 1] = new_move_path;
					move_paths = new_move_paths;

					chars_in_line = 0;
				}
			}
		}

		int num_starting_nodes = 0;
		struct MovePath* curr_nodes = malloc(0);
		for (int x = 0; x < move_paths_size; x++) {
			struct MovePath move_path = move_paths[x];
			if (move_path.src[2] == 'A') {
				num_starting_nodes += 1;
				struct MovePath* new_curr_nodes = realloc(curr_nodes, num_starting_nodes * sizeof(struct MovePath));
				new_curr_nodes[num_starting_nodes - 1] = move_path;
				curr_nodes = new_curr_nodes;
			}
		}

		int sum = 0;
		int instruction_index = 0;
		while(all_end_in_z(curr_nodes, num_starting_nodes) == 0) {
			if (instruction_index == instructions_size) {
				instruction_index = 0;
			}

			int instruction = instructions[instruction_index];
			for (int i = 0; i < num_starting_nodes; i++) {
				struct MovePath node = curr_nodes[i];
				char* dest_node = node.dests[instruction];
				for (int j = 0; j < move_paths_size; j++) {
					struct MovePath move_path = move_paths[j];
					if (strcmp(move_path.src, dest_node) == 0) {
						curr_nodes[i] = move_path;
					}
				}
			}

			sum += 1;
			instruction_index += 1;
		}

		printf("%i", sum);
	}
	return 0;
}
