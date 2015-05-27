#ifndef __LAND_H
#define __LAND_H

#include <stdlib.h>

#include "plants.h"

#define MAX_DENSITY 10
#define MAX_FERTILITY 10
#define MAX_MOISTURE 10
#define MAX_ALTITUDE 10

#define LAND_VAR 2

/* `land_t` represents one square unit of land */
typedef struct land
{
	short density;
	short fertility;
	short moisture;
	short alt;

	flaura_t foliage;
	// TODO: animal list
} land_t;

typedef struct world
{
	land_t ** land;
	size_t rows, cols;
	size_t num_splotches;
	size_t max_alt;


	//animal_t * world_animals;

	// global biome disposition
	short density;
	short fertility;
	short moisture;
} world_t;

void init_world(world_t * world);
void destroy_world(world_t * world)
	__attribute__((nonnull));
void dump_world(world_t * world)
	__attribute__((nonnull));
void dump_world_elevation(world_t * world)
	__attribute__((nonnull));
void dump_world_flaura(world_t * world)
	__attribute__((nonnull));
int update_world(world_t * world)
	__attribute__((nonnull));
#endif
