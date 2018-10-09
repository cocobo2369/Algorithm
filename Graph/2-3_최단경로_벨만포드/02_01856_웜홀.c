#include<stdio.h>
#define MaxV 501
#define MaxE 2501
#define MaxW 201
#define INF 0x7fffffff

int T, V, E, W;

typedef struct edge {
	int f;
	int t;
	int c;
}Edge;
Edge edge[MaxE * 2], wormhole[MaxW];

int dist[MaxV];

int bellman(int start) {
	dist[start] = 0;

	int n_cycle = 0;

	for (int n = 1; n <= V; n++) {
		int from, to, cost;
		for (int e = 1; e <= E * 2; e++) {
			from = edge[e].f;
			to = edge[e].t;
			cost = edge[e].c;

			if (dist[from] != INF) {
				if (dist[to] > dist[from] + cost) {
					dist[to] = dist[from] + cost;
				}
			}
		}
		for (int w = 1; w <= W; w++) {
			from = wormhole[w].f;
			to = wormhole[w].t;
			cost = wormhole[w].c;

			if (dist[from] != INF) {
				if (dist[to] > dist[from] + cost) {
					dist[to] = dist[from] + cost;
					if (n == V) {
						n_cycle = 1;
						return n_cycle;
					}
				}
			}

		}
	}
	return n_cycle;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &V, &E, &W);

		for (int i = 1; i <= V; i++)
			dist[i] = INF;

		int f, t, c;
		for (int i = 1; i <= E * 2; i += 2) {
			scanf("%d %d %d", &f, &t, &c);
			edge[i].f = f, edge[i].t = t, edge[i].c = c;
			edge[i + 1].f = t, edge[i + 1].t = f, edge[i + 1].c = c; //¾ç¹æÇâ

		}
		for (int i = 1; i <= W; i++) {
			scanf("%d %d %d", &f, &t, &c);
			wormhole[i].f = f;
			wormhole[i].t = t;
			wormhole[i].c = c*-1;
		}

		printf("%s\n", bellman(1) == 1 ? "YES" : "NO");
	}
	return 0;
}