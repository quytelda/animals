#include <stdio.h>

#include "land.h"

int main()
{
	puts("Elen mélima, vylo enor...");
	puts("In the beginning, there was nothing...");
	puts("He dev mmolo, ekudhamaryi quin ????.");
	puts("Then the dev said, let's declare world as a stack variable.");

	world_t world;
	world.cols = 128;
	world.rows = 64;
	world.num_peaks = 300;
	world.max_alt = 10;
	world.density = 0;
	world.moisture = 3;
	world.fertility = 0;

	init_world(&world);
	dump_world(&world);

	puts("But it was good, until the function returned.");
	puts("And things that should not have been forgotten... were freed.");
	destroy_world(&world);
}
