#include "player.h"

#include <stdio.h>
#include <stdlib.h>

#include "deck.h"

// Sets everything to 0 for every player
Players *player_setup(int player_count)
{
	Players *player = calloc(player_count + 1, sizeof(Players));

	for (int i = 1; i <= player_count; i++) {
		player[i].in_game = true;
		player[i].round_points = 0;
		player[i].total_points = 0;
		player[i].different_cards = 0;
		player[i].total_cards = 0;

		for (int j = 0; j <= 21; j++) {
			player[i].cards_in_hand[j] = 0;
		}
	}

	return player;
}

bool update_bust_state(Players *player)
{
	int diff_cards = 13;
	for (int i = 0; i < diff_cards; i++) {
		if (player->cards_in_hand[i] > 1) {
			player->in_game = false;
			player->round_points = 0;

			return true;
		}
	}

	return false;
}

void show_player_cards(Players player)
{
	bool printed;

	// Number cards
	printed = false;
	for (int i = 0; i <= 12; i++) {
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
		printf("Freeze x%d ", player.cards_in_hand[freeze]);
		printed = true;
	}
	if (player.cards_in_hand[second_chance] > 0) {
		printf("Second Chance x%d ", player.cards_in_hand[second_chance]);
		printed = true;
	}
	if (player.cards_in_hand[flip_three] > 0) {
		printf("Flip Three x%d ", player.cards_in_hand[flip_three]);
		printed = true;
	}
	if (printed) {
		printf("\n");
	}

	// Special cards
	printed = false;
	if (player.cards_in_hand[plus_two] == 1) {
		printf("+2 ");
		printed = true;
	}
	if (player.cards_in_hand[plus_four] == 1) {
		printf("+4 ");
		printed = true;
	}
	if (player.cards_in_hand[plus_six] == 1) {
		printf("+6 ");
		printed = true;
	}
	if (player.cards_in_hand[plus_eight] == 1) {
		printf("+8 ");
		printed = true;
	}
	if (player.cards_in_hand[plus_ten] == 1) {
		printf("+10 ");
		printed = true;
	}
	if (player.cards_in_hand[times_two] == 1) {
		printf("x2 ");
		printed = true;
	}
	if (printed) {
		printf("\n");
	}
}