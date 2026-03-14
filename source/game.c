#include "game.h"

#include <stdbool.h>
#include <stdio.h>

#include "utils.h"

#define diff_cards 22
#define text_time 2000

void make_choice(int *players_turn, int *active_players,
				 deck *cards, Players *player)
{
	int option;

	clear_screen();
	printf(
		"Player %d:\n"
		"Points: %d\n"
		"Current cards:\n",
		*players_turn, player[*players_turn].total_points);
	show_player_cards(player[*players_turn]);
	printf("Hit/Stay\n");

	scanf("%d", &option);

	switch (option) {
		case 1:	 // hit
			hit(cards, &player[*players_turn]);

			update_bust_state(&player[*players_turn]);
			if (player[*players_turn].busted) {
				clear_screen();
				printf("Player %d busted!\n", *players_turn);
				delay_ms(text_time);

				(*active_players)--;
			}

			break;
		case 2:	 // stay
			player[*players_turn].in_game = false;
			(*active_players)--;

			break;
		default:  // error
			clear_screen();
			printf("Not an option, try again.\n");
			delay_ms(text_time);

			(*players_turn)--;
	}
}

void new_round_setup(int player_count, Players *player)
{
	for (int i = 1; i <= player_count; i++) {
		player[i].in_game = true;
		player[i].busted = false;

		for (int j = 0; j < diff_cards; j++) {
			player[i].cards_in_hand[j] = 0;
		}
	}
}

void game_round(int player_count, deck *cards, Players *player)
{
	// New round
	int players_turn = 1, active_players = player_count;
	bool flip7 = false;
	new_round_setup(player_count, player);

	// Play until everyone is out, or someone got a flip7
	while (active_players && !flip7) {
		if (players_turn > player_count) {
			players_turn = 1;
		}

		if (player[players_turn].in_game) {
			make_choice(&players_turn, &active_players,
						cards, player);
		}

		if (player[players_turn].different_cards == 7) {
			flip7 = true;
		}

		players_turn++;
	}

	end_round(player_count, player);
}

void game(int player_count, deck *cards, Players *player)
{
	bool winner = false;

	// Play until one person reaches 200 points
	while (!winner) {
		game_round(player_count, cards, player);

		clear_screen();
		printf("Round ended!\n");
		delay_ms(text_time);
	}

	printf(
		"Game Ended!\n"
		"Winner: Player %d",
		winner);
}
