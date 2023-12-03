#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCUBES 10	/* arbitrary max number of sets of cubes per game */
#define MAXGAMES 200	/* arbitrary max number of games */

struct cubes {
	int red;	/* red cubes */
	int blue;	/* blue cubes */
	int green;	/* green cubes */
};

struct game {
	int id;	/* id number of the game */
	int ncubes; /* number of subsets of cubes per game */
	struct cubes cubes[MAXCUBES];
};

struct game games[MAXGAMES];
int ngames = 0;

int
parse(char *line)
{
	char *p, *token, *subtoken, *subsubtoken;
	int i, j;

	token = strsep(&line, ":");
	if (sscanf(token, "Game %m[0-9]", &p) != 1)
		err(1, "Unexpected input");
	games[ngames].id = strtol(p, NULL, 10);

	token = strsep(&line, ":");
	

	for (games[ngames].ncubes = 0; 
	    (subtoken = strsep(&token, ";"));
	    games[ngames].ncubes++) {
		games[ngames].cubes[games[ngames].ncubes].blue = 0;
		games[ngames].cubes[games[ngames].ncubes].green = 0;
		games[ngames].cubes[games[ngames].ncubes].red = 0;

		while ((subsubtoken = strsep(&subtoken, ","))) {
			char *n, *color;

			if (sscanf(subsubtoken, " %m[0-9] %m[a-z]", &p, &color) != 2)
				err(1, "unexepected input");

			if (strcmp(color, "blue") == 0)
				games[ngames].cubes[games[ngames].ncubes].blue = strtol(p, NULL, 10);
			if (strcmp(color, "green") == 0)
				games[ngames].cubes[games[ngames].ncubes].green = strtol(p, NULL, 10);
			if (strcmp(color, "red") == 0)
				games[ngames].cubes[games[ngames].ncubes].red = strtol(p, NULL, 10);
			free(p);
			free(color);
		}
	}

	ngames++;

	return 1;
}

int
part1()
{
	int sum, valid;
	int i, j;

	sum = 0;
	for (i = 0; i < ngames; i++) {
		valid = 1;
		for (j = 0; j < games[i].ncubes; j++) {
			if ((games[i].cubes[j].red > 12) ||
			    (games[i].cubes[j].green > 13) ||
			    (games[i].cubes[j].blue > 14))
				valid = 0;
		}
		if (valid)
			sum += games[i].id;
	}

	return sum;
}

int
part2()
{
	int sum;
	int i, j;
	int mred, mgreen, mblue;

	sum = 0;
	for (i = 0; i < ngames; i++) {
		mred = 0, mgreen = 0, mblue = 0;

		for (j = 0; j < games[i].ncubes; j++) {
			if (games[i].cubes[j].red > mred)
				mred = games[i].cubes[j].red;
			if (games[i].cubes[j].green > mgreen)
				mgreen = games[i].cubes[j].green;
			if (games[i].cubes[j].blue > mblue)
				mblue = games[i].cubes[j].blue;
		}

		sum += (mred * mgreen * mblue);
	}

	return sum;
}

int
main()
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while ((nread = getline(&line, &len, stdin)) != -1) {
		if (!parse(line)) {
			err(1, "failed to parse line");
		}
	}

	printf("Answer for day 2 part 1 is: %d\n", part1());
	printf("Answer for day 2 part 2 is: %d\n", part2());

	free(line);
	exit(0);
}
