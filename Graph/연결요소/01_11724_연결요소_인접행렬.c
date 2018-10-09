#include<stdio.h>

int map[1001][1001];
int N, E, cnt;
int check[1001];
void dfs(int from) {
	check[from] = 1;
	for (int to = 1; to <= N; to++)
		if (check[to] == 0 && map[from][to]) {
			check[to] = 1;
			dfs(to);
		}
}

int main() {
	int cnt = 0;
	scanf("%d %d", &N, &E);
	for (int i = 0; i < E; i++) {
		int from, to;
		scanf("%d %d", &from, &to);
		map[from][to] = map[to][from] = 1;
	}

	for (int from = 1; from <= N; from++) {
		if (check[from] == 0) {
			cnt++;
			dfs(from);
		}
	}
	printf("%d\n", cnt);
	return 0;
}