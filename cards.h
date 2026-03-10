#ifndef CARDS
#define Cards

enum cards {
	freeze = 13,
	second_chance,
	flip_three,
	b_two,
	b_four,
	b_six,
	b_eight,
	b_ten,
	times_two
};

typedef struct {
	int main[22], discard[22];
	int total_nmb;
} deck;

void card_setup(deck *cards);

#endif