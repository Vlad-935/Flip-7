#include "hit.h"

void hit(deck cards[], Players player)
{
	int card = rand() % 22;

	if (!cards->total_nmb) {
		// Transfering the discard pile to the main pile if empty
		for (int i = 0; i < 22; i++) {
			cards->main[i] = cards->discard[i];
			cards->discard[i] = 0;
		}
	}

	if (cards->main[card] > 0) {
		cards->main[card]--;
		cards->total_nmb--;
	} else {
		hit(cards, player);	 // hit until finds a card
	}
}
