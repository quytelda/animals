#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include "land.h"
#include "globals.h"

int main(int argc, char *argv[])
{
	puts("Elen mélima, vylo enor...");
	puts("In the beginning, there was nothing...");
	puts("He dev mmolo, ekudhamaryi quin ????.");
	puts("Then the dev said, let's declare world as a stack variable.");

	world_t world;
	if(argc == 5 || argc == 4)
	{
		int r;
		int c;
		int p;

		//Read and bounds check rows argument
		sscanf(argv[1], "%d", &r);
		r = MAX(r, 0);
		printf("r = %d\n",r);

		//Read and bounds check columns argument
		sscanf(argv[2], "%d", &c);
		c = MAX(c, 0);
		printf("c = %d\n",c);
		
		//Read and bounds check peaks argument
		sscanf(argv[3], "%d", &p);
		p = MAX(p, 0);
		printf("p = %d\n",p);
		
		world.rows = r;
		world.cols = c;
		world.num_splotches = p;
	}
	else
	{
		struct winsize w;
		ioctl(0, TIOCGWINSZ, &w);

		world.rows = w.ws_row - 3;
		world.cols = w.ws_col;
		world.num_splotches = (w.ws_row * w.ws_col)/30;
	}

	world.max_alt = 10;
	world.density = 0;
	world.moisture = 5;
	world.fertility = 0;

	init_world(&world);

	if(argc > 1 && strcmp(argv[argc-1], "e") == 0)
		dump_world_elevation(&world);
	else if(argc > 1 && strcmp(argv[argc-1], "c") == 0)
		{
			int i = 0;
			while((i = update_world(&world, i)) && i <= 150000);
		}
	else
		dump_world(&world);

	puts("But it was good, until the function returned.");
	puts("And things that should not have been forgotten... were freed.");
	destroy_world(&world);
}
