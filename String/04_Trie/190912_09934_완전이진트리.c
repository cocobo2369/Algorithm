#include<stdio.h>
#define Max 1026
int K, N;
int num[Max];
int tree[Max], treeIdx = 1;

void make(int now) {
	if (now >= N)
		return;

	make(now * 2);
	tree[now] = num[treeIdx++];
	make(now * 2 + 1);

}

int main() {
	scanf("%d", &K);
	N = 1;
	N <<= K;
	for (int i = 1; i < N; i++)
		scanf("%d", &num[i]);

	make(1);

	int k = 2;
	for (int i = 1; i < N; i++) {
		printf("%d ", tree[i]);
		if (i == k - 1) {
			printf("\n");
			k <<= 1;
		}

	}
	return 0;
}