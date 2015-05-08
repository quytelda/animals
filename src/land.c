#include "land.h"
#include <stdlib.h>
#include <time.h>

land_t init_land(world_t * world)
{
	land_t ret;
	//Initialize land tile's properties to the 
	//	corresponding world's property +- 2
	ret.density = world->density + (rand() % 5) - 2;
	ret.fertility = world->fertility + (rand() % 5) - 2;
	ret.moisture = world->moisture + (rand() % 5) - 2;
	ret.alt = 0;

	//TODO: initialize plant list to null
	//TODO: initialize animal list to null
	return ret;	
}

void raise(world_t * world, int x, int y, int dA)
{
	for(int i = 0; i != dA; i++)
	{
		int x1 = x - i;
		int x2 = x + i;
		int y1 = y - i;
		int y2 = y + i;

		// fill in horizontally
		for(int xi = MAX(x1, 0); xi <= MIN(x2, world->cols - 1); xi++)
		{
			if(y1 >= 0)
				world->land[xi][y1].alt = dA - i;
			if(y2 < size)
				world->land[xi][y2].alt = dA - i;
		}

		// fill in vertically
		for(int yi = MAX(y1, 0); yi <= MIN(y2, world->rows - 1); yi++)
		{
			if(x1 >= 0)
				world->land[x1][yi].alt = dA - i;
			if(x2 < size)
				world->land[x2][yi].alt = dA - i;
		}

	}
}

void tectonic_shifts(world_t * world)
{
	//Create some elevation
	int i;
	for(i = 0; i < world->num_peaks; i++)
		raise(world, rand()%world->cols, rand()%world->rows, rand()%world->max_alt);
	
}

void init_world(world_t * world)
{
	//Seed random number generator for the initialization process
	srand((unsigned)time(NULL));

	//Allocate space for the land array
	world->land = malloc(world->rows * sizeof(land_t *));
	for(int i = 0; i < world->rows; i++)
	{
		world->land[i] = malloc(world->cols * sizeof(land_t));
		// set default values
		for(int j = 0; j < world->cols; j++)
		{
			world->land[i][j] = init_land(world);
		}
	}

	//Set up the elevation
	tectonic_shifts(world);
}

/**
 * "Now, I am become death, the Destroyer of Worlds"
 * "Kora li hiro, vankelda quinar."
 */
void destroy_world(world_t * world)
{
}
