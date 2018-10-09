#include<stdio.h>
#define MaxN 1000001
int root[MaxN];
int N, M;
void make(int n) {
	for (int i = 0; i <= n; i++)
		root[i] = i;
}

int Find(int x) {
	if (x == root[x]) 
		return x;
	else 
		return root[x] = Find(root[x]);
}

void Union(int main, int sub) {
	root[Find(sub)] = Find(main);
}

int main() {
	scanf("%d %d", &N, &M);
	make(N);
	while (M--) {
		int cmd, a, b;
		scanf("%d %d %d", &cmd, &a, &b);
		if (cmd)
			printf("%s\n", Find(a) == Find(b) ? "YES" : "NO");
		else
			Union(a, b);
	}
	return 0;
}