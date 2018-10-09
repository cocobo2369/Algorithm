#include<stdio.h>
#define Max 100001
int check[Max];
int q[Max], in, out;

int N, K;

int bfs(int start) {
	q[in++] = start;
	check[start] = 1;

	while (in != out) {
		int from = q[out++];
		if (from == K)
			return check[from];
		int to = from - 1;
		if (to >= 0) {
			if (check[to] == 0) {
				q[in++] = to;
				check[to] = check[from] + 1;
			}
		}
		to = from + 1;
		if (to < Max) {
			if (check[to] == 0) {
				q[in++] = to;
				check[to] = check[from] + 1;
			}
		}
		to = from * 2;
		if (to < Max) {
			if (check[to] == 0) {
				q[in++] = to;
				check[to] = check[from] + 1;
			}
		}
	}
}
int main() {
	scanf("%d %d", &N, &K);
	printf("%d\n", bfs(N)-1);
	return 0;
}