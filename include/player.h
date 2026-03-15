#ifndef PLAYER
#define PLAYER

#include <stdbool.h>

typedef struct {
	int id;

	int total_points;
	int different_cards,
		total_cards,
		cards_in_hand[22];
	bool in_game, busted;
} Players;

Players *player_setup(int player_count);

void update_bust_state(Players *player);

void bust(Players *player);

void show_player_cards(Players player);

int calculate_points(Players player);

#endif