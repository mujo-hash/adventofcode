#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SOPLEN 4
#define SOMLEN 14
#define MAX 100

struct packet {
	int top;
	char mark[MAX];
};

void printpacket(struct packet p) {
	int i;

	printf("packet: ");
	for (i = 0; i < p.top; i++) {
		printf("%c", p.mark[i]);
	}
	printf("\n");
}

void pushpacket(struct packet *p, int len, char c) {
	int i;

	if (p->top < len) {
		p->mark[p->top++] = c;
		return;
	} else {
		for (i = 1; i < len; i++) {
			p->mark[i - 1] = p->mark[i];
		}
		p->mark[len - 1] = c;
	}
}

bool ismark(struct packet p, int len) {
	int i, j;

	for (i = 0; i < len; i++) {
		for (j = i + 1; j < len; j++) {
			if (p.mark[i] == p.mark[j])
				return false;
		}
	}
	return true;
}

int part1(char *ds) {
	int i;
	struct packet packet = {0, {'\0'}};

	for (i = 0; ds[i] != '\0'; i++) {
		pushpacket(&packet, SOPLEN, ds[i]);
		if (i > (SOPLEN - 1) && ismark(packet, SOPLEN))
			return ++i;	// result uses 1 based arrays
	}
	return -1;
}

int part2(char *ds) {
	int i;
	struct packet packet = {0, {'\0'}};

	for (i = 0; ds[i] != '\0'; i++) {
		pushpacket(&packet, SOMLEN, ds[i]);
		if (i > (SOMLEN - 1) && ismark(packet, SOMLEN))
			return ++i;	// result uses 1 based arrays
	}
	return -1;
}

int main() {
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	assert(part1("mjqjpqmgbljsphdztnvjfqwrcgsmlb") == 7);
	assert(part1("bvwbjplbgvbhsrlpgdmjqwftvncz") == 5);
	assert(part1("nppdvjthqldpwncqszvftbrmjlhg") == 6);
	assert(part1("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg") == 10);
	assert(part1("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw") == 11);

	assert(part2("mjqjpqmgbljsphdztnvjfqwrcgsmlb") == 19);
	assert(part2("bvwbjplbgvbhsrlpgdmjqwftvncz") == 23);
	assert(part2("nppdvjthqldpwncqszvftbrmjlhg") == 23);
	assert(part2("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg") == 29);
	assert(part2("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw") == 26);

	while ((nread = getline(&line, &len, stdin)) != -1) {
		int res;

		res = part1(line);
		printf("part1 num characters processed before first start-of-packet marker %d\n",
			res);
		res = part2(line);
		printf("part2 num characters processed before first start-of-message marker %d\n",
			res);
	}	
	free(line);
	return 0;
}
