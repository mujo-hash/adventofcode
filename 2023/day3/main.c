#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 2048	/* arbitrary limit to number of symbols or numbers */

struct point {
	int row;	/* 0th indexed row */
	int col;	/* 0th indexed column */
};

struct symbol {
	char val;
	struct point pnt;
};

struct number {
	int val;
	int npnts;	/* number of points the number ranges over */
	struct point pnts[10];	/* arbitrary max length of number */
};

struct symbol symbols[MAX];
struct number numbers[MAX];
int nsymbols = 0;
int nnumbers = 0;
int nrows = 0;

int
parse(char *line)
{
	char *s, *p;
	int i, j;

	for (i = 0, s = line; i < strlen(line) && *s != '\0'; ) {
		if (sscanf(s, "%m[0-9]", &p) == 1) {
			numbers[nnumbers].val = strtol(p, NULL, 10);
			numbers[nnumbers].npnts = 0;
			for (j = 0; j < strlen(p); j++) {
				numbers[nnumbers].pnts[j].row = nrows;
				numbers[nnumbers].pnts[j].col = i + j;
			}
			numbers[nnumbers].npnts = j;
			nnumbers++;
			i += j;
			s += j;
			free(p);
			continue;
		}
		if (sscanf(s, "%m[-#$*+/@%=&]", &p) == 1) {
			symbols[nsymbols].val = p[0];
			symbols[nsymbols].pnt.row = nrows;
			symbols[nsymbols].pnt.col = i;
			nsymbols++;
			free(p);
		}
		i++;
		*s++;
	}
	nrows++;

	return 1;
}

int
isdiagnol(struct point a, struct point b)
{
	if (((a.row - 1 == b.row) && (a.col - 1 == b.col)) ||
	    ((a.row - 1 == b.row) && (a.col == b.col)) ||
	    ((a.row - 1 == b.row) && (a.col + 1 == b.col)) ||
	    ((a.row == b.row) && (a.col - 1 == b.col)) ||
	    ((a.row == b.row) && (a.col == b.col)) ||
	    ((a.row == b.row) && (a.col + 1 == b.col)) ||
	    ((a.row + 1 == b.row) && (a.col - 1 == b.col)) ||
	    ((a.row + 1 == b.row) && (a.col == b.col)) ||
	    ((a.row + 1 == b.row) && (a.col + 1 == b.col)))
		return 1;
	return 0;
}

int
part1()
{
	int valid, sum, i, j, k;

	// find the valid numbers
	sum = 0;
	for (i = 0; i < nnumbers; i++) {
		valid = 0;
		for (j = 0; j < numbers[i].npnts; j++) {
			for (k = 0; k < nsymbols; k++) {
				if (isdiagnol(numbers[i].pnts[j], symbols[k].pnt))
					valid = 1;
			}
		}
		if (valid) {
			sum += numbers[i].val;
		}
	}

	return sum;
}

int
part2()
{
	int gear1, gear2, valid, sum, i, j, k;

	sum = 0;
	for (i = 0; i < nsymbols; i++) {
		if (symbols[i].val != '*')
			continue;
		valid = 0, gear1 = 0, gear2 = 0;
		for (j = 0; j < nnumbers; j++) {
			for (k = 0; k < numbers[j].npnts; k++) {
				if (isdiagnol(symbols[i].pnt, numbers[j].pnts[k])) {
					valid++;
					if (valid == 1)
						gear1 = numbers[j].val;
					if (valid == 2)
						gear2 = numbers[j].val;
					break;
				}
			}
		}
		if (valid == 2) {
			sum += (gear1 * gear2);
		}
	}

	return sum;
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

	printf("The answer for day 3 part 1 is: %d\n", part1());
	printf("The answer for day 3 part 2 is: %d\n", part2());

	free(line);
	exit(0);
}
