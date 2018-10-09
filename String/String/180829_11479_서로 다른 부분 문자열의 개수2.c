#include<stdio.h>

#define Max 1000001

char string[Max];
int N;
int suffixArr[Max],
	group[21][Max];
int cmp(int small, int big, int t, int gt) {
	if (group[gt][small] != group[gt][big])
		return group[gt][small] < group[gt][big];
	else
		return group[gt][small + t] < group[gt][big + t];
}

void quick(int above, int below, int t, int gt) {
	if (above >= below)
		return;

	int left = above - 1,
		right = below + 1,
		pivot = suffixArr[left + (right - left) / 2];

	while (left < right) {

		while (cmp(suffixArr[++left], pivot, t,gt));
		while (cmp(pivot, suffixArr[--right],t,gt));

		if (left >= right)break;
		int temp = suffixArr[left];
		suffixArr[left] = suffixArr[right];
		suffixArr[right] = temp;
	}
	quick(above, left - 1, t,gt);
	quick(right + 1, below, t,gt);
}


long long getlcp(int gt) {

	long long total = (long long)N*(N+1)/2; //주의

	for (int i = 1; i < N; i++) {
		int s1 = suffixArr[i - 1],
			s2 = suffixArr[i],
			t = gt;
		while (s1 < N && s2 < N && t >= 0) {
			if (group[t][s1] == group[t][s2]) {
				total -= (long long)(1 << t);
				s1 += (1 << t);
				s2 += (1 << t);
			}
			t -= 1;
		}


	}
	return total;
}

long long getSuffixArr() {

	int gt = 0;
	//1. 초기화
	for (N = 0; string[N]; N++) {
		suffixArr[N] = N;
		group[gt][N] = string[N]-'a';
	}
	group[gt][N] = -1;
	
	//2. 정렬
	int t = 1;
	while (t < N) {
		quick(0, N - 1, t,gt);

		gt++;
		group[gt][suffixArr[0]] = 0;
		
		for (int i = 1; i < N; i++)
			if (cmp(suffixArr[i - 1], suffixArr[i], t,gt-1))
				group[gt][suffixArr[i]] = group[gt][suffixArr[i - 1]] + 1;
			else
				group[gt][suffixArr[i]] = group[gt][suffixArr[i-1]];
		group[gt][N] = -1;
		
		t *= 2;
	}

	return getlcp(gt);
}


int main() {
	scanf("%s", &string);
	printf("%lld\n",getSuffixArr());

	return 0;
}