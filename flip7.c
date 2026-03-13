#include <stdio.h>

#include "cards.h"
#include "game.h"
#include "hit.h"
#include "player.h"

int main(void)
{
	int player_count;
	deck cards;

	card_setup(&cards);

	printf("Introduceti numarul de jucatori: ");
	scanf("%d", &player_count);

	Players *player = player_setup(player_count);

	game(player_count, cards, player);

	return 0;
}