#ifndef CARDS
#define CARDS

#include "player.h"

// All the specials cards (action/bonus)
enum cards {
	freeze = 13,
	second_chance,
	flip_three,
	plus_two,
	plus_four,
	plus_six,
	plus_eight,
	plus_ten,
	times_two
};

typedef struct {
	int main[22], discard[22];
	int total_nmb, dicard_nmb;
} deck;

void card_setup(deck *cards);

void reshuffle_deck(deck *cards);

void hit(deck *cards, Players *player);

#endif