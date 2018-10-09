#include<stdio.h>
#define MaxV 401
#define MaxE 400*400
#define INF 400*10000

int V, E,
	dist[MaxV][MaxV];
//spfa는 사이클은 못찾는 듯 하다.
int FloydW() {
	for (int via = 1; via <= V; via++) {
		for (int from = 1; from <= V; from++) {
			for(int to = 1; to <= V;to++){
				if (dist[from][to] > dist[from][via] + dist[via][to])
					dist[from][to] = dist[from][via] + dist[via][to];
			}
		}
	}

	int min = INF;
	for (int i = 1; i <= V; i++)
		min = min < dist[i][i] ? min : dist[i][i];
	return min = min >= INF ? -1 : min;
}

int main() {
	scanf("%d %d", &V, &E);

	for (int from = 1; from <= V; from++)
		for (int to = 1; to <= V; to++)
			dist[from][to] = INF;

	while (E--) {
		int f, t, c;
		scanf("%d %d %d", &f, &t, &c);
		dist[f][t] = dist[f][t] < c ? dist[f][t] : c; // 이거 체크 중요
	}

	printf("%d\n", FloydW());
	return 0;
}