#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../compat/compat.h"

struct HandBet {
	char* hand;
	int bet;
};

char* card_rankings_part_1 = "23456789TJQKA";
char* card_rankings_part_2 = "J23456789TQKA";

int compare_part_1(const void* a, const void* b) {
	char* a_hand = (*((struct HandBet *) a)).hand;
	char* b_hand = (*((struct HandBet *) b)).hand;

	int num_diff_a_hand_cards = 0;
	char cards_in_a_hand[] = "\0\0\0\0\0\0";
	int num_card_occurrences_a[] = {0, 0, 0, 0, 0};

	int num_diff_b_hand_cards = 0;
	char cards_in_b_hand[] = "\0\0\0\0\0\0";
	int num_card_occurrences_b[] = {0, 0, 0, 0, 0};

	int highest_a_rank = 0;
	int highest_b_rank = 0;

	// 1 if A hand outranks, -1 if B hand outranks.
	int hand_that_outranks = 0;

	for (int i = 0; i < 5; i++) {
		char a_hand_char = a_hand[i];
		char b_hand_char = b_hand[i];

		int j;
		for (j = 0; j < num_diff_a_hand_cards; j++) {
			if (a_hand_char == cards_in_a_hand[j]) {
				num_card_occurrences_a[j] += 1;
				break;
			}
		}
		if (j == num_diff_a_hand_cards) {
			num_diff_a_hand_cards += 1;
			cards_in_a_hand[num_diff_a_hand_cards - 1] = a_hand_char;
			num_card_occurrences_a[num_diff_a_hand_cards - 1] = 1;
		}

		for (j = 0; j < num_diff_b_hand_cards; j++) {
			if (b_hand_char == cards_in_b_hand[j]) {
				num_card_occurrences_b[j] += 1;
				break;
			}
		}
		if (j == num_diff_b_hand_cards) {
			num_diff_b_hand_cards += 1;
			cards_in_b_hand[num_diff_b_hand_cards - 1] = b_hand_char;
			num_card_occurrences_b[num_diff_b_hand_cards - 1] = 1;
		}

		int a_char_rank = strchr(card_rankings_part_1, a_hand_char) - card_rankings_part_1;
		int b_char_rank = strchr(card_rankings_part_1, b_hand_char) - card_rankings_part_1;

		if (a_char_rank > highest_a_rank) highest_a_rank = a_char_rank;
		if (b_char_rank > highest_b_rank) highest_b_rank = b_char_rank;

		if (hand_that_outranks == 0) {
			if (a_char_rank > b_char_rank) {
				hand_that_outranks = 1;
			} else if (b_char_rank > a_char_rank) {
				hand_that_outranks = -1;
			}
		}
	}

	if (num_diff_a_hand_cards < num_diff_b_hand_cards) {
		return 1;
	}
	if (num_diff_b_hand_cards < num_diff_a_hand_cards) {
		return -1;
	}

	// 1 if A has highest occurrence, -1 if B has highest occurrence.
	int hand_with_highest_occurrence = 0;
	int highest_occurrence = 0;
	for (int i = 0; i < num_diff_a_hand_cards; i++) {
		int a_occurrence = num_card_occurrences_a[i];
		int b_occurence = num_card_occurrences_b[i];

		if (a_occurrence > highest_occurrence) {
			highest_occurrence = a_occurrence;
			hand_with_highest_occurrence = 1;
		} else if (a_occurrence == highest_occurrence && hand_with_highest_occurrence == -1) {
			hand_with_highest_occurrence = 0;
		}
		if (b_occurence > highest_occurrence) {
			highest_occurrence = b_occurence;
			hand_with_highest_occurrence = -1;
		} else if (b_occurence == highest_occurrence && hand_with_highest_occurrence == 1) {
			hand_with_highest_occurrence = 0;
		}
	}

	if (hand_with_highest_occurrence != 0) {
		return hand_with_highest_occurrence;
	}

	return hand_that_outranks;
}

int compare_part_2(const void* a, const void* b) {
	char* a_hand = (*((struct HandBet *) a)).hand;
	char* b_hand = (*((struct HandBet *) b)).hand;

	int num_diff_a_hand_cards = 0;
	char cards_in_a_hand[] = "\0\0\0\0\0\0";
	int num_card_occurrences_a[] = {0, 0, 0, 0, 0};
	int a_num_jokers = 0;

	int num_diff_b_hand_cards = 0;
	char cards_in_b_hand[] = "\0\0\0\0\0\0";
	int num_card_occurrences_b[] = {0, 0, 0, 0, 0};
	int b_num_jokers = 0;

	int highest_a_rank = 0;
	int highest_b_rank = 0;

	// 1 if A hand outranks, -1 if B hand outranks.
	int hand_that_outranks = 0;

	for (int i = 0; i < 5; i++) {
		char a_hand_char = a_hand[i];
		char b_hand_char = b_hand[i];

		int j;
		for (j = 0; j < num_diff_a_hand_cards; j++) {
			if (a_hand_char == cards_in_a_hand[j]) {
				num_card_occurrences_a[j] += 1;
				break;
			}
		}
		if (j == num_diff_a_hand_cards && a_hand_char != 'J') {
			num_diff_a_hand_cards += 1;
			cards_in_a_hand[num_diff_a_hand_cards - 1] = a_hand_char;
			num_card_occurrences_a[num_diff_a_hand_cards - 1] = 1;
		}
		if (a_hand_char == 'J') {
			a_num_jokers += 1;
		}

		for (j = 0; j < num_diff_b_hand_cards; j++) {
			if (b_hand_char == cards_in_b_hand[j]) {
				num_card_occurrences_b[j] += 1;
				break;
			}
		}
		if (j == num_diff_b_hand_cards && b_hand_char != 'J') {
			num_diff_b_hand_cards += 1;
			cards_in_b_hand[num_diff_b_hand_cards - 1] = b_hand_char;
			num_card_occurrences_b[num_diff_b_hand_cards - 1] = 1;
		}
		if (b_hand_char == 'J') {
			b_num_jokers += 1;
		}

		int a_char_rank = strchr(card_rankings_part_2, a_hand_char) - card_rankings_part_2;
		int b_char_rank = strchr(card_rankings_part_2, b_hand_char) - card_rankings_part_2;

		if (a_char_rank > highest_a_rank) highest_a_rank = a_char_rank;
		if (b_char_rank > highest_b_rank) highest_b_rank = b_char_rank;

		if (hand_that_outranks == 0) {
			if (a_char_rank > b_char_rank) {
				hand_that_outranks = 1;
			} else if (b_char_rank > a_char_rank) {
				hand_that_outranks = -1;
			}
		}
	}

	if (num_diff_a_hand_cards < num_diff_b_hand_cards && num_diff_a_hand_cards != 0) {
		return 1;
	}
	if (num_diff_b_hand_cards < num_diff_a_hand_cards && num_diff_b_hand_cards != 0) {
		return -1;
	}

	// 1 if A has highest occurrence, -1 if B has highest occurrence.
	int hand_with_highest_occurrence = 0;
	int highest_occurrence = 0;
	for (int i = 0; i < 5; i++) {
		int a_occurrence = num_card_occurrences_a[i] + a_num_jokers;
		int b_occurence = num_card_occurrences_b[i] + b_num_jokers;

		if (a_occurrence > highest_occurrence) {
			highest_occurrence = a_occurrence;
			hand_with_highest_occurrence = 1;
		} else if (a_occurrence == highest_occurrence && hand_with_highest_occurrence == -1) {
			hand_with_highest_occurrence = 0;
		}
		if (b_occurence > highest_occurrence) {
			highest_occurrence = b_occurence;
			hand_with_highest_occurrence = -1;
		} else if (b_occurence == highest_occurrence && hand_with_highest_occurrence == 1) {
			hand_with_highest_occurrence = 0;
		}
	}

	if (hand_with_highest_occurrence != 0) {
		return hand_with_highest_occurrence;
	}

	return hand_that_outranks;
}

int day7part1() {
	int c;
	char* curr_str = malloc(0);
	char* curr_hand;
	int hand_bets_size = 0;
	struct HandBet* hand_bets = malloc(0);

	FILE* file;
	fopen_s(&file, "./day7/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (c == ' ') {
				curr_hand = curr_str;
				curr_str = malloc(0);
			} else if (c == '\n') {
				int bet = strtol(curr_str, NULL, 10);
				struct HandBet new_hand_bet = {
					curr_hand,
					bet
				};

				hand_bets_size += 1;
				struct HandBet* new_hand_bets = realloc(hand_bets, hand_bets_size * sizeof(struct HandBet));
				new_hand_bets[hand_bets_size - 1] = new_hand_bet;
				hand_bets = new_hand_bets;

				free(curr_str);
				curr_str = malloc(0);
			} else {
				size_t curr_str_len = strlen(curr_str);
				char* new_str = malloc(curr_str_len + 1 + 1);
				strcpy_s(new_str, curr_str_len + 1, curr_str);
				new_str[curr_str_len] = c;
				new_str[curr_str_len + 1] = '\0';
				free(curr_str);
				curr_str = malloc(strlen(new_str) + 1);
				strcpy_s(curr_str, strlen(new_str) + 1, new_str);
				free(new_str);
			}
		}
	}

	qsort(hand_bets, hand_bets_size, sizeof(struct HandBet), compare_part_1);

	int sum = 0;
	for (int i = 0; i < hand_bets_size; i++) {
		struct HandBet hand_bet = hand_bets[i];
		sum += hand_bets[i].bet * (i + 1);
		printf("Hand: %s, Bet: %i, Sum: %i\n", hand_bet.hand, hand_bet.bet, sum);
	}

	printf("%i", sum);
	return 0;
}

int day7part2() {
	int c;
	char* curr_str = malloc(0);
	char* curr_hand;
	int hand_bets_size = 0;
	struct HandBet* hand_bets = malloc(0);

	FILE* file;
	fopen_s(&file, "./day7/input.txt", "r");
	if (file) {
		while ((c = getc(file)) != EOF) {
			if (c == ' ') {
				curr_hand = curr_str;
				curr_str = malloc(0);
			} else if (c == '\n') {
				int bet = strtol(curr_str, NULL, 10);
				struct HandBet new_hand_bet = {
					curr_hand,
					bet
				};

				hand_bets_size += 1;
				struct HandBet* new_hand_bets = realloc(hand_bets, hand_bets_size * sizeof(struct HandBet));
				new_hand_bets[hand_bets_size - 1] = new_hand_bet;
				hand_bets = new_hand_bets;

				free(curr_str);
				curr_str = malloc(0);
			} else {
				size_t curr_str_len = strlen(curr_str);
				char* new_str = malloc(curr_str_len + 1 + 1);
				strcpy_s(new_str, curr_str_len + 1, curr_str);
				new_str[curr_str_len] = c;
				new_str[curr_str_len + 1] = '\0';
				free(curr_str);
				curr_str = malloc(strlen(new_str) + 1);
				strcpy_s(curr_str, strlen(new_str) + 1, new_str);
				free(new_str);
			}
		}
	}

	qsort(hand_bets, hand_bets_size, sizeof(struct HandBet), compare_part_2);

	int sum = 0;
	for (int i = 0; i < hand_bets_size; i++) {
		struct HandBet hand_bet = hand_bets[i];
		sum += hand_bets[i].bet * (i + 1);
		printf("Hand: %s, Bet: %i, Sum: %i\n", hand_bet.hand, hand_bet.bet, sum);
	}

	printf("%i", sum);
	return 0;
}
