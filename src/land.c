#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "land.h"
#include "globals.h"

void set_alt(land_t * land, short x)
{
	land->alt = x;
}

void set_density(land_t * land, short x)
{
	land->density = x;
}

void set_moisture(land_t * land, short x)
{
	land->moisture = MIN(x, 7);
}

void set_fertility(land_t * land, short x)
{
	land->fertility = x;
}


void splotch_set(world_t * world, int x, int y, short dA, void (*func)(land_t *, short))
{
	assert(world);
	assert(x < world->rows);
	assert(y < world->cols);
	assert(func);

	for(int i = 0; i < dA; i++)
	{
		int x1 = x - i;
		int x2 = x + i;
		int y1 = y - i;
		int y2 = y + i;

		// fill in horizontally
		for(int xi = MAX(x1, 0); xi <= MIN(x2, world->rows - 1); xi++)
		{
			if(y1 >= 0)
				func(&world->land[xi][y1], dA - i);
			if(y2 < world->cols)
				func(&world->land[xi][y2], dA - i);
		}

		// fill in vertically
		for(int yi = MAX(y1, 0); yi <= MIN(y2, world->cols - 1); yi++)
		{
			if(x1 >= 0)
				func(&world->land[x1][yi], dA - i);
			if(x2 < world->rows)
				func(&world->land[x2][yi], dA - i);
		}
	}
}

/**
 * Initialize land tile's properties to the 
 * corresponding world's property +- 2 */
land_t init_land(world_t * world, short var)
{
	land_t lres;
	lres.density =   world->density   + RVAR(var);
	lres.fertility = world->fertility + RVAR(var);
	lres.moisture =  world->moisture  + RVAR(var);
	lres.alt = 0;

	lres.foliage = (flaura_t) {0, 0, 0, 0, 0, 0};
	//TODO: initialize animal list to null
	return lres;
}

void apply_splotches(world_t * world, void (*setter)(land_t *, short))
{
	for(int k = 0; k < world->num_splotches; k++)
	{
		int x = rand() % world->rows;
		int y = rand() % world->cols;

		short delta = (short) rand() % 10;
		splotch_set(world, x, y, delta, setter);
	}
}


void init_world(world_t * world)
{
	// allocate space for the land grid
	world->land = malloc(world->rows * sizeof(land_t *));
	for(int i = 0; i < world->rows; i++)
	{
		world->land[i] = malloc(world->cols * sizeof(land_t));

		// set default values
		for(int j = 0; j < world->cols; j++)
			world->land[i][j] = init_land(world, LAND_VAR);
	}

	/* Shape the land and add terrain.
	 * Randomly "splotch" land properties onto the land grid. */
	srand((unsigned)time(NULL));
	puts("==> Applying Terrain...");
	apply_splotches(world, set_alt);
	apply_splotches(world, set_moisture);
	apply_splotches(world, set_fertility);
	apply_splotches(world, set_density);

	puts("==> Adding water...");
	for(int i = 0; i < world->rows; i++)
		for(int j = 0; j < world->cols; j++)
			if(world->land[i][j].alt == 0)
				world->land[i][j].moisture = (MAX_MOISTURE - 1);

	puts("==> Adding fauna...");
}

/**
 * "Now, I am become death, the Destroyer of Worlds"
 * "Kora li hiro, vankelda quinar."
 */
void destroy_world(world_t * world)
{
	int i;
	for(i=0;i<world->rows;i++)
		free(world->land[i]);
	free(world->land);
}


/** Dump a pictorial representation of the world, for debugging only. */
void dump_world(world_t * world)
{
	for(int i = 0; i < world->rows; i++)
	{
		for(int j = 0; j < world->cols; j++)
		{
			land_t curr = world->land[i][j];

			// pick foreground
			int fg = 0;
			if(curr.density < 4 && curr.fertility < 4)
				fg = 196;
			else if(curr.density < 4 && curr.fertility >= 4)
				fg = 22;
			else if(curr.density >= 4 && curr.fertility < 4)
				fg = 232+11;
			else
				fg = 52;

			// pick background
			int bg =0;
			if(curr.moisture < 3)
				bg = 196+19;
			else if(curr.moisture >= 8)
				bg = 21;
			else
				bg = 16+18;

			printf("\033[38;5;%d;48;5;%dm%d\033[m", fg, bg, curr.alt);
		}
		putchar('\n');
	}
}

void dump_world_elevation(world_t * world)
{
	for(int i = 0; i < world->rows; i++)
	{
		for(int j = 0; j < world->cols; j++)
		{
			land_t curr = world->land[i][j];

			// pick foreground
			int c = 0;
			if(curr.alt )
				c = 196;
			else if(curr.density < 4 && curr.fertility >= 4)
				c = 22;
			else if(curr.density >= 4 && curr.fertility < 4)
				c = 232+11;
			else
				c = 52;

			// pick background
			int b =0;
			if(curr.alt == 0)
				b = 21;
			else if(curr.alt < 2)
				b = 222;
			else if(curr.alt >= 2 && curr.alt < 4)
				b = 130;
			else if(curr.alt >= 4 && curr.alt < 6)
				b = 40;
			else if(curr.alt >= 6 && curr.alt < 8)
				b = 58;
			else
				b= 232 + 13;

			printf("\033[38;5;%d;48;5;%dm%d\033[m", c, b, curr.alt);
		}
		putchar('\n');
	}
}
