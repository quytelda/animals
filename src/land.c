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

	//TODO: initialize plant list to null
	//TODO: initialize animal list to null
	return ret;	
}

void init_world(world_t * world)
{
	srand((unsigned)time(NULL));
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
}

/**
 * "Now, I am become death, the Destroyer of Worlds"
 * "Kora li hiro, vankelda quinar."
 */
void destroy_world(world_t * world)
{
}
