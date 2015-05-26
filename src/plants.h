#ifndef __PLANT_H
#define __PLANT_H

#define MAX_FRUIT 10
#define MAX_SEEDS 10
#define MAX_FLOWERS 10
#define MAX_ROOTS 10
#define MAX_LEAVES 10
#define MAX_HEALTH 10

typedef struct range
{
	int min;
	int max;
} range_t;

typedef struct flaura
{
	short fruit;
	short seeds;
	short flowers;
	short roots;
	short leaves;
	short health;
} flaura_t;
#endif
