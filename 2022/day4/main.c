#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef int section;

size_t assignment(section ass[MAX], char *range) {
	section a, a0, an;
	int i, len;

	sscanf(range, "%d-%d", &a0, &an);
	for (i = 0, a = a0; a <= an; i++, a++) {
		ass[i] = a;
	}
	len = i;
	return len;
}

bool iscontains(section a1[MAX], size_t len1, section a2[MAX], size_t len2) {
	if (a1[0] <= a2[0] && a1[len1 - 1] >= a2[len2 - 1])
		return true;
	if (a1[0] >= a2[0] && a1[len1 - 1] <= a2[len2 - 1])
		return true;
	return false;
}

int part1(char *r1, char *r2) {
	section a1[MAX], a2[MAX];
	size_t len1, len2;
	bool res;

	len1 = assignment(a1, r1);
	len2 = assignment(a2, r2);

	if (iscontains(a1, len1, a2, len2))
		return 1;
	return 0;
}

bool isoverlap(section a1[MAX], size_t len1, section a2[MAX], size_t len2) {
	if (a1[len1 - 1] >= a2[0] && a1[0] <= a2[len2 - 1])
		return true;
	if (a1[0] <= a2[len2 - 1] && a1[len1 - 1] >= a2[0])
		return true;
	return false;
}

int part2(char *r1, char *r2) {
	section a1[MAX], a2[MAX];
	size_t len1, len2;
	bool res;

	len1 = assignment(a1, r1);
	len2 = assignment(a2, r2);

	if (isoverlap(a1, len1, a2, len2))
		return 1;
	return 0;
}

int main() {
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int ncontains = 0, noverlaps = 0;

	assert(part1("2-4", "6-8") == 0);
	assert(part1("2-8", "3-7") == 1);

	assert(part2("2-4", "6-8") == 0);
	assert(part2("2-3", "4-5") == 0);
	assert(part2("5-7", "7-9") == 1);
	assert(part2("2-8", "3-7") == 1);
	assert(part2("6-6", "4-6") == 1);
	assert(part2("2-6", "4-8") == 1);
	assert(part2("4-98", "1-1") == 0);

	while ((nread = getline(&line, &len, stdin)) != -1) {
		char r1[10], r2[10];

		sscanf(line, "%[0-9-],%[0-9-]\n", r1, r2);
		ncontains += part1(r1, r2);
		noverlaps += part2(r1, r2);
	}
	free(line);

	printf("part1 number of containing pairs: %d\n", ncontains);
	printf("part2 number of overlapping pairs: %d\n", noverlaps);
	return 0;
}
