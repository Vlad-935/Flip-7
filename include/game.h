#ifndef GAME
#define GAME

#include "deck.h"
#include "player.h"

void show_cards(Players player);

void make_choice(int players_turn, int active_players,
				 deck cards, Players *player);

void game_round(int player_count, deck cards, Players *player);

void game(int player_count, deck cards, Players *player);

#endif