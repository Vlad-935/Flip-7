#include "game.h"

#include <stdbool.h>
#include <stdio.h>

#include "utils.h"

#define time 3000

void show_cards(Players player)
{
	// Number cards
	for (int i = 0; i <= 12; i++) {
		if (player.cards_in_hand[i] > 0) {
			printf("%d ", i);
		}
	}
	printf("\n");

	// Action cards
	if (player.cards_in_hand[freeze] > 0) {
		printf("Freeze x%d ", player.cards_in_hand[freeze]);
	}
	if (player.cards_in_hand[second_chance] > 0) {
		printf("Second Chance x%d ", player.cards_in_hand[second_chance]);
	}
	if (player.cards_in_hand[flip_three] > 0) {
		printf("Flip Three x%d ", player.cards_in_hand[flip_three]);
	}
	printf("\n");

	// Special cards
	if (player.cards_in_hand[plus_two] == 1) {
		printf("+2 ");
	}
	if (player.cards_in_hand[plus_four] == 1) {
		printf("+4 ");
	}
	if (player.cards_in_hand[plus_six] == 1) {
		printf("+6 ");
	}
	if (player.cards_in_hand[plus_eight] == 1) {
		printf("+8 ");
	}
	if (player.cards_in_hand[plus_ten] == 1) {
		printf("+10 ");
	}
	if (player.cards_in_hand[times_two] == 1) {
		printf("x2 ");
	}
	printf("\n");
}

void make_choice(int players_turn, int active_players,
				 deck cards, Players *player)
{
	int option;

	clear_screen();
	printf("Player %d: Hit/Stay\n", players_turn);
	show_cards(player[players_turn]);
	scanf("%d", &option);

	switch (option) {
		case 1:	 // hit
			hit(&cards, &player[players_turn]);

			bool busted = update_bust_state(&player[players_turn]);
			if (busted) {
				clear_screen();
				printf("Player %d busted!\n", players_turn);
				delay_ms(time);

				active_players--;
			}

			break;
		case 2:	 // stay
			player[players_turn].in_game = false;
			active_players--;

			break;
		default:
			clear_screen();
			printf("Not an option, try again.\n");
			delay_ms(time);

			players_turn--;
	}
}

void game_round(int player_count, deck cards, Players *player)
{
	// New round
	int players_turn = 1, active_players = player_count;
	bool flip7 = false;
	for (int i = 1; i <= player_count; i++) {
		player[i].in_game = true;
	}

	while (active_players && !flip7) {
		if (players_turn > player_count) {
			players_turn = 1;
		}

		if (player[players_turn].in_game) {
			make_choice(players_turn, active_players,
						cards, player);
		}

		players_turn++;
	}
}

void game(int player_count, deck cards, Players *player)
{
	bool winner = false;

	while (!winner) {
		game_round(player_count, cards, player);

		clear_screen();
		printf("Round ended!\n");
		delay_ms(time);
	}

	printf(
		"Game Ended!\n"
		"Winner: Player %d",
		winner);
}
