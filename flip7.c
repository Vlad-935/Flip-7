#include "cards.h"
#include "hit.h"
#include "player.h"

void game_round(int player_count, deck cards, Players *player)
{
	int players_turn = 1;
	while (player_count) {
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
					player_count--;
					break;
				default:
					printf("Optiune inexistenta, incercati din nou.\n");
					players_turn--;
			}
		}
		players_turn++;
	}
}

void game(int player_count, deck cards, Players player)
{
	bool winner = false;

	while (!winner) {
		int active_players = player_count;
		while (active_players) {
			game_round(player_count, cards, &player);
			printf("Round ended!\n");
		}
	}
}

int main(void)
{
	int player_count;
	deck cards;

	fflush(stdout);
	card_setup(&cards);

	printf("Introduceti numarul de jucatori: ");
	scanf("%d", &player_count);

	Players player = player_setup(player_count);

	game(player_count, cards, player);

	return 0;
}