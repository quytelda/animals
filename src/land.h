#ifndef __LAND_H
#define __LAND_H
#include <stdlib.h>

/* `land_t` represents one square unit of land */
typedef struct land
{
	short density;
	short fertility;
	short moisture;

	// TODO: plant list
	// TODO: animal list
} land_t;

typedef struct world
{
	land_t ** land;
	size_t rows, cols;

	// global biome disposition
	short density;
	short fertility;
	short moisture;
} world_t;

void init_world(world_t * world);
void destroy_world(world_t * world);

#endif
