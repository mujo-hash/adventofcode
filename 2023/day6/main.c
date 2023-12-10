#include <err.h>
#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

struct race {
	uint64_t time;
	uint64_t dist;
} races[MAX];

int nraces;

int
parse(char *buf)
{
	char *line, *tok;
	int i;

	line = strsep(&buf, "\n");
	strsep(&line, " ");	// ignore "Time:" prefix
	i = 0;
	while ((tok = strsep(&line, " "))) {
		if (strcmp(tok, "") == 0)
			continue;
		races[i++].time = strtol(tok, NULL, 10);
	}

	line = strsep(&buf, "\n");
	strsep(&line, " ");	// ignore "Distance:" prefix
	i = 0;
	while ((tok = strsep(&line, " "))) {
		if (strcmp(tok, "") == 0)
			continue;
		races[i++].dist = strtol(tok, NULL, 10);
	}

	nraces = i;

	return 1;
}

uint64_t
getwins(struct race race)
{
	uint64_t win, lose, i;

	win = 0, lose = 0;
	for (i = 0; i < race.time; i++)
		if (((race.time - i) * (i)) > race.dist)	// race record win
			break;
	win = i;
	for (; i < race.time; i++)
		if (((race.time - i) * (i)) <= race.dist)	// race record lost
			break;
	lose = i;
	
	return lose - win;
}

uint64_t
part1()
{
	uint64_t prod, nwin, i;

	prod = 1;
	for (i = 0; i < nraces; i++) {
		nwin = getwins(races[i]);
		if (nwin > 0 && nwin > (INT_MAX / prod))
			err(1, "overflow");
		prod *= nwin;
	}

	return prod;
}

uint64_t
part2()
{
	struct race race;
	char time[20], dist[20];
	char *p;
	int i;

	p = time;
	for (i = 0; i < nraces; i++)
		p += sprintf(p, "%ld", races[i].time);
	p = dist;
	for (i = 0; i < nraces; i++)
		p += sprintf(p, "%ld", races[i].dist);

	race.time = strtol(time, NULL, 10);
	race.dist = strtol(dist, NULL, 10);

	return getwins(race);
}

int
main()
{
	char *buf;
	size_t len;
	ssize_t nread;

	buf = NULL, len = 0;
	while ((nread = getdelim(&buf, &len, EOF, stdin)) != -1) {
		parse(buf);
	}

	printf("The answer to day 6 part 1 is: %ld\n", part1());
	printf("The answer to day 6 part 1 is: %ld\n", part2());

	free(buf);
	exit(0);
}
