#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <unistd.h>
#include <ncurses.h>

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

void initialize_fauna(land_t * f)
{
	f->foliage.fruit 	= rand() % 60;
	f->foliage.seeds 	= rand() % 60;
	f->foliage.flowers 	= rand() % 60;
	f->foliage.roots 	= rand() % 60;
	f->foliage.leaves 	= rand() % 60;
	f->foliage.health 	= rand() % 60;
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

	puts("==> Adding flaura...");
	for(int i = 0; i < world->rows; i++)
		for(int j = 0; j < world->cols; j++)
			if(world->land[i][j].alt != 0)
				initialize_fauna(&world->land[i][j]);
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

int check_range(short l, short m, short x)
{
	if(x >= l && x <= m)
		return 1;
	return -1;
}

void update_flaura(land_t * land)
{
	//weight all 4 equally
	short d = land->density;
	short m = land->moisture;
	short f = land->fertility;
	short a = land->alt;

	if(land->foliage.fruit)
	{
		int inc = -2;
		inc += rand() % 5;
		inc += check_range(2, 6, d);
		inc += check_range(4, 10, f);
		inc += check_range(3, 7, m);
		inc += check_range(1, 5, a);
		land->foliage.fruit += inc;
		land->foliage.fruit = MIN(land->foliage.fruit, 99);
		land->foliage.fruit = MAX(land->foliage.fruit, 0);
	}

	if(land->foliage.seeds)
	{
		int inc = -2;
		inc += rand() % 5;
		inc += check_range(2, 7, d);
		inc += check_range(3, 10, f);
		inc += check_range(2, 6, m);
		inc += check_range(2, 7, a);
		land->foliage.seeds += inc;
		land->foliage.seeds = MIN(land->foliage.seeds, 99);
		land->foliage.seeds = MAX(land->foliage.seeds, 0);
	}

	if(land->foliage.flowers)
	{
		int inc = -2;
		inc += rand() % 5;
		inc += check_range(3, 6, d);
		inc += check_range(3, 10, f);
		inc += check_range(2, 8, m);
		inc += check_range(1, 7, a);
		land->foliage.flowers += inc;
		land->foliage.flowers = MIN(land->foliage.flowers, 99);
		land->foliage.flowers = MAX(land->foliage.flowers, 0);
	}

	if(land->foliage.roots)
	{
		int inc = -2;
		inc += rand() % 5;
		inc += check_range(3, 6, d);
		inc += check_range(2, 10, f);
		inc += check_range(2, 6, m);
		inc += check_range(1, 5, a);
		land->foliage.roots += inc;
		land->foliage.roots = MIN(land->foliage.roots, 99);
		land->foliage.roots = MAX(land->foliage.roots, 0);
	}	

	if(land->foliage.leaves)
	{
		int inc = -2;
		inc += rand() % 5;
		inc += check_range(1, 8, d);
		inc += check_range(1, 10, f);
		inc += check_range(1, 8, m);
		inc += check_range(1, 8, a);
		land->foliage.leaves += inc;
		land->foliage.leaves = MIN(land->foliage.leaves, 99);
		land->foliage.leaves = MAX(land->foliage.leaves, 0);
	}

	land->foliage.health = land->foliage.fruit + land->foliage.seeds + land->foliage.flowers + land->foliage.roots + land->foliage.leaves;
}
//continuously iterates through all plants and animals
	//updates them and the worlds knowledge of them
int update_world(world_t * world)
{
	//updates all plants
	//puts("updating flaura...");
	for(int i = 0; i < world->rows; i++)
		for(int j = 0; j < world->cols; j++)
			if(world->land[i][j].alt != 0)
				update_flaura(&world->land[i][j]);
	
	//puts("updating fauna...");
	//updates all animals

	return 1;
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

void dump_world_flaura(world_t * world)
{
	for(int i = 0; i < world->rows; i++)
	{
		for(int j = 0; j < world->cols; j++)
		{
			land_t curr = world->land[i][j];

			// pick background
			int bg = 0;
			if(curr.foliage.health < 100)
				bg = 196;
			else if(curr.foliage.health < 200)
				bg = 52;
			else if(curr.foliage.health < 300)
				bg = 222;
			else if(curr.foliage.health < 400)
				bg = 22;
			else
				bg = 40;

			// pick foreground
			int fg =0;
			if(curr.foliage.leaves < 25)
				fg = 16+18;
			else if(curr.foliage.leaves >= 75)
				fg = 232 + 13;
			else
				fg = 196+19;

			if(curr.alt == 0)
				bg = 21;

			printf("\033[38;5;%d;48;5;%dm%d\033[m", fg, bg, (curr.foliage.health/100));
		}
		putchar('\n');
	}
}


