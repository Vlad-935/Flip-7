#include "utils.h"

#include <stdio.h>

void clear_screen(void)
{
	printf("\033[H\033[J");
}
