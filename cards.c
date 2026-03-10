#include "cards.h"

// fac setupul de carti la inceput
// gen fac deckul, intializez numarul de carti
void card_setup(deck *cards)
{
	cards->total_nmb = 94;

	cards->main[0] = 1;
	for (int i = 1; i <= 12; i++) {
		cards->main[i] = i;
	}

	for (int i = 13; i <= 15; i++) {
		cards->main[i] = 3;
	}

	for (int i = 16; i <= 21; i++) {
		cards->main[i] = 1;
	}

	for (int i = 0; i <= 21; i++) {
		cards->discard[i] = 0;
	}

	return;
}