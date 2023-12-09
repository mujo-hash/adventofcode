#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX 100 /* arbitrary */

struct map {
	uint32_t src;
	uint32_t dst;
	uint32_t rng;
};

struct mapl {
	int nmap;
	struct map map[MAX];
};

enum mapgroup {
	SEED2SOIL,
	SOIL2FERT,
	FERT2WATER,
	WATER2LIGHT,
	LIGHT2TEMP,
	TEMP2HUMID,
	HUMID2LOCAT,
	NGROUPS
};

struct almanac {
	uint32_t seeds[MAX];
	int nseeds;
	struct mapl mapl[NGROUPS];
} almanac;


void
parseseeds(char *line)
{
	char *tok;
	int i;

	i = 0;
	while ((tok = strsep(&line, " ")) != NULL) {
		if (strcmp(tok, "") == 0)
			continue;
		almanac.seeds[i++] = strtol(tok, NULL, 10);
	}
	almanac.nseeds = i;
}

void
parsemap(enum mapgroup mgroup, char *line)
{
	char *tok;
	int n;

	n = almanac.mapl[mgroup].nmap;

	tok = strsep(&line, " ");
	almanac.mapl[mgroup].map[n].dst = strtol(tok, NULL, 10);
	tok = strsep(&line, " ");
	almanac.mapl[mgroup].map[n].src = strtol(tok, NULL, 10);
	tok = strsep(&line, "\n");
	almanac.mapl[mgroup].map[n].rng = strtol(tok, NULL, 10);

	almanac.mapl[mgroup].nmap++;
}

char *
parsemapl(char *line, char *buf)
{
	char *tok;
	enum mapgroup mg;

	mg = 0;
	if (strcmp(line, "seed-to-soil map:") == 0)
		mg = SEED2SOIL;
	else if (strcmp(line, "soil-to-fertilizer map:") == 0)
		mg = SOIL2FERT;
	else if (strcmp(line, "fertilizer-to-water map:") == 0)
		mg = FERT2WATER;
	else if (strcmp(line, "water-to-light map:") == 0)
		mg = WATER2LIGHT;
	else if (strcmp(line, "light-to-temperature map:") == 0)
		mg = LIGHT2TEMP;
	else if (strcmp(line, "temperature-to-humidity map:") == 0)
		mg = TEMP2HUMID;
	else if (strcmp(line, "humidity-to-location map:") == 0)
		mg = HUMID2LOCAT;
	else
		err(1, "unexpected map type in input");

	while (tok = strsep(&buf, "\n")) {
		if (strcmp(tok, "") == 0)	// end of map section
			break;
		parsemap(mg, tok);
	}

	return buf;	// pointer moved from strsep so return it
}

void
parse(char *buf)
{
	char *tok;
	int i;

	tok = strsep(&buf, ":");
	if (strcmp(tok, "seeds") == 0) {
		tok = strsep(&buf, "\n");
		parseseeds(tok);
	} else {
		err(1, "unexpected input at seeds");
	}
	tok = strsep(&buf, "\n");	// eat the blank newline
	for (i = 0; i < NGROUPS; i++) {
		tok = strsep(&buf, "\n");
		buf = parsemapl(tok, buf);
	}
}

int
src2dst(uint32_t src, enum mapgroup mg)
{
	struct map m;
	uint32_t d;
	int i;

	for (i = 0; i < almanac.mapl[mg].nmap; i++) {
		m = almanac.mapl[mg].map[i];
		if ((src >= m.src) && (src < (m.src + m.rng))) {
			d = src - m.src;
			return m.dst + d;
		}
	}

	return src;	// identity
}

uint32_t
part1()
{
	enum mapgroup mg;
	uint32_t tmp, min;
	int i;

	min = UINT32_MAX;
	for (i = 0; i < almanac.nseeds; i++) {
		tmp = almanac.seeds[i];
		for (mg = SEED2SOIL; mg < NGROUPS; mg++) {
			tmp = src2dst(tmp, mg);
		}
		if (min > tmp)
			min = tmp;
	}

	return min;
}

uint32_t
part2()
{
	enum mapgroup mg;
	uint32_t tmp, min;
	uint32_t i, j;

	min = UINT32_MAX;
	for (i = 0; i < almanac.nseeds; i+=2) {
		for (
			j = 0;
			j < almanac.seeds[i+1];
			j++
		) {
			tmp = almanac.seeds[i] + j;
			for (mg = SEED2SOIL; mg < NGROUPS; mg++) {
				tmp = src2dst(tmp, mg);
			}
			if (min > tmp) {
				min = tmp;
			}
		}
	}

	return min;
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

	printf("The answer to day 5 part 1 is %d\n", part1());
	printf("The answer to day 5 part 1 is %d\n", part2());

	free(buf);
	exit(0);
}
