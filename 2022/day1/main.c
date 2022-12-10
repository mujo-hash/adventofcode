#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>

int findindexofmax(int arr[], size_t len) {
	int tmp, max, index;

	index = 0;
	tmp = max = arr[0];
	for (int i = 0; i < len; i++) {
		tmp = arr[i];
		max = MAX(tmp, max);
		if (tmp == max)
			index = i;
	}
	return index;
}


int main() {
	char *line = NULL;
	size_t len = 0;
	ssize_t nread = 0;
	int cal[BUFSIZ] = {0};
	int i = 0;
	int max = 0;
	int imax;
	int sum = 0;

	while ((nread = getline(&line, &len, stdin)) != -1) {
		int n, res;

		res = sscanf(line, "%d", &n);
		if (res < 0) {
			i++;
			continue;
		}
		cal[i] += n;
	}
	i++;
	free(line);

	imax = findindexofmax(cal, i);
	max = cal[imax];
	printf("max calories in inventory is: %d\n", max);

	sum = max;
	cal[imax] = 0;
	imax = findindexofmax(cal, i);
	sum += cal[imax];

	cal[imax] = 0;
	imax = findindexofmax(cal, i);
	sum += cal[imax];

	printf("sum of top 3 calories in inventory is: %d\n", sum);

	return 0;
}
