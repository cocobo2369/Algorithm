//¸øÇ¯
#include<stdio.h>
#define MAX 100001
int T, V;
int student[MAX],
check[MAX],
departure[MAX];

int dfs(int from, int cnt, int start) {
	if (check[from] != 0) {
		if (start != departure[from])
			return 0;
		return cnt - check[from];
	}
	check[from] = cnt;
	departure[from] = start;
	return dfs(student[from], cnt + 1, start);
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &V);
		for (int v = 1; v <= V; v++) {
			scanf("%d", &student[v]);
			check[v] = departure[v] = 0;
		}
		int cycleNode = 0;
		for (int v = 1; v <= V; v++) {
			if (check[v] == 0) {
				cycleNode += dfs(v, 1, v);
			}
		}
		printf("%d\n", V-cycleNode);
	}
	return 0;
}