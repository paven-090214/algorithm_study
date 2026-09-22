#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 20
#define INF INT_MAX
#define TRUE 1
#define FALSE 0

typedef struct GRAPH {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
}GRAPH;

int all_visited(GRAPH* g, int* visited);
void choose(GRAPH* g, int current, int* dist, int* visited);
int found(GRAPH* g, int* dist, int* visited);
void path(GRAPH* g, int* dist, int start, int finish, int* visited);

int main(void) {

	int start = 0, finish = 6;

	printf("start node : ");
	//scanf("%d", &start);
	printf("finish node : ");
	//scanf("%d", &finish);

	GRAPH g = {
		7, 
		{
			{0, 7, INF, INF, 3, 10, INF},
			{7, 0, 4, 10, 2, 6, INF},
			{INF, 4, 0, 2, INF, INF, INF},
			{INF, 10, 2, 0, 11, INF, 6},
			{3, 2, INF, 11, 0, INF, 5},
			{10, 6, INF, 9, INF, 0, INF},
			{INF, INF, INF, 4, 5, INF, 0}
		}
	};

	int* dist = malloc(sizeof(int) * g.n);
	int* visited = malloc(sizeof(int) * g.n);

	if (dist != NULL && visited != NULL) {
		for (int i = 0; i < g.n; i++) {
			dist[i] = INF;
			visited[i] = FALSE;
		}
	}
	else {
		printf("dist/visited malloc false");
	}

	path(&g, dist, start, finish, visited);
	free(dist);
	free(visited);
	return 0;
}

void status(GRAPH* g, int n, int current) {
	int* array = calloc(g->n, sizeof(int));
	if (array == NULL) {
		printf("calloc false");
		return;
	}

	printf("current node : %d\n", current);
	for (int i = 0; i < g->n; i++) {
		if (g->weight[current][i] == INF) {
			printf(" * ");
		}
		else {
			array[i] = g->weight[current][i];
			printf(" %d ", array[i]);
		}
	}
	printf("\n");
}

int all_visited(GRAPH* g, int* visited) {
	for (int i = 0; i < g->n; i++) {
		if (visited[i] == FALSE) {
			return FALSE;
		}
	}
	return TRUE;
}

void choose(GRAPH* g, int current, int* dist, int* visited) {
	for (int i = 0; i < g->n; i++) {
		if (g->weight[current][i] != INF && 
			dist[current] != INF &&
			g->weight[current][i] + dist[current] < dist[i])
		{
			dist[i] = g->weight[current][i] + dist[current];
		}
	}
}

int found(GRAPH* g, int* dist, int* visited) {
	int min = INF;
	int index = -1;
	for (int i = 0; i < g->n; i++) {
		if (min > dist[i] && visited[i] == FALSE) {
			min = dist[i];
			index = i;
		}
	}
	if (index == -1) {
		return index;
	}
	visited[index] = TRUE;
	printf("found node : %d\n", index);
	return index;
}

void path(GRAPH* g, int* dist, int start, int finish, int* visited) {
	dist[start] = 0;
	int next = found(g, dist, visited);
	for (int i = 0; i < g->n; i++) {
		status(g, g->n, i);
	}
	while (!all_visited(g, visited)) {
		choose(g, next, dist, visited);
		next = found(g, dist, visited);
	}
}