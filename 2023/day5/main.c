#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

uint32_t **seed2soil;
uint32_t **soil2fert;
uint32_t **fert2water;
uint32_t **water2light;
uint32_t **light2temp;
uint32_t **temp2humid;
uint32_t **humid2locat;

uint32_t plant[100];	/* arbitrary max number of seeds to plant */
int nplant;

/**
 * Initialize the maps and put them in the global map pointers.
 */
void
initmaps()
{
	if ((seed2soil = calloc(UINT32_MAX, sizeof(uint32_t))) == NULL)
		err(1, "calloc failed");
	// for (i = 0; i < UINT32_MAX; i++)
		// mapp[i].seed = i;
}

void
parseseeds(char *line)
{
	printf("%s\n", line);
}

void
parsemap(uint32_t dst[], uint32_t src[], char *line)
{
}

int
parse(char *buf)
{
	char *tok;

	tok = strsep(&buf, ":");
	if (strcmp(tok, "seeds") == 0) {
		tok = strsep(&buf, "\n");
		parseseeds(tok);
	} else {
		err(1, "unexpected input at seeds");
	}
	tok = strsep(&buf, "\n");	// eat the blank newline
	tok = strsep(&buf, ":");
	if (strcmp(tok, "seed-to-soil map") == 0) {
		tok = strsep(&buf, "\n");	// eat the trailing newline
		while (tok = strsep(&buf, "\n")) {
			if (strcmp(tok, "") == 0)
				break;
			// parsemap(map.seeds, map.soils, tok);
		}
	} else {
		err(1, "unexpected input at seed-to-soil map");
	}

	return 1;
}

int
main()
{
	char *buf;
	size_t len;
	ssize_t nread;

	initmaps();

	buf = NULL, len = 0;
	while ((nread = getdelim(&buf, &len, EOF, stdin)) != -1) {
		parse(buf);
	}

	free(buf);
	exit(0);
}
