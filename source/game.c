#include "game.h"

#include <stdbool.h>
#include <stdio.h>

#include "utils.h"

#define diff_cards 22
#define text_time 2000

void make_choice(round_state *round, deck *cards, Players *player)
{
	int option;

	clear_screen();
	printf(
		"Player %d:\n"
		"Points: %d\n"
		"Current cards:\n",
		round->players_turn, player[round->players_turn].total_points);
	show_player_cards(player[round->players_turn]);
	printf("Hit/Stay\n");

	scanf("%d", &option);

	switch (option) {
		case 1:	 // hit
			hit(cards, &player[round->players_turn]);

			update_bust_state(&player[round->players_turn]);  // Set player as busted if they have 2 dublicates
			if (player[round->players_turn].busted) {
				clear_screen();
				printf("Player %d busted!\n", round->players_turn);
				delay_ms(text_time);

				round->active_players--;
			}

			break;
		case 2:	 // stay
			player[round->players_turn].in_game = false;
			round->active_players--;

			break;
		default:  // error
			clear_screen();
			printf("Not an option, try again.\n");
			delay_ms(text_time);

			round->players_turn--;
	}
}

void new_round_setup(round_state *round, Players *player)
{
	round->flip7 = false;
	round->players_turn = 1;
	round->active_players = round->player_count;

	for (int i = 1; i <= round->player_count; i++) {
		player[i].in_game = true;
		player[i].busted = false;

		for (int j = 0; j < diff_cards; j++) {
			player[i].cards_in_hand[j] = 0;
		}
		player[i].total_cards = 0;
	}
}

void game_round(round_state round, deck *cards, Players *player)
{
	// New round
	new_round_setup(&round, player);

	// Play until everyone is out, or someone got a flip7
	while (round.active_players && !round.flip7) {
		if (round.players_turn > round.player_count) {
			round.players_turn = 1;
		}

		if (player[round.players_turn].in_game) {
			make_choice(&round, cards, player);
		}

		if (player[round.players_turn].different_cards == 7) {
			round.flip7 = true;
		}

		round.players_turn++;
	}

	end_round(round.player_count, player);
}

void game(round_state round, deck *cards, Players *player)
{
	bool winner = false;

	// Play until one person reaches 200 points
	while (!winner) {
		game_round(round, cards, player);

		clear_screen();
		printf("Round ended!\n");
		delay_ms(text_time);
	}

	printf(
		"Game Ended!\n"
		"Winner: Player %d",
		winner);
}
