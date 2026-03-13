#include "player.h"

#include <stdio.h>
#include <stdlib.h>

// initializare fiecare player
// se reseteaza totul la 0 si tot asa
Players *player_setup(int player_count)
{
	Players *player = calloc(player_count + 1, sizeof(Players));

	for (int i = 1; i <= player_count; i++) {
		player[i].in_game = true;
		player[i].round_points = 0;
		player[i].total_points = 0;
		player[i].different_cards = 0;
		player[i].total_cards = 0;

		for (int j = 0; j < 16; j++) {
			player[i].cards_in_hand[j] = 0;
		}
	}

	return player;
}