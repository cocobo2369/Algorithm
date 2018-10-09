#include<stdio.h>

#define Max 500001

char string[Max];
int N;
int suffixArr[Max],
	group[Max], newgroup[Max];

int before[Max], lcp[Max], plcp[Max];

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

void getSuffixArr() {
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

		//3. 새그룹 만들기
		newgroup[suffixArr[0]] = 0;
		newgroup[N] = -1;
		for (int i = 1; i< N; i++)
			if (cmp(suffixArr[i - 1], suffixArr[i],t))
				newgroup[suffixArr[i]] = newgroup[suffixArr[i - 1]] + 1;
			else
				newgroup[suffixArr[i]] = newgroup[suffixArr[i - 1]];

		for (int i = 0; i < N; i++)
			group[i] = newgroup[i];
		t *= 2;
	}
}

void getlcp() {

	//1. before[]
	before[suffixArr[0]] = -1;
	for (int i = 1; i < N; i++)
		before[suffixArr[i]] = suffixArr[i - 1];

	//2. plcp[]
	for (int now = 0, L = 0; now < N; now++) {
		if (before[now] == -1)plcp[now] = 0;
		while (string[now + L] == string[before[now] + L])L++;
		plcp[now] = L;
		L = L - 1 > 0 ? L - 1 : 0;
	}

	//3. lcp[]
	for (int i = 0; i < N; i++)
		lcp[i] = plcp[suffixArr[i]];
}

int main() {
	scanf("%s", string);
	getSuffixArr();
	getlcp();
	for (int i = 0; i < N; i++)
		printf("%d ", suffixArr[i]+1);
	printf("\nx ");
	for (int i = 1; i < N; i++)
		printf("%d ", lcp[i]);
	printf("\n");
	return 0;
}