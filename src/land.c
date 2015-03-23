#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "globals.h"
#include "land.h"

/**
 * Allocate and initialize memory representing square, two-dimensional land.
 * @param size the length of one side of the land square
 * @return a pointer to the start of the land data
 */
land_t ** init_land(int size)
{
	land_t ** land = malloc(size * sizeof(land_t *));
	for(int i = 0; i < size; i++)
	{
		land[i] = malloc(size * sizeof(land_t));

		for(int j = 0; j < size; j++)
			land[i][j].alt = 0;
	}

	return land;
}

/**
 * Randomly generate a landscape.  A landscape is shaped by elevation,
 * and contains semi-randomly distributed terrain types.
 */
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
	int sandline = (waterline + treeline) / 3;
	printf(">>> waterline = %d, treeline = %d\n", waterline, treeline);
	printf(">>> sandline = %d\n", sandline);

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(land[i][j].alt <= waterline)
			{
				land[i][j].terrain = WATER;
			}
			else if(land[i][j].alt >= treeline)
			{
				land[i][j].terrain = ROCK;
			}
			else
			{
				int chance = rand() % 100;
				if((chance <= PROB_SOIL_ABOVE_SL && land[i][j].alt >= sandline) ||
				   (chance <= PROB_SOIL_BELOW_SL && land[i][j].alt < sandline))
				{
					land[i][j].terrain = SOIL;

					// maybe add plant life
					if(chance <= PROB_SOIL_FERTILITY)
						land[i][j].fauna.value = 100;

				}
				else
				{
				   
					land[i][j].terrain = SAND;
					// maybe add plant life
					if(chance <= PROB_SAND_FERTILITY)
						land[i][j].fauna.value = 100;

				}
			}
		}
	}
}

/**
 * Apply a change in elevation to the given (x, y).
 * @param land
 * @param size
 * @param x
 * @param y
 * @param dA
 */
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
