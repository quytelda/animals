#ifndef __LAND_H
#define __LAND_H

#define MAX_ALT 10
#define SIZE 64
#define NUM_PEAKS 128

typedef enum {ROCK, SOIL, SAND, WATER} terrain_t;

typedef struct land
{
	int alt;
	terrain_t terrain;
} land_t;

land_t ** init_land(land_t ** land, int size);
void make_landscape(land_t ** land, int size, int num);

void raise(land_t ** land, int size, int x, int y, int alt);

#endif
