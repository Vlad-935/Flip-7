#include "deck.h"

#include <stdio.h>
#include <stdlib.h>

#include "colors.h"
#include "game.h"
#include "utils.h"

// Sets the number of every card in the deck
void card_setup(deck *cards)
{
	cards->total_nmb = 94;
	cards->dicard_nmb = 0;

	cards->main[0] = 1;	 // special number 0
	for (int i = 1; i < number_cards; i++) {
		cards->main[i] = i;
	}

	int action_cards_nmb = 3;
	cards->main[freeze] = action_cards_nmb;
	cards->main[second_chance] = action_cards_nmb;
	cards->main[flip_three] = action_cards_nmb;

	int special_cards_nmb = 1;
	for (int i = 16; i < diff_cards; i++) {
		cards->main[i] = special_cards_nmb;
	}

	int empty = 0;
	for (int i = 0; i < diff_cards; i++) {
		cards->discard[i] = empty;
	}
}

void show_card(int card)
{
	printf("Card: ");

	// Number cards
	if (card < number_cards) {
		printf("%d\n", card);
	}

	// Action cards
	if (card == freeze) {
		printf(CYAN "Freeze\n" RESET);
	}
	if (card == second_chance) {
		printf(RED "Second Chance\n" RESET);
	}
	if (card == flip_three) {
		printf(YELLOW "Flip Three\n" RESET);
	}

	// Bonus cards
	if (card == plus_two) {
		printf(MAGENTA "+2\n" RESET);
	}
	if (card == plus_four) {
		printf(MAGENTA "+4\n" RESET);
	}
	if (card == plus_six) {
		printf(MAGENTA "+6\n" RESET);
	}
	if (card == plus_eight) {
		printf(MAGENTA "+8\n" RESET);
	}
	if (card == plus_ten) {
		printf(MAGENTA "+10\n" RESET);
	}
	if (card == times_two) {
		printf(MAGENTA "x2\n" RESET);
	}

	delay_ms(text_time);
}

void reshuffle_deck(deck *cards)
{
	if (!cards->total_nmb) {
		// Transfering the discard pile to the main pile if empty
		clear_screen();
		printf("Reshuffling deck, please wait.\n");
		delay_ms(text_time);

		for (int i = 0; i < diff_cards; i++) {
			cards->main[i] = cards->discard[i];
			cards->discard[i] = 0;
		}

		cards->total_nmb = cards->dicard_nmb;
		cards->dicard_nmb = 0;
	}
}

void action_cards(int card, deck *cards, Players *player)
{
	if (card == freeze) {
		if (player->total_cards > 1) {
			player->in_game = false;

			clear_screen();
			printf("Player %d is out: "	 //
				   CYAN "Freeze" RESET
				   "!\n",
				   player->id);
			delay_ms(text_time);
		} else {
			player->cards_in_hand[freeze]--;
			player->total_cards--;

			cards->discard[freeze]++;
			cards->dicard_nmb++;

			printf(CYAN "Freeze" RESET
						" as first card. Redrawing card.\n");
			delay_ms(text_time);

			hit(cards, player);
		}
	}

	if (card == flip_three) {
		for (int i = 0; i < 3 && player->in_game; i++) {
			hit(cards, player);
			bust(cards, player);
		}
	}
}

void hit(deck *cards, Players *player)
{
	reshuffle_deck(cards);	// Reshuffles the deck if empty

	int card;

	do {
		card = rand() % diff_cards;	 // Searches for an available card
	} while (cards->main[card] == 0);

	show_card(card);

	cards->main[card]--;
	cards->total_nmb--;

	player->cards_in_hand[card]++;
	player->total_cards++;
	if (card < number_cards && player->cards_in_hand[card] == 1) {
		player->different_cards++;
	}

	action_cards(card, cards, player);
}
