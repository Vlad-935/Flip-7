#include "cards.h"

// fac setupul de carti la inceput
// gen fac deckul, intializez numarul de carti
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
	for (int i = 16; i <= 21; i++) {
		cards->main[i] = special_cards_nmb;
	}

	int empty = 0;
	for (int i = 0; i <= 21; i++) {
		cards->discard[i] = empty;
	}
}