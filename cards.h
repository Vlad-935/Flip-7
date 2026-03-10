#ifndef CARDS
#define CARDS

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
	int total_nmb;
} deck;

void card_setup(deck *cards);

#endif