#include<stdio.h>
#define Max 1001
#define MaxE 100001
int T, N, E, W;
int time[Max];
int map[Max][Max];

//tplSort
int indegree[Max],
q[MaxE], in, out;
int totaltime[Max];
int tplSort() {
	for (int v = 1; v <= N; v++)
		if (indegree[v] == 0) {
			q[in++] = v;
			totaltime[v] += time[v];
		}

	while (in != out) {
		int from = q[out++];

		for (int to = 1; to <= N; to++) {
			if (map[from][to] == 1) {
				indegree[to]--;
				totaltime[to] = totaltime[to] > totaltime[from] + time[to] ?
					totaltime[to] : totaltime[from] + time[to];
				if (indegree[to] == 0)
					q[in++] = to;
			}
		}
	}
	return totaltime[W];
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &N, &E);
		for (int v = 1; v <= N; v++)
			scanf("%d", &time[v]);
		for (int v = 1; v <= E; v++) {
			int from, to;
			scanf("%d %d", &from, &to);
			if (map[from][to] == 0) {
				map[from][to] = 1;
				indegree[to]++;
			}
		}
		scanf("%d", &W);
		printf("%d\n", tplSort());

		in = out = 0;
		for (int y = 1; y <= N; y++) {
			indegree[y] = time[y] = totaltime[y] = 0;
			for (int x = 1; x <= N; x++)
				map[y][x] = 0;
		}
	}
	return 0;
}