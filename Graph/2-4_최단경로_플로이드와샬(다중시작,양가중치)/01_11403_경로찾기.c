#include<stdio.h>
#define MaxV 101
#define INF 100000000//0x7fffffff 이면 덧셈에서 오버플로우나니까 적당히 큰값으로 
int map[MaxV][MaxV], dist[MaxV][MaxV];
int N;

void Floyd_Warshall() {
	
	for (int via = 1; via <= N; via++)
		for (int from = 1; from <= N; from++)
			for (int to = 1; to <= N; to++)
				if (dist[from][to] > dist[from][via] + dist[via][to])
					dist[from][to] = dist[from][via] + dist[via][to];
}

int main() {
	scanf("%d", &N);
	for (int y = 1; y <= N; y++)
		for (int x = 1; x <= N; x++) {
			scanf("%d", &map[y][x]);
			if(map[y][x] == 0)
				dist[y][x] = INF;
		}
	Floyd_Warshall();

	for (int f = 1; f <= N; f++) {
		for (int t = 1; t <= N; t++) printf("%d ", map[f][t] != INF ? 1 : 0);
		printf("\n");
	}
	return 0;
}