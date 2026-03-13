#include "utils.h"

#include <stdio.h>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

void clear_screen(void)
{
	printf("\033[H\033[J");
}

void delay_ms(int milliseconds)
{
	// clang-format off
	#ifdef _WIN32
		Sleep(milliseconds);
	#else
		usleep(milliseconds * 1000);
	#endif
	// clang-format on
}
