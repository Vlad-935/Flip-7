#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cards.h"
#include "player.h"

void game_round(int player_count, deck cards, Players *player)
{
	for (int i = 0; i < player_count; i++) {
		if (player[i].in_game) {
			int option;
			printf("Player %d: Hit/Stay\n", i + 1);
			scanf("%d", &option);

			if (option == 2) {	// stay
				player[i].in_game = false;
			} else {  // hit
			}
		}
	}
}

void game(int player_count, deck cards, Players player)
{
	bool winner = false;

	while (!winner) {
		int active_players = player_count;
		while (!active_players) {
			game_round(player_count, cards, &player);
		}
	}
}

int main(void)
{
	int player_count;
	deck cards;
	card_setup(&cards);

	printf("Introduceti numarul de jucatori: ");
	scanf("%d", &player_count);

	Players player = player_setup(player_count);

	game(player_count, cards, player);

	return 0;
}