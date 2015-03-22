#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "globals.h"
#include "land.h"

land_t ** init_land(land_t ** land, int size)
{
	land = malloc(size * sizeof(land_t *));
	for(int i = 0; i < size; i++)
	{
		land[i] = malloc(size * sizeof(land_t));

		for(int j = 0; j < size; j++)
			land[i][j].alt = 0;
	}

	return land;
}

void make_landscape(land_t ** land, int size, int num)
{
	// generate landscape shape
	puts("==> Shaping landscape...");
	srand(time(NULL));
	for(int k = 0; k < num; k++)
	{
		int x = rand() % size;
		int y = rand() % size;

		int dA = rand() % MAX_ALT;

		raise(land, size, x, y, dA);
	}

	// add terrain types
	puts("==> Adding terrain types...");
	int waterline = 0;
	int treeline = (2 * MAX_ALT) / 3;
	printf(">>> waterline = %d, treeline = %d\n", waterline, treeline);

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(land[i][j].alt <= waterline)
				land[i][j].terrain = WATER;
			else if(land[i][j].alt >= treeline)
				land[i][j].terrain = ROCK;
			else
				land[i][j].terrain = SOIL;
		}
	}
}

void raise(land_t ** land, int size, int x, int y, int dA)
{
	for(int i = 0; i != dA; i++)
	{
		int x1 = x - i;
		int x2 = x + i;
		int y1 = y - i;
		int y2 = y + i;

		// fill in horizontally
		for(int xi = MAX(x1, 0); xi <= MIN(x2, size - 1); xi++)
		{
			if(y1 >= 0)
				land[xi][y1].alt = dA - i;
			if(y2 < size)
				land[xi][y2].alt = dA - i;
		}

		// fill in vertically
		for(int yi = MAX(y1, 0); yi <= MIN(y2, size - 1); yi++)
		{
			if(x1 >= 0)
				land[x1][yi].alt = dA - i;
			if(x2 < size)
				land[x2][yi].alt = dA - i;
		}

	}
}
