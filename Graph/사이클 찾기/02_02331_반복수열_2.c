#include<stdio.h>
int map[300000];
int check[300000];
int A, P;
int cal(int a, int p) {
	int aa[7], i, res = 0;
	for (i = 0; a; i++) {
		aa[i] = a % 10;
		a /= 10;
	}

	for (int j = 0; j < i; j++) {
		int v = 1;
		for (int k = 0; k < p; k++)
			v *= aa[j];
		res += v;
	}
	return res;
}

int dfs(int from,int cnt) {
	if (check[from] != 0)
		return check[from] - 1;

	check[from] = cnt;

	return dfs(cal(from, P), cnt + 1);
}

int main() {
	scanf("%d %d", &A, &P);
	printf("%d\n", dfs(A, 1));
	return 0;
}