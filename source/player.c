#include "player.h"

#include <stdio.h>
#include <stdlib.h>

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