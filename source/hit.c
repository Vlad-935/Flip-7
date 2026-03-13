#include "hit.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void reshuffle_deck(deck *cards)
{
	if (!cards->total_nmb) {
		// Transfering the discard pile to the main pile if empty
		clear_screen();
		printf("Reshuffling deck, please wait.\n");
		delay_ms(2000);

		for (int i = 0; i < 22; i++) {
			cards->main[i] = cards->discard[i];
			cards->discard[i] = 0;
		}

		cards->total_nmb = cards->dicard_nmb;
		cards->dicard_nmb = 0;
	}
}

void hit(deck *cards, Players *player)
{
	int card = rand() % 22;
	printf("Card: %d\n", card);

	reshuffle_deck(cards);	// Verify if deck is empty and reshuffle it

	if (cards->main[card] > 0) {
		cards->main[card]--;
		cards->total_nmb--;

		cards->dicard_nmb++;
	} else {
		hit(cards, player);	 // hit until finds a card
	}

	player->total_cards++;
	player->cards_in_hand[card]++;
}
