#include<stdio.h>
#define MaxN 200
#define MaxM 1000
int N, M;

int set[MaxN+1];

void makeSet() {
	for (int i = 0; i <= N; i++)
		set[i] = i;
}

int find(int n) {
	if (set[n] == n)
		return n;
	else
		return set[n] = find(set[n]);
}

void Union(int main, int sub) {
	main = find(main);
	sub = find(sub);
	if (main > sub) {
		int temp = main;
		main = sub;
		sub = temp;
	}
	set[sub] = main;
}

int main() {
	scanf("%d %d", &N, &M);
	makeSet();
	for (int y = 1; y <= N; y++)
		for (int x = 1; x <= N; x++) {
			int n;
			scanf("%d", &n);
			if (n)
				Union(y, x);
		}

	int root, is = 0, num;
	scanf("%d", &root);
	root = find(root);
	for (int i = 1; i < M; i++) {
		scanf("%d", &num);
		if (root == set[num])continue;
		is = 1;
	}
	printf("%s\n", is == 0 ? "YES": "NO");
	return 0;
}