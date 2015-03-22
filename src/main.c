#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "land.h"

int main()
{
	land_t ** land;

	puts("* Initializing land...");
	land = init_land(land, SIZE);

	puts("* Generating landscape...");
	make_landscape(land, SIZE, NUM_PEAKS);

	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			char * term_color;
			switch(land[i][j].terrain)
			{
			case WATER:
				term_color = KBLU;
				break;
			case SOIL:
				term_color = KGRN;
				break;
			default:
				term_color = KNRM;
			}

			printf("%s%d%s", term_color, land[i][j].alt, KNRM);
		}
		putchar('\n');
	}

	free(land);
	return 0;
}
