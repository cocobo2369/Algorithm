#include<stdio.h>
#define MaxN 101
int N, M;
char root[MaxN];
void make(int n) {
	for (int i = 1; i <= n; i++)
		root[i] = i;
}

int Find(int x) {
	if (x == root[x]) return x;
	else return root[x] = Find(root[x]);
}

void Union(int main, int sub) {
	return root[Find(sub)] = Find(main);
}

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	make(N);
	while (M--) {
		int m, s;
		scanf("%d %d", &m, &s);
		Union(m, s);
}

	int cnt = 0, u = Find(1);
	for (int i = 2; i <= N; i++) {
		if (u == Find(i))cnt++;
	}
	printf("%d\n", cnt);
	return 0;
}