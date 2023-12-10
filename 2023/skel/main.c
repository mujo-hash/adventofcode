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
main()
{
	char *buf;
	size_t len;
	ssize_t nread;

	buf = NULL, len = 0;
	while ((nread = getdelim(&buf, &len, EOF, stdin)) != -1) {
		parse(buf);
	}

	free(buf);
	exit(0);
}
