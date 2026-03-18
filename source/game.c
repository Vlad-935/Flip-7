#include "game.h"

#include <stdbool.h>
#include <stdio.h>

#include "utils.h"

void bust(deck *cards, Players *player)
{
	// Searching for duplicate number card
	int duplicate = -1;
	for (int i = 0; i < number_cards; i++) {
		if (player->cards_in_hand[i] > 1) {
			duplicate = i;
			break;
		}
	}

	// Stops if player didn't bust
	if (duplicate == -1) {
		return;
	}

	update_bust_state(duplicate, player);  // Set player as busted if they have 2 dublicates

	// Checks to see if player had second chance
	if (player->busted) {
		clear_screen();
		printf("Player %d busted!\n", player->id);
		delay_ms(text_time);
	} else {
		cards->discard[duplicate]++;
		cards->discard[second_chance]++;
		cards->dicard_nmb += 2;

		clear_screen();
		printf("Player %d used second chance!\n", player->id);
		delay_ms(text_time);
	}
}

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
	show_player_cards(*player);

	int option;
	if ((*player).total_cards) {
		printf("Hit(1)/Stay(2)\n");
		scanf("%d", &option);
	} else {
		// First draw is automated
		option = 1;
	}

	switch (option) {
		case 1:	 // Hit
			hit(cards, &(*player));
			bust(cards, &(*player));

			break;
		case 2:	 // Stay
			(*player).in_game = false;

			break;
		default:  // Error
			clear_screen();
			printf("Not an option, try again.\n");
			delay_ms(text_time);

			round->players_turn--;
	}

	if (!(*player).in_game) {
		round->active_players--;
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
			make_choice(&round, cards, &player[round.players_turn]);
		}

		if (player[round.players_turn].different_cards == 7) {
			round.flip7 = true;

			clear_screen();
			printf("Player %d got FLIP7!\n", round.players_turn);
			delay_ms(text_time);
		}

		round.players_turn++;
	}

	end_round(round.player_count, cards, player);
}

bool check_winner(round_state round, Players *player)
{
	int max_points = 0,
		max_count = 1,
		player_id;
	for (int i = 1; i <= round.player_count; i++) {
		if (player[i].total_points > max_points) {
			max_points = player[i].total_points;
			max_count = 1;

			player_id = i;
		} else if (player[i].total_points == max_points) {
			max_count++;
		}
	}

	int points_needed_to_win = 200;
	if (max_points > points_needed_to_win) {
		if (max_count == 1) {
			clear_screen();
			printf(
				"Player %d won!\n"
				"Points: %d\n",
				player_id, max_points);
			delay_ms(text_time);

			return 1;
		} else {
			clear_screen();
			printf(
				"It's a tie!\n"
				"Continue playing until someone wins!\n");
			delay_ms(text_time);
		}
	}

	return 0;
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

		winner = check_winner(round, player);
	}

	printf("\n");
	for (int i = 1; i <= round.player_count; i++) {
		printf("Player %d: %d points\n", i, player[i].total_points);
	}

	printf("Game Ended!\n");
}
