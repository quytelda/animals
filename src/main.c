#include <stdio.h>
#include <stdlib.h>

#include "globals.h"
#include "land.h"

int main()
{
	land_t ** land;

	puts("* Initializing land...");
	land = init_land(SIZE);

	puts("* Generating landscape...");
	make_landscape(land, SIZE, NUM_PEAKS);

	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			char * term_color;
			char * term_bg_color = BG_NRM;
			switch(land[i][j].terrain)
			{
			case WATER:
				term_color = KBLU;
				break;
			case SOIL:
				term_color = KRED;
				break;
			case SAND:
				term_color = KYLW;
				break;
			case ROCK:
				term_color = KGRY;
				break;
			default:
				term_color = KNRM;
			}

			if(land[i][j].fauna.value > 0)
				term_bg_color = BG_GRN;

			printf("%s%s%d%s%s", term_color, term_bg_color, land[i][j].alt, KNRM, BG_NRM);
		}
		putchar('\n');
	}

	free(land);
	return 0;
}
