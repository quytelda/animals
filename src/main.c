#include <stdio.h>

#include "land.h"

int main()
{
	puts("Elen mélima, vylo enor...");
	puts("In the beginning, there was nothing...");
	puts("He dev mmolo, ekudhamaryi quin ????.");
	puts("Then the dev said, let's declare world as a stack variable.");

	world_t world;
	world.cols = world.rows = 64;
	world.num_peaks = 32;
	world.max_alt = 10;
	world.density = 5;
	world.moisture = 5;
	world.fertility = 5;

	init_world(&world);
	dump_world(&world);

	puts("But it was good, until the function returned.");
	puts("And things that should not have been forgotten... were freed.");
	destroy_world(&world);
}
