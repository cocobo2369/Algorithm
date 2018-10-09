#include<stdio.h>
#define Max 100001*2
int max;
int group[Max];
//1. 비교
int cmp(int small, int big, int t) {
	if (group[small] != group[big])
		return group[small] < group[big];
	else
		return group[small + t] < group[big + t];
}

//2. 정렬
int suffixArr[Max];
void quick(int above, int below, int t) {

	if (above >= below) return;

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

//3. 만들기
int newgroup[Max];
char string[Max];
int midN,N;
void getsuffixArr() {

	//1. 초기화
	for (int i = 0; i < N; i++) {
		suffixArr[i] = i;
		group[i] = string[i];
	}
	group[N] = -1;

	//2.정렬
	int t = 1;
	while (t < N) {
		quick(0, N - 1, t);

		//3. newgroup
		newgroup[suffixArr[0]] = 0;
		newgroup[N] = -1;
		for (int now = 1; now < N; now++) {
			if (cmp(suffixArr[now - 1], suffixArr[now], t))
				newgroup[suffixArr[now]] = newgroup[suffixArr[now - 1]] + 1;
			else
				newgroup[suffixArr[now]] = newgroup[suffixArr[now - 1]];
		}

		for (int i = 0; i < N; i++)
			group[i] = newgroup[i];
		t *= 2;
		if (group[suffixArr[N - 1]] == N - 1)break;
	}
}

//lcp
int before[Max], plcp[Max], lcp[Max];
void getlcp() {
	before[suffixArr[0]] = -1;
	for (int i = 1; i < N; i++)
		before[suffixArr[i]] = suffixArr[i - 1];

	int L = 0;
	for (int now = 0; now < N; now++) {
		if (before[now] == -1) {
			plcp[now] = 0;
			continue;
		}
		while (string[now + L] == string[before[now] + L])L++;
		if ((long long )(now - midN)*(before[now] - midN) < 0)
			max = max > L ? max : L;
		plcp[now] = L;
		if (L)
			L--;
	}
	for (int i = 0; i < N; i++)
		lcp[i] = plcp[suffixArr[i]];
}

int main() {
	scanf("%s", string);
	for (midN = 0; string[midN]; midN++);
	string[midN] = 1;
	for (int i = 1; i <=midN; i++) {
		string[midN + i] = string[midN - i];
	}
	N = midN * 2 + 1;
	getsuffixArr();
	getlcp();

	printf("%d\n", max);
	return 0;
}
