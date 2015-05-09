#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "land.h"
#include "globals.h"

void change_alt(land_t * land, short x)
{
	land->alt = x;
}

void change_density(land_t * land, short x)
{
	land->density = x;
}

void change_moisture(land_t * land, short x)
{
	land->moisture = MIN(x, 7);
}

void change_fertility(land_t * land, short x)
{
	land->fertility = x;
}


void apply_change(world_t * world, int x, int y, short dA, void (*func)(land_t *, short))
{
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


land_t init_land(world_t * world)
{
	land_t ret;
	//Initialize land tile's properties to the 
	//	corresponding world's property +- 2
	ret.density = MIN(MAX(world->density + (rand() % 5) - 2, 0),9);
	ret.fertility = MIN(MAX(world->fertility + (rand() % 5) - 2, 0),9);
	ret.moisture = MIN(MAX(world->moisture + (rand() % 5) - 2, 0),9);
	ret.alt = 0;

	//TODO: initialize plant list to null
	//TODO: initialize animal list to null
	return ret;	
}

void apply_splotches(world_t * world, void (*func)(land_t *, short))
{
	for(int k = 0; k < world->num_peaks; k++)
	{
		int x = rand() % world->rows;
		int y = rand() % world->cols;

		short dA = (short) rand() % 10;
		apply_change(world, x, y, dA, func);
	}
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
			world->land[i][j] = init_land(world);
	}

	// Set up the elevation
	puts("==> Applying Splotches...");
	puts("  >>> altitude");
	apply_splotches(world, change_alt);
	puts("  >>> moisture");
	apply_splotches(world, change_moisture);
	puts("  >>> fertility");
	apply_splotches(world, change_fertility);
	puts("  >>> density");
	apply_splotches(world, change_density);

	puts("==> Just adding water...");
	for(int i = 0; i < world->rows; i++)
		for(int j = 0; j < world->cols; j++)
			if(!world->land[i][j].alt)
				world->land[i][j].moisture = 9;
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


//Dump a pictorial representation of the world, for debugging only
void dump_world(world_t * world)
{
	for(int i = 0; i < world->rows; i++)
	{
		for(int j = 0; j < world->cols; j++)
		{
			land_t curr = world->land[i][j];

			// pick foreground
			int c = 0;
			if(curr.density < 4 && curr.fertility < 4)
				c = 196;
			else if(curr.density < 4 && curr.fertility >= 4)
				c = 22;
			else if(curr.density >= 4 && curr.fertility < 4)
				c = 232+11;
			else
				c = 52;

			// pick background
			int b =0;
			if(curr.moisture < 3)
				b = 196+19;
			else if(curr.moisture >= 8)
				b = 21;
			else
				b=16+18;

			printf("\033[38;5;%d;48;5;%dm%d\033[m", c, b, curr.alt);
		}
		putchar('\n');
	}
}
