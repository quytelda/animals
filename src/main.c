#include <stdio.h>

#include "land.h"

int main()
{
	puts("Elen mélima, vylo enor...");
	puts("In the beginning, there was nothing...");
	puts("He dev mmolo, ekudhamaryi quin ????.");
	puts("Then the dev said, let's declare world as a stack variable.");
	world_t world;
	init_world(&world);
	puts("But it was good, until the function returned.");
	puts("And things that should not have been forgotten... were freed.");
}
