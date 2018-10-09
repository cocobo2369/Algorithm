#include<stdio.h>
int map[300000];
int check[300000];
int A, P;
int cal(int a, int p) {
	int aa[7], i,res = 0;
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
int cnt,end;
int dfs(int from) {
	cnt++;
	check[from] = 1;
	int next = cal(from, P);
	if (check[next] == 0) {
		if (dfs(next)) { //교훈 next를 기준삼았으니까 next에 대해서 처리하자
			if (next == end)
				return 0;
			else {
				cnt--;
				return 1;
			}
		}
	}
	else {
		cnt--;
		end = next;
		return 1;
	}
	return 0;
}

int main() {
	scanf("%d %d", &A, &P);
	dfs(A);
	printf("%d\n", cnt);
	return 0;
}