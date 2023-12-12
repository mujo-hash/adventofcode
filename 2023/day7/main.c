#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum strength {
	HIGHC,
	ONEP,
	TWOP,
	THREEOAK,
	FULLH,
	FOUROAK,
	FIVEOAK
};

struct poker {
	char hand[6];
	int bid;
} hands[1000];

int nhands;

void
parse(char *buf)
{
	char *line, *ph, *pb;

	while ((line = strsep(&buf, "\n")) != NULL && (strcmp(line, "") != 0)) {
		sscanf(line, "%m[AKQJT2-9] %m[0-9]", &ph, &pb);
		sprintf(hands[nhands].hand, "%s", ph);
		hands[nhands].bid = strtol(pb, NULL, 10);
		nhands++;
		free(ph);
		free(pb);
	}
}

enum strength
getstrength(struct poker hand)
{
	
}

int
compare(const void *p1, const void *p2)
{
	struct poker *hand1, *hand2;
	enum strength s1, s2;

	hand1 = (struct poker *) p1;
	hand2 = (struct poker *) p2;

	s1 = getstrength(&hand1);
	s2 = getstrength(&hand2);

	return 0;
}

int
part1()
{
	qsort(hands, nhands, sizeof(hands[0]), compare);
	return 1;
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

	printf("The answer to day 7 part 1 is: %d\n", part1());
	// printf("The answer to day 7 part 2 is: %ld\n", part2());

	free(buf);
	exit(0);
}
