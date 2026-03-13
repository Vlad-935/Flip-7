#include <stdio.h>

#include "deck.h"
#include "game.h"
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