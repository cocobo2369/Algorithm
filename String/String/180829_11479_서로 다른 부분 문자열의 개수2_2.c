#include<stdio.h>

#define Max 1000001

char string[Max];
int N;
int suffixArr[Max],group[Max],newgroup[Max];
int cmp(int small, int big, int t) {
	if (group[small] != group[big])
		return group[small] < group[big];
	else
		return group[small + t] < group[big + t];
}

void quick(int above, int below, int t) {
	if (above >= below)
		return;

	int left = above - 1,
		right = below + 1,
		pivot = suffixArr[left + (right - left) / 2];

	while (left < right) {

		while (cmp(suffixArr[++left], pivot, t));
		while (cmp(pivot, suffixArr[--right], t));

		if (left >= right)break;
		int temp = suffixArr[left];
		suffixArr[left] = suffixArr[right];
		suffixArr[right] = temp;
	}
	quick(above, left - 1, t);
	quick(right + 1, below, t);
}

int lcp[Max], plcp[Max],before[Max];
long long getlcp() {
	long long total = (long long)N*(N + 1) / 2;
	//1. 직전 접미사를 담은 배열 만들기
	before[suffixArr[0]] = -1;
	for (int i = 1; i < N; i++)
		before[suffixArr[i]] = suffixArr[i - 1];
	//2. plcp 활용
	for (int i = 0, L = 0; i < N; i++) {
		if (before[i] == -1)plcp[i] = 0;
		while (string[i + L] == string[before[i] + L])L++;
		plcp[i] = L;
		total -= L;
		L = L - 1 > 0 ? L - 1 : 0;
	}
	//3. plcp를 기반으로 lcp 만들기
	for (int i = 0; i < N; i++)
		lcp[i] = plcp[suffixArr[i]];
	return total;
}

void getSuffixArr() {

	int gt = 0;
	//1. 초기화
	for (N = 0; string[N]; N++) {
		suffixArr[N] = N;
		group[N] = string[N] - 'a';
	}
	group[N] = -1;

	//2. 정렬
	int t = 1;
	while (t < N) {
		quick(0, N - 1, t);
		newgroup[suffixArr[0]] = 0;
		newgroup[N] = -1;
		for (int i = 1; i < N; i++)
			if (cmp(suffixArr[i - 1], suffixArr[i], t))
				newgroup[suffixArr[i]] = newgroup[suffixArr[i - 1]] + 1;
			else
				newgroup[suffixArr[i]] = newgroup[suffixArr[i - 1]];
		
		for (int i = 0; i < N; i++)
			group[i] = newgroup[i];

		t *= 2;
	}

	return;
}


int main() {
	scanf("%s", &string);
	getSuffixArr();
	printf("%lld\n", getlcp());

	return 0;
}