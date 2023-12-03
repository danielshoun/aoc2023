#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../compat/compat.h"

struct NumCoord {
    int min_x_coord;
    int max_x_coord;
    int y_coord;
    int num;
};

struct SymbolCoord {
    int x_coord;
    int y_coord;
};

int day3part1() {
    int c;
    int curr_x_coord = 0;
    int curr_y_coord = 0;
    char* curr_num_str = malloc(0);
    int num_coords_size = 0;
    struct NumCoord* num_coords = malloc(0);
    int symbol_coords_size = 0;
    struct SymbolCoord* symbol_coords = malloc(0);


    FILE* file;
    fopen_s(&file, "./day3/input.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF) {
            if (isdigit(c)) {
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
                if (strlen(curr_num_str) > 0) {
                    int curr_num = strtol(curr_num_str, NULL, 10);
                    struct NumCoord new_num_coord = {
                        curr_x_coord - (int) strlen(curr_num_str),
                        curr_x_coord - 1,
                        curr_y_coord,
                        curr_num
                    };
                    num_coords_size += 1;
                    struct NumCoord* new_num_coords = realloc(num_coords, num_coords_size * sizeof(struct NumCoord));
                    new_num_coords[num_coords_size - 1] = new_num_coord;
                    num_coords = new_num_coords;

                    free(curr_num_str);
                    curr_num_str = malloc(0);
                }

                if (c == '\n') {
                    curr_y_coord += 1;
                    curr_x_coord = -1;
                } else if (c != '.') {
                    struct SymbolCoord new_symbol_coord = {
                        curr_x_coord,
                        curr_y_coord
                    };
                    symbol_coords_size += 1;
                    struct SymbolCoord* new_symbol_coords = realloc(symbol_coords,
                                                                    symbol_coords_size * sizeof(struct SymbolCoord));
                    new_symbol_coords[symbol_coords_size - 1] = new_symbol_coord;
                    symbol_coords = new_symbol_coords;
                }
            }
            curr_x_coord += 1;
        }
    }

    int sum = 0;
    for (int i = 0; i < symbol_coords_size; i++) {
        struct SymbolCoord symbol_coord = symbol_coords[i];
        for (int j = 0; j < num_coords_size; j++) {
            struct NumCoord num_coord = num_coords[j];
            if (
                (symbol_coord.y_coord - 1 <= num_coord.y_coord && num_coord.y_coord <= symbol_coord.y_coord + 1) &&
                (symbol_coord.x_coord >= num_coord.min_x_coord - 1 && symbol_coord.x_coord <= num_coord.max_x_coord + 1)
            ) {
                sum += num_coord.num;
            }
        }
    }
    free(num_coords);
    free(symbol_coords);
    free(curr_num_str);
    printf("%i", sum);
    return 0;
}

int day3part2() {
    int c;
    int curr_x_coord = 0;
    int curr_y_coord = 0;
    char* curr_num_str = malloc(0);
    int num_coords_size = 0;
    struct NumCoord* num_coords = malloc(0);
    int symbol_coords_size = 0;
    struct SymbolCoord* symbol_coords = malloc(0);


    FILE* file;
    fopen_s(&file, "./day3/input.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF) {
            if (isdigit(c)) {
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
                if (strlen(curr_num_str) > 0) {
                    int curr_num = strtol(curr_num_str, NULL, 10);
                    struct NumCoord new_num_coord = {
                        curr_x_coord - (int) strlen(curr_num_str),
                        curr_x_coord - 1,
                        curr_y_coord,
                        curr_num
                    };
                    num_coords_size += 1;
                    struct NumCoord* new_num_coords = realloc(num_coords, num_coords_size * sizeof(struct NumCoord));
                    new_num_coords[num_coords_size - 1] = new_num_coord;
                    num_coords = new_num_coords;

                    free(curr_num_str);
                    curr_num_str = malloc(0);
                }

                if (c == '\n') {
                    curr_y_coord += 1;
                    curr_x_coord = -1;
                } else if (c == '*') {
                    struct SymbolCoord new_symbol_coord = {
                        curr_x_coord,
                        curr_y_coord
                    };
                    symbol_coords_size += 1;
                    struct SymbolCoord* new_symbol_coords = realloc(symbol_coords,
                                                                    symbol_coords_size * sizeof(struct SymbolCoord));
                    new_symbol_coords[symbol_coords_size - 1] = new_symbol_coord;
                    symbol_coords = new_symbol_coords;
                }
            }
            curr_x_coord += 1;
        }
    }

    int sum = 0;
    for (int i = 0; i < symbol_coords_size; i++) {
        struct SymbolCoord symbol_coord = symbol_coords[i];
        int num_adjacent = 0;
        int gear_ratio = 1;
        for (int j = 0; j < num_coords_size; j++) {
            struct NumCoord num_coord = num_coords[j];
            if (
                (symbol_coord.y_coord - 1 <= num_coord.y_coord && num_coord.y_coord <= symbol_coord.y_coord + 1) &&
                (symbol_coord.x_coord >= num_coord.min_x_coord - 1 && symbol_coord.x_coord <= num_coord.max_x_coord + 1)
            ) {
                num_adjacent += 1;
                gear_ratio *= num_coord.num;
            }
        }
        if (num_adjacent == 2) {
            sum += gear_ratio;
        }
    }

    free(num_coords);
    free(symbol_coords);
    free(curr_num_str);
    printf("%i", sum);
    return 0;
}
