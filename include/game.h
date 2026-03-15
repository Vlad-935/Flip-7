#ifndef GAME
#define GAME

#include "deck.h"
#include "player.h"

typedef struct {
	int player_count,
		active_players,
		players_turn;
	bool flip7;
} round_state;

void new_round_setup(round_state *round, Players *player);

void make_choice(round_state *round, deck *cards, Players *player);

void game_round(round_state round, deck *cards, Players *player);

void game(round_state round, deck *cards, Players *player);

#endif