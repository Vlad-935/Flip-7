#ifndef CARDS
#define CARDS

#include "player.h"

#define number_cards 13
#define diff_cards 22

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
	int main[diff_cards], discard[diff_cards];
	int total_nmb, dicard_nmb;
} deck;

void card_setup(deck *cards);

void show_card(int card);

void reshuffle_deck(deck *cards);

void action_cards(int card, deck *cards, Players *player);

void hit(deck *cards, Players *player);

#endif