#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "deck.h"
#include "game.h"
#include "player.h"

int main(void)
{
	srand(time(NULL));

	round_state round;
	round.player_count = 0;

	deck cards;
	card_setup(&cards);

	printf("Introduceti numarul de jucatori: ");
	scanf("%d", &round.player_count);

	Players *player = player_setup(round.player_count);

	game(round, &cards, player);
	return 0;
}