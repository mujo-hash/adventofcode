#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int priority(char item) {
	switch (item) {
	case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g': case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n': case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
		return item + 1 - 'a';
	case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
		return item + 27 - 'A';
	}
}

int finditem(char *line, ssize_t len) {
	int i, j;

	for (i = 0; i < (len / 2); ++i) {
		for (j = (len / 2); j < len; ++j) {
			if (line[i] == line[j])
				return priority(line[i]);
		}
	}
}

void freegroup(char ***group) {
	free(**group);
}

int findgroup(char ***group) {
	printf("passed group pointer: %p\n", **group);
	int i;

	for (i = 0; i < 3; i++, *group++) {
		//printf("group: %s\n", *group);
	}
	return 0;
}

int main() {
	char **group;
	char *line = NULL;
	size_t len = 0, nlines = 0;
	ssize_t nread;
	int part1 = 0, part2 = 0;

	group = malloc(sizeof(char*) * 3);
	while ((nread = getline(&line, &len, stdin)) != -1) {
		// trim newline
		--nread, line[nread] = '\0';

		part1 += finditem(line, nread);

		if (nlines != 0 && nlines % 3 == 0) {
			printf("got here\n");
			part2 += findgroup(&group);
			printf("got here2\n");
			freegroup(&group);
		}

		group[nlines] = malloc(len);
		memcpy(group[nlines++ % 3], line, len);
		printf("line: %s\n", line);
		printf("group: %s\n", group[nlines - 1]);
		printf("group pointer: %p\n", group[nlines - 1]);
	}
	free(line);
	freegroup(&group);
	free(group);
	printf("Sum of priorities is: %d\n", part1);
	return 0;
}
