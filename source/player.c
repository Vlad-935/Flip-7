#include "player.h"

#include <stdio.h>
#include <stdlib.h>

#include "colors.h"
#include "deck.h"
#include "utils.h"

// Sets everything to 0 for every player
Players *player_setup(int player_count)
{
	Players *player = calloc(player_count + 1, sizeof(Players));

	for (int i = 1; i <= player_count; i++) {
		player[i].id = i;

		player[i].in_game = true;
		player[i].busted = false;

		player[i].total_points = 0;

		player[i].total_cards = 0;
		player[i].different_cards = 0;

		for (int j = 0; j < diff_cards; j++) {
			player[i].cards_in_hand[j] = 0;
		}
	}

	return player;
}

void update_bust_state(int duplicate, Players *player)
{
	if (player->cards_in_hand[second_chance] > 0) {
		player->cards_in_hand[second_chance]--;
		player->cards_in_hand[duplicate]--;
		player->total_cards -= 2;
	} else {
		player->in_game = false;
		player->busted = true;
	}
}

void show_player_cards(Players player)
{
	clear_screen();
	printf(
		"Player %d:\n"
		"Points: %d\n",
		player.id, player.total_points);

	if (player.total_cards > 0) {
		printf("Current Cards: \n");
	}

	bool printed;

	// Number cards
	printed = false;
	for (int i = 0; i < number_cards; i++) {
		if (player.cards_in_hand[i] > 0) {
			printf("%d ", i);
			printed = true;
		}
	}
	if (printed) {
		printf("\n");
	}

	// Action cards
	printed = false;
	if (player.cards_in_hand[freeze] > 0) {
		printf(CYAN "Freeze" RESET
					"x%d ",
			   player.cards_in_hand[freeze]);
		printed = true;
	}
	if (player.cards_in_hand[second_chance] > 0) {
		printf(RED "Second Chance" RESET
				   " x%d ",
			   player.cards_in_hand[second_chance]);
		printed = true;
	}
	if (player.cards_in_hand[flip_three] > 0) {
		printf(YELLOW "Flip Three" RESET
					  " x%d ",
			   player.cards_in_hand[flip_three]);
		printed = true;
	}
	if (printed) {
		printf("\n");
	}

	// Special cards
	printed = false;
	if (player.cards_in_hand[plus_two] == 1) {
		printf(MAGENTA "+2 " RESET);
		printed = true;
	}
	if (player.cards_in_hand[plus_four] == 1) {
		printf(MAGENTA "+4 " RESET);
		printed = true;
	}
	if (player.cards_in_hand[plus_six] == 1) {
		printf(MAGENTA "+6 " RESET);
		printed = true;
	}
	if (player.cards_in_hand[plus_eight] == 1) {
		printf(MAGENTA "+8 " RESET);
		printed = true;
	}
	if (player.cards_in_hand[plus_ten] == 1) {
		printf(MAGENTA "+10 " RESET);
		printed = true;
	}
	if (player.cards_in_hand[times_two] == 1) {
		printf(MAGENTA "x2 " RESET);
		printed = true;
	}
	if (printed) {
		printf("\n");
	}
}

int calculate_points(Players player)
{
	int round_points = 0;

	if (player.busted) {
		return 0;
	}

	for (int i = 0; i < number_cards; i++) {
		if (player.cards_in_hand[i] > 0) {
			round_points += i;
		}
	}

	if (player.cards_in_hand[times_two] == 1) {
		round_points *= 2;
	}

	if (player.cards_in_hand[plus_two] == 1) {
		round_points += 2;
	}
	if (player.cards_in_hand[plus_four] == 1) {
		round_points += 4;
	}
	if (player.cards_in_hand[plus_six] == 1) {
		round_points += 6;
	}
	if (player.cards_in_hand[plus_eight] == 1) {
		round_points += 8;
	}
	if (player.cards_in_hand[plus_ten] == 1) {
		round_points += 10;
	}

	if (player.different_cards == 7) {
		round_points += 15;
	}

	return round_points;
}
