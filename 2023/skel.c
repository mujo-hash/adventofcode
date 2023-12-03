#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main()
{
	char *line;
	size_t len;
	ssize_t nread;

	line = NULL, len = 0;
	while ((nread = getline(&line, &len, stdin)) != -1) {
		// do stuff
	}

	free(line);
	exit(0);
}
