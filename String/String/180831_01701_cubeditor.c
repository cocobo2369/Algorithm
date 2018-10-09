#include<stdio.h>
#define Max 5001


char string[Max];
int N;



int suffixArr[Max];
int group[Max], newgroup[Max];

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
		group[N] = string[N] - 'a'; //소문자로만 이루어짐
		suffixArr[N] = N;
	}
	group[N] = -1;

	//2. 정렬하기
	int t = 1;
	while (t < N) {
		quick(0, N - 1, t);

		//3. 새그룹
		newgroup[suffixArr[0]] = 0;
		newgroup[N] = -1;
		for (int i = 1; i < N; i++) {
			if (cmp(suffixArr[i - 1], suffixArr[i], t))
				newgroup[suffixArr[i]] = newgroup[suffixArr[i - 1]] + 1;
			else
				newgroup[suffixArr[i]] = newgroup[suffixArr[i - 1]];
		}

		for (int i = 0; i < N; i++)
			group[i] = newgroup[i];
		t *= 2;
		if (newgroup[suffixArr[N - 1]] == N - 1)break;
	}
}

int lcp[Max], before[Max], plcp[Max],L;
int getlcp() {
	int max = 0;
	//1. 직전 suffixArr
	before[suffixArr[0]] = -1;
	for (int now = 1; now < N; now++)
		before[suffixArr[now]] = suffixArr[now - 1];

	//2. plcp[]
	for (int now = 0; now < N; now++) {
		if (before[now] == -1) {
			plcp[now] = 0; continue;
		}
		while (string[now + L] == string[before[now] + L])L++;
		max = max > L ? max : L;
		plcp[now] = L;
		if (L) L--;
	}
	//3. plcp를 기반으로 lcp 만들기
	for (int i = 0; i < N; i++)
		lcp[i] = plcp[suffixArr[i]];
	return max;
}


int main() {
	scanf("%s", &string);
	getSuffixArr();
	printf("%d\n", getlcp());
	return 0;
}