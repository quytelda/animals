#ifndef __ANIMAL_H
#define __ANIMAL_H
#include <stdlib.h>

//IDEA: all animals are independent actors
	//that constantly make new decisions
	//based on their surroundings, needs,
	//attributes, and maybe experience?


//One implementation of diet, makes evolution of diet
	//difficult to implement though
enum diet_t{
	carnivore,
	herbivore,
	omnivore,
	piscevore,
	insectivore
};

enum mobility_t{
	flying,
	swimming,
	galloping,
	running
};


typedef struct animal
{
	//All scales 0-9
	
	//0 = mouse
	//9 = brontosauraus?
	//Scale too wide, too narrow?
	short size;
	short aggression;
	
	//Perhaps these two should be bound
		//for balance purposes
	short gestation_time;
	short litter_size;

	//Alternate diet impementation, loses fine grain
		//control of diet
	//0 = eats only plants
	//9 = eats only meat
	short diet;

	// "world cycles" to move one tile maybe?
	short speed;
	//number of tiles within los?
	short sight;

	//perhaps a sum of creature attributes i.e.
		//claws, teeth, weighted tails, each assigned some form
		//of numerical value?
	short lethality;

	short life_span;
	short age;

	short health_max;
	short health;

	//current vs. best possible
	short stamina_max;
	short stamina;

	short stealth;
	short intelligence;

	struct animal * mate;

} animal_t;

short get_modified(short val, short age, short intelligence);

//have each "species" struct keep a list of its members?
	//maybe an average of traits as well for evolutionary 
	//purposes and/or interesting game stats
typedef struct species
{
	animal_t * members;

}species_t;


//void 

#endif
