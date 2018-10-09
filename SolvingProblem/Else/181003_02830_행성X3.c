#include<stdio.h>
#define Max 1000001
int N, num[Max];
int main() {
	scanf("%d", &N);
	int ans = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d", &num[i]);
		ans += num[i];
	}
	ans = ans^ans;
	printf("%d\n", ans);
	return 0;
}