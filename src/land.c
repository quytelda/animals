#include "land.h"

land_t init_land(world_t * world)
{
	land_t ret;
}

void init_world(world_t * world)
{
	world->land = malloc(world->rows * sizeof(land_t *));
	for(int i = 0; i < world->rows; i++)
	{
		world->land[i] = malloc(world->cols * sizeof(land_t));

		// set default values
		for(int j = 0; j < world->cols; j++)
		{
			world->land[i][j] = init_land();
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
