#include "deck.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define diff_cards 22
#define text_time 2000

// Sets the number of every card in the deck
void card_setup(deck *cards)
{
	cards->total_nmb = 94;
	cards->dicard_nmb = 0;

	cards->main[0] = 1;	 // special number 0
	for (int i = 1; i <= 12; i++) {
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

void hit(deck *cards, Players *player)
{
	reshuffle_deck(cards);	// Verify if deck is empty and reshuffle it

	int card;

	do {
		card = rand() % diff_cards;	 // Searches an avaiable card
	} while (cards->main[card] == 0);

	printf("Card: %d\n", card);
	delay_ms(text_time);

	cards->main[card]--;
	cards->total_nmb--;

	cards->discard[card]++;
	cards->dicard_nmb++;

	player->cards_in_hand[card]++;
}
