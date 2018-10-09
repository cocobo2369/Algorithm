#include<stdio.h>
#define MaxV 101
#define INF 100000000
int N, E;
int map[MaxV][MaxV];
int dist[MaxV][MaxV];
int course[MaxV][MaxV];
void Floyd_Warshall() {

	for (int via = 1; via <= N; via++)
		for (int from = 1; from <= N; from++)
			for (int to = 1; to <= N; to++)
				if (dist[from][to] > dist[from][via] + dist[via][to]) {
					dist[from][to] = dist[from][via] + dist[via][to];
					course[from][to] = via;
				}
}

int cnt, c[MaxV];
int go(int from, int to) {
	if (course[from][to] == 0)
		return cnt;

	go(from, course[from][to]);
	c[cnt] = course[from][to];
	cnt++;
	go(course[from][to], to);
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
			printf("%d ", dist[y][x]);
		printf("\n");
	}

	for(int from = 1; from <= N;from ++)
		for (int to = 1; to <= N; to++) {
			if (dist[from][to] ==0 || dist[from][to] >= INF )
				printf("0\n");
			else {
				cnt = 0;
				go(from, to);
				printf("%d ", cnt+2);
				printf("%d ", from);
				for (int i = 0; i < cnt; i++)
					printf("%d ", c[i]);
				printf("%d\n", to);
			}
		}

	return 0;
}