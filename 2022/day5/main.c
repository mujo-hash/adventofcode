#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef char crate;

struct stack {
	int top;
	crate crates[MAX];
};

struct stack testinput[] = {
	{1, {'Z', 'N'}},
	{2, {'M', 'C', 'D'}},
	{0, {'P'}}};

struct stack input[] = {
	{7, {'T', 'P', 'Z', 'C', 'S', 'L', 'Q', 'N'}},
	{6, {'L', 'P', 'T', 'V', 'H', 'C', 'G'}},
	{3, {'D', 'C', 'Z', 'F'}},
	{7, {'G', 'W', 'T', 'D', 'L', 'M', 'V', 'C'}},
	{2, {'P', 'W', 'C'}},
	{7, {'P', 'F', 'J', 'D', 'C', 'T', 'S', 'Z'}},
	{4, {'V', 'W', 'G', 'B', 'D'}},
	{5, {'N', 'J', 'S', 'Q', 'H', 'W'}},
	{6, {'R', 'C', 'Q', 'F', 'S', 'L', 'V'}}};

crate pop(struct stack *s) {
	crate c;

	c = s->crates[s->top];
	s->top--;
	return c;
}

void push(struct stack *s, crate c) {
	s->crates[s->top + 1] = c;
	s->top++;
}

void printstacks(struct stack s[], int nstacks) {
	int i, j;

	for (i = 0; i < nstacks; i++) {
		for (j = 0; j <= s[i].top; j++) {
			printf("[%c] ", s[i].crates[j]);
		}
		printf("\n");
	}
}

void movecrates(struct stack stacks[], int ncrates, int from, int to) {
	int i;

	for (i = 0; i < ncrates; i++) {
		crate c;

		c = pop(&stacks[from]);
		push(&stacks[to], c);
	}
}


int main() {
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while ((nread = getline(&line, &len, stdin)) != -1) {
		int n, from, to;

		sscanf(line, "move %d from %d to %d", &n, &from, &to);
		movecrates(input, n, --from, --to); // 0-indexes but input assumes 1-based indexes
	}
	free(line);
	printstacks(input, sizeof(input)/sizeof(input[0]));

	// movecrates(testinput, 1, 1, 0);
	// movecrates(testinput, 3, 0, 2);
	// movecrates(testinput, 2, 1, 0);
	// movecrates(testinput, 1, 0, 1);
	// printstacks(testinput, 3);

	return 0;
}
