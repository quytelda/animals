#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_ALT 10
#define MIN_ALT -10

#define SGN(x) ((x >= 0) ? 1 : -1)
#define MAX(x, y) ((x > y) ? x : y)
#define MIN(x, y) ((x > y) ? y : x)

typedef enum {ROCK, SOIL, SAND, WATER} terrain_t;

typedef struct land
{
	int alt;
} land_t;

land_t ** init_land(land_t ** land, int size);
void make_landscape();
void make_terrain();

void raise(land_t ** land, int size, int x, int y, int alt);

int main()
{
	land_t ** land;

	puts("* Initializing land...");
	land = init_land(land, 64);

	puts("* Generating landscape...");
	make_landscape(land, 64, 32);

	for(int i = 0; i < 64; i++)
	{
		for(int j = 0; j < 64; j++)
			printf("%d", land[i][j].alt);
		putchar('\n');
	}

	free(land);
	return 0;
}

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
	for(int k = 0; k < num; k++)
	{
		int x = rand() % size;
		int y = rand() % size;

		int dA = rand() % MAX_ALT;
		printf("(%d, %d).alt += %d\n", x, y, dA);

		raise(land, size, x, y, dA);
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

		printf("%d,%d,%d,%d\n", x1,x2,y1,y2);

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
