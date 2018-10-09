#include<stdio.h>

int N, dist[21][21];

int main() {
	scanf("%d", &N);
	for (int y = 1; y <= N; y++)
		for (int x = 1; x <= N; x++)
			scanf("%d", &dist[y][x]);

	int sum = 0;
	for (int via = 1; via <= N; via++)
		for (int from = 1; from <= N; from++)
			for (int to = 1; to <= N; to++)
			{
				if (dist[from][to] == 0 || dist[from][via] == 0 || dist[via][to] == 0)continue;
				if (dist[from][to] > (dist[from][via] + dist[via][to])) { //최소라했는데 이런게 있을 수 없다
					printf("-1\n");
					return 0;
				}
				if (dist[from][to] == (dist[from][via] + dist[via][to]))
					dist[from][to] = 0;
			}
	for (int y = 1; y <= N; y++)
		for (int x = y; x <= N; x++)
			sum += dist[y][x];
	printf("%d\n", sum);
	return 0;
}