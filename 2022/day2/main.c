#include <stdio.h>
#include <stdlib.h>

int winner(char opp, char self) {
	int sum;

	switch (opp) {
	case 'A':
		switch (self) {
		case 'X':
			sum = 3; // draw
			break;
		case 'Y':
			sum = 6; //win
			break;
		case 'Z':
			sum = 0; //loss
			break;
		}
		break;
	case 'B':
		switch (self) {
		case 'X':
			sum = 0; // loss
			break;
		case 'Y':
			sum = 3; // draw
			break;
		case 'Z':
			sum = 6; // win
			break;
		}
		break;
	case 'C':
		switch (self) {
		case 'X':
			sum = 6; // win
			break;
		case 'Y':
			sum = 0; //loss
			break;
		case 'Z':
			sum = 3; //draw
			break;
		}
		break;
	default:
		printf("error\n");
	}
	
	return sum;
}

int hand(char opp, char self) {
	int sum;

	switch (opp) {
	case 'A':
		sum = 1;
		break;
	case 'B':
		sum = 2;
		break;
	case 'C':
		sum = 3;
		break;
	default:
		printf("error\n");
	}

	sum = 0;
	switch (self) {
	case 'X':
		sum += 1;
		break;
	case 'Y':
		sum += 2;
		break;
	case 'Z':
		sum += 3;
		break;
	default:
		printf("error\n");
	}

	return sum;
}

int score1(char strat[][2], int rows) {
	int i, sum;

	sum = 0;
	for (i = 0; i < rows; i++) {
		sum += hand(strat[i][0], strat[i][1]);
		sum += winner(strat[i][0], strat[i][1]);
	}
	return sum;
}

int score2(char strat[][2], int rows) {
	int i, sum;

	sum = 0;
	for (i = 0; i < rows; i++) {
		sum += hand(strat[i][0], strat[i][1]);
		sum += winner(strat[i][0], strat[i][1]);
	}
	return sum;
}

int main() {
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int i, nlines;

	char strat[BUFSIZ][2];

	for (i = 0; (nread = getline(&line, &len, stdin)) != -1; i++) {
		int res;

		res = sscanf(line, "%c %c", &strat[i][0], &strat[i][1]);
	}
	free(line);
	nlines = i++;

	printf("total score from guide: %d\n", score1(strat, nlines));
	printf("total score from guide two: %d\n", score2(strat, nlines));
	return 0;
}

