#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void
parse(char *buf)
{
	// do stuff
}

int
part1()
{
	// do stuff
}

int
part2()
{
	// do stuff
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

	// printf("The answer to day X part 1 is: %d\n", part1());
	// printf("The answer to day X part 2 is: %d\n", part2());

	free(buf);
	exit(0);
}
