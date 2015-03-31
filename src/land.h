#ifndef __LAND_H
#define __LAND_H

#define MAX_ALT 10
#define SIZE 64
#define NUM_PEAKS 128
#define PLANT_VALUE	100


// Probabilities of landscape features.
// Probabilities are integers between 0 and 100, inclusive.
#define PROB_SOIL_FERTILITY 20 // probability a soil square will have plants
#define PROB_SAND_FERTILITY 10 // probability a sand square will have plants
#define PROB_SOIL_ABOVE_SL  75 // probability of dirt above the sand line
#define PROB_SOIL_BELOW_SL  25 // probability of dirt below the sand line
#define PROB_SOIL_ABOVE_TL  10 // probability of dirt above the treeline

typedef enum {ROCK, SOIL, SAND, WATER} terrain_t;

typedef struct plant
{
	int value;
} plant_t;


typedef struct land
{
	int alt;
	terrain_t terrain;

	plant_t fauna;
} land_t;

land_t ** init_land(int size);
void make_landscape(land_t ** land, int size, int num);

void raise(land_t ** land, int size, int x, int y, int alt);

#endif
