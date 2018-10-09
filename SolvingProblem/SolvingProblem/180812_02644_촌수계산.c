#include<stdio.h>
#define Max 101

int map[Max][Max];
int check[Max];
int N, S, F, E;

int q[Max*Max], in, out;
int bfs(int start) {
	q[in++] = start;
	check[start] = 1;

	while (in != out) {
		int from = q[out++];

		if (from == F)
			return check[from]-1;

		for (int to = 1; to <= N; to++) {
			if (map[from][to] == 1 && check[to] == 0) {
				q[in++] = to;
				check[to] = check[from] + 1;
			}
		}
	}
	return -1;
}

int main() {
	scanf("%d %d %d %d", &N, &S, &F, &E);
	while (E--) {
		int p, c;
		scanf("%d %d", &p, &c);
		map[p][c] = map[c][p] = 1;
	}
	printf("%d\n", bfs(S));
	return 0;
}