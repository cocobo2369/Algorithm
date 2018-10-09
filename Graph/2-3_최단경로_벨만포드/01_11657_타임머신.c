#include<stdio.h>
#define MaxV 501
#define MaxE 6001
#define INF 0x7fffffff
typedef struct edge {
	int f;
	int t;
	int c;
}Edge;
Edge edge[MaxE];
int dist[MaxV];

int V, E;
//시작점부터 차근차근 나가는 알고리즘이 아니다.
//
int bellman(int start) {
	int negative_cycle = 0;
	for (int i = 1; i <= V; i++)
		dist[i] = INF;
	dist[start] = 0;

	for (int n = 1; n <= V; n++) {
		for (int e = 1; e <= E; e++) {
			int from = edge[e].f,
				to = edge[e].t,
				cost = edge[e].c;
			if (dist[from] != INF) {
				if (dist[to] > dist[from] + cost) {
					dist[to] = dist[from] + cost;
					if (n == V)
						negative_cycle = 1;
				}
			}
		}
	}
		return negative_cycle;
}

int main() {
	scanf("%d %d", &V, &E);

	for (int e = 1; e <= E; e++) {
		int f, t, c;
		scanf("%d %d %d", &f, &t, &c);
		edge[e].f = f;
		edge[e].t = t;
		edge[e].c = c;
	}
	if (bellman(1))
		printf("-1\n");
	else
		for(int i = 2;i<=V;i++)
			printf("%d\n", dist[i] == INF ? -1 : dist[i]);
	return 0;
}