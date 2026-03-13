#include "game.h"

#include <stdbool.h>
#include <stdio.h>

void game_round(int player_count, deck cards, Players *player)
{
	// new round
	int players_turn = 1;
	int active_players = player_count;
	for (int i = 1; i <= player_count; i++) {
		player[i].in_game = true;
	}
	// end reseting

	while (active_players) {
		if (players_turn > player_count) {
			players_turn = 1;
		}

		if (player[players_turn].in_game) {
			int option;

			printf("Player %d: Hit/Stay\n", players_turn);
			scanf("%d", &option);

			switch (option) {
				case 1:	 // hit
					hit(&cards, player[players_turn]);
					break;
				case 2:	 // stay
					player[players_turn].in_game = false;
					active_players--;
					break;
				default:
					printf("Optiune inexistenta, incercati din nou.\n");
					players_turn--;
			}
		}

		players_turn++;
	}
}

void game(int player_count, deck cards, Players *player)
{
	bool winner = false;

	while (!winner) {
		game_round(player_count, cards, player);
		printf("Round ended!\n");
	}

	printf(
		"Game Ended!\n"
		"Winner: Player %d",
		winner);
}
