#ifndef GAME
#define GAME

#include "cards.h"
#include "hit.h"
#include "player.h"

void game_round(int player_count, deck cards, Players *player);

void game(int player_count, deck cards, Players *player);

#endif