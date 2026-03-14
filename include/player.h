#ifndef PLAYER
#define PLAYER

#include <stdbool.h>

typedef struct {
	int total_points, round_points;
	int different_cards, total_cards, cards_in_hand[22];
	bool in_game;
} Players;

Players *player_setup(int player_count);

bool update_bust_state(Players *player);

void show_player_cards(Players player);

#endif