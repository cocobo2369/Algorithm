#include<stdio.h>
#define MaxV 101
#define INF 100000000
int N, E;
int map[MaxV][MaxV];
int dist[MaxV][MaxV];

void Floyd_Warshall() {

	for (int via = 1; via <= N; via++)
		for (int from = 1; from <= N; from++)
			for (int to = 1; to <= N; to++)
				if (dist[from][to] > dist[from][via] + dist[via][to]) {
					dist[from][to] = dist[from][via] + dist[via][to];
				}
}

int main() {
	scanf("%d %d", &N, &E);

	for (int y = 1; y <= N; y++)
		for (int x = 1; x <= N; x++)
			if (y == x) dist[y][x] = 0;
			else dist[y][x] = INF;

	while (E--) {
		int f, t, c;
		scanf("%d %d %d", &f, &t, &c);
		dist[f][t] = dist[f][t] < c ? dist[f][t] : c;
	}
	Floyd_Warshall();

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++)
			printf("%d ", dist[y][x] >= INF ? 0 : dist[y][x]);
		printf("\n");
	}
	return 0;
}