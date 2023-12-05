#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000 /* aribtrary limit */

struct card {
	int id;	/* id number of card */
	int nwin;	/* number of winning numbers on card */
	int nhave;	/* number of numbers we have on card */
	int win[MAX];	/* array of winning numbers */
	int have[MAX];	/* array of numbers we have on the card */
};

struct card cards[MAX];
int ncards = 0;

int
parse(char *line)
{
	char *token, *subtok, *subsubtok;
	char *p;
	int i;

	token = strsep(&line, ":");
	sscanf(token, "Card %m[0-9]", &p);
	cards[ncards].id = strtol(p, NULL, 10);
	free(p);
	token = strsep(&line, ":");
	subtok = strsep(&token, "|");
	for (i = 0; (subsubtok = strsep(&subtok, " ")) != NULL; ) {
		if (sscanf(subsubtok, " %m[0-9]", &p) != 1)
			continue;
		cards[ncards].win[i++] = strtol(p, NULL, 10);
		free(p);
	}
	cards[ncards].nwin = i;
	subtok = strsep(&token, "|");
	for (i = 0; (subsubtok = strsep(&subtok, " ")) != NULL; ) {
		if (sscanf(subsubtok, " %m[0-9]", &p) != 1)
			continue;
		cards[ncards].have[i++] = strtol(p, NULL, 10);
		free(p);
	}
	cards[ncards].nhave = i;
	ncards++;

	return 1;
}

int
part1()
{
	int points, sum;
	int i, j, k;
	
	sum = 0;
	for (i = 0; i < ncards; i++) {
		points = 0;
		for (j = 0; j < cards[i].nwin; j++) {
			for (k = 0; k < cards[i].nhave; k++) {
				if (cards[i].win[j] == cards[i].have[k])
					points = (points > 0) ? (points * 2) : 1;
			}
		}
		sum += points;
	}

	return sum;
}

int
countcards(int start, int end)
{
	int copy, sum;
	int i, j, k;
	
	sum = 0;
	for (i = start; i < end; i++) {
		copy = 0;
		for (j = 0; j < cards[i].nwin; j++) {
			for (k = 0; k < cards[i].nhave; k++) {
				if (cards[i].win[j] == cards[i].have[k])
					copy++;
			}
		}
		sum++;
		sum += countcards(i + 1, i + 1 + copy);
	}

	return sum;
}

int
part2()
{
	return countcards(0, ncards);
}

int
main()
{
	char *line;
	size_t len;
	ssize_t nread;

	line = NULL, len = 0;
	while ((nread = getline(&line, &len, stdin)) != -1) {
		if (!parse(line))
			err(1, "failed to parse line");
	}

	printf("The answer to day 4 part 1 is: %d\n", part1());
	printf("The answer to day 4 part 2 is: %d\n", part2());

	free(line);
	exit(0);
}
