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

typedef struct range { char start, end; } range;

static const range PLANT_D = {1, 9};
static const range FLOWERS_D = {2, 8};
static const range ROOTS_D = {3, 6};
static const range FRUITS_D = {2, 7};
static const range SEEDS_D = {3, 8};

static const range PLANT_F = {1, 10};
static const range FLOWERS_F = {3, 10};
static const range ROOTS_F = {3, 10};
static const range FRUITS_F = {5, 10};
static const range SEEDS_F = {3, 10};

static const range PLANT_M = {2, 9};
static const range FLOWERS_M = {3, 7};
static const range ROOTS_M = {4, 8};
static const range FRUITS_M = {2, 8};
static const range SEEDS_M = {4, 6};

#define M_FRUIT  0
#define M_FLOWER 1
#define M_ROOT   2
#define M_SEED   3

typedef struct plant
{
	int matter;
	int value;
} plant_t;

void add_matter(plant_t * plant, int m);
void rem_matter(plant_t * plant, int m);

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
