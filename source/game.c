#include "game.h"

#include <stdbool.h>
#include <stdio.h>

#include "utils.h"

void new_round_setup(round_state *round, Players *player)
{
	// Round related
	round->flip7 = false;
	round->players_turn = 1;
	round->active_players = round->player_count;

	// Player related
	for (int i = 1; i <= round->player_count; i++) {
		player[i].in_game = true;
		player[i].busted = false;

		for (int j = 0; j < diff_cards; j++) {
			player[i].cards_in_hand[j] = 0;
		}
		player[i].total_cards = 0;
		player[i].different_cards = 0;
	}
}

void end_round(int player_count, deck *cards, Players *player)
{
	for (int i = 1; i <= player_count; i++) {
		for (int j = 0; j < diff_cards; j++) {
			cards->discard[j] += player[i].cards_in_hand[j];
			cards->dicard_nmb += player[i].cards_in_hand[j];
		}
	}

	for (int i = 1; i <= player_count; i++) {
		int round_points = calculate_points(player[i]);
		player[i].total_points += round_points;

		player[i].in_game = false;
	}
}

void make_choice(round_state *round, deck *cards, Players *player)
{
	show_player_cards(player[round->players_turn]);

	int option;
	printf("Hit/Stay\n");
	scanf("%d", &option);

	switch (option) {
		case 1:	 // hit
			hit(cards, &player[round->players_turn]);

			bool busted;
			busted = bust(&player[round->players_turn]);

			if (busted) {
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

	end_round(round.player_count, cards, player);
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
