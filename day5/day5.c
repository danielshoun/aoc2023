#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../compat/compat.h"

struct RangeMap {
	int depth;
	int64_t dest_start;
	int64_t src_start;
	int64_t range;
};

int day5part1() {
	int c;
	char* curr_num_str = malloc(0);
	int seeds_size = 0;
	int64_t* seeds = malloc(0);
	int range_maps_size = 0;
	struct RangeMap* range_maps = malloc(0);
	int curr_depth = -1;
	int64_t curr_dest_start = -1;
	int64_t curr_src_start = -1;
	int64_t curr_range = -1;

	FILE* file;
	fopen_s(&file, "./day5/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (c == ':') {
				curr_depth += 1;
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
			} else if (c == ' ' && strlen(curr_num_str) > 0) {
				if (curr_depth == 0) {
					seeds_size += 1;
					int64_t* new_seeds = realloc(seeds, seeds_size * sizeof(int64_t));
					new_seeds[seeds_size - 1] = strtol(curr_num_str, NULL, 10);
					seeds = new_seeds;
					free(curr_num_str);
					curr_num_str = malloc(0);
				} else if (curr_dest_start == -1) {
					curr_dest_start = strtol(curr_num_str, NULL, 10);
					free(curr_num_str);
					curr_num_str = malloc(0);
				} else {
					curr_src_start = strtol(curr_num_str, NULL, 10);
					free(curr_num_str);
					curr_num_str = malloc(0);
				}
			} else if (c == '\n' && strlen(curr_num_str) > 0) {
				if (curr_depth == 0) {
					seeds_size += 1;
					int64_t* new_seeds = realloc(seeds, seeds_size * sizeof(int64_t));
					new_seeds[seeds_size - 1] = strtol(curr_num_str, NULL, 10);
					seeds = new_seeds;
					free(curr_num_str);
					curr_num_str = malloc(0);
				} else {
					curr_range = strtol(curr_num_str, NULL, 10);
					free(curr_num_str);
					curr_num_str = malloc(0);
					struct RangeMap new_range_map = {
						curr_depth,
						curr_dest_start,
						curr_src_start,
						curr_range
					};
					range_maps_size += 1;
					struct RangeMap* new_range_maps = realloc(range_maps, range_maps_size * sizeof(struct RangeMap));
					new_range_maps[range_maps_size - 1] = new_range_map;
					range_maps = new_range_maps;

					curr_dest_start = -1;
					curr_src_start = -1;
					curr_range = -1;
				}
			}
		}
	}

	int64_t lowest_location = -1;
	for (int i = 0; i < seeds_size; i++) {
		int64_t curr_mapping = seeds[i];
		int found_in_depth = 0;
		int curr_depth = 1;
		for (int j = 0; j < range_maps_size; j++) {
			struct RangeMap range_map = range_maps[j];
			if (range_map.depth != curr_depth) {
				found_in_depth = 0;
				curr_depth += 1;
			}
			if (found_in_depth == 0) {
				int64_t src_end = range_map.src_start + range_map.range - 1;
				if (curr_mapping >= range_map.src_start && curr_mapping <= src_end) {
					printf("Mapping: %lld, Depth: %i, DStart: %lld, SStart: %lld, Range: %lld\n", curr_mapping,
					       range_map.depth, range_map.dest_start, range_map.src_start, range_map.range);
					curr_mapping = range_map.dest_start + (curr_mapping - range_map.src_start);
					found_in_depth = 1;
				}
			}
		}
		printf("Final Location: %lld\n", curr_mapping);
		if (lowest_location == -1 || curr_mapping < lowest_location) {
			lowest_location = curr_mapping;
		}
	}
	printf("%lld", lowest_location);
	return 0;
}

struct SeedRange {
	int64_t start;
	int64_t range;
};

int day5part2() {
	int c;
	char* curr_num_str = malloc(0);
	int seeds_size = 0;
	struct SeedRange* seeds = malloc(0);
	int64_t curr_seed_start = -1;
	int64_t curr_seed_range = -1;

	int range_maps_size = 0;
	struct RangeMap* range_maps = malloc(0);
	int curr_depth = -1;
	int64_t curr_dest_start = -1;
	int64_t curr_src_start = -1;
	int64_t curr_range = -1;

	FILE* file;
	fopen_s(&file, "./day5/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (c == ':') {
				curr_depth += 1;
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
			} else if (c == ' ' && strlen(curr_num_str) > 0) {
				if (curr_depth == 0) {
					if (curr_seed_start == -1) {
						curr_seed_start = strtol(curr_num_str, NULL, 10);
						free(curr_num_str);
						curr_num_str = malloc(0);
					} else {
						curr_seed_range = strtol(curr_num_str, NULL, 10);
						free(curr_num_str);
						curr_num_str = malloc(0);
						struct SeedRange new_seed_range = {
							curr_seed_start,
							curr_seed_range
						};
						seeds_size += 1;
						struct SeedRange* new_seeds = realloc(seeds, seeds_size * sizeof(struct SeedRange));
						new_seeds[seeds_size - 1] = new_seed_range;
						seeds = new_seeds;

						curr_seed_start = -1;
						curr_seed_range = -1;
					}
				} else if (curr_dest_start == -1) {
					curr_dest_start = strtol(curr_num_str, NULL, 10);
					free(curr_num_str);
					curr_num_str = malloc(0);
				} else {
					curr_src_start = strtol(curr_num_str, NULL, 10);
					free(curr_num_str);
					curr_num_str = malloc(0);
				}
			} else if (c == '\n' && strlen(curr_num_str) > 0) {
				if (curr_depth == 0) {
					curr_seed_range = strtol(curr_num_str, NULL, 10);
					free(curr_num_str);
					curr_num_str = malloc(0);
					struct SeedRange new_seed_range = {
						curr_seed_start,
						curr_seed_range
					};
					seeds_size += 1;
					struct SeedRange* new_seeds = realloc(seeds, seeds_size * sizeof(struct SeedRange));
					new_seeds[seeds_size - 1] = new_seed_range;
					seeds = new_seeds;

					curr_seed_start = -1;
					curr_seed_range = -1;
				} else {
					curr_range = strtol(curr_num_str, NULL, 10);
					free(curr_num_str);
					curr_num_str = malloc(0);
					struct RangeMap new_range_map = {
						curr_depth,
						curr_dest_start,
						curr_src_start,
						curr_range
					};
					range_maps_size += 1;
					struct RangeMap* new_range_maps = realloc(range_maps, range_maps_size * sizeof(struct RangeMap));
					new_range_maps[range_maps_size - 1] = new_range_map;
					range_maps = new_range_maps;

					curr_dest_start = -1;
					curr_src_start = -1;
					curr_range = -1;
				}
			}
		}
	}

	int64_t lowest_location = -1;
	for (int i = 0; i < seeds_size; i++) {
		struct SeedRange seed_range = seeds[i];
		int64_t seed_range_start = seed_range.start;
		int64_t seed_range_end = seed_range.start + seed_range.range - 1;

		for (int64_t x = seed_range_start; x <= seed_range_end; x++) {
			int64_t curr_mapping = x;
			int found_in_depth = 0;
			int curr_depth = 1;
			for (int j = 0; j < range_maps_size; j++) {
				struct RangeMap range_map = range_maps[j];
				if (range_map.depth != curr_depth) {
					found_in_depth = 0;
					curr_depth += 1;
				}
				if (found_in_depth == 0) {
					int64_t src_end = range_map.src_start + range_map.range - 1;
					if (curr_mapping >= range_map.src_start && curr_mapping <= src_end) {
						// printf("Mapping: %lld, Depth: %i, DStart: %lld, SStart: %lld, Range: %lld\n", curr_mapping, range_map.depth, range_map.dest_start, range_map.src_start, range_map.range);
						curr_mapping = range_map.dest_start + (curr_mapping - range_map.src_start);
						found_in_depth = 1;
					}
				}
			}
			// printf("Final Location: %lld\n", curr_mapping);
			if (lowest_location == -1 || curr_mapping < lowest_location) {
				lowest_location = curr_mapping;
			}
		}
	}
	printf("%lld", lowest_location);
	return 0;
}
