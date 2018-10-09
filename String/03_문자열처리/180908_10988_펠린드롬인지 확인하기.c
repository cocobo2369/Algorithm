#include<stdio.h>

#define Max 101 *2

int group[Max],newgroup[Max];

int cmp(int small, int big, int t) {
	if (group[small] != group[big])
		return group[small] < group[big];
	else
		return group[small + t] < group[big + t];
}

int suffixArr[Max];
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

int N;
char string[Max];
void getsuffixArr() {
	//1. group, suffixArr 초기화
	for (int i = 0; i<N; i++) {
		suffixArr[i] = i;
		group[i] = string[i];
	}
	group[N] = -1;


	int t = 1;
	while (t < N) {
		//2. 정렬
		quick(0, N - 1, t);

		//3. newgroup
		newgroup[suffixArr[0]] = 0;
		newgroup[N] = -1;

		for (int i = 1; i < N; i++) {
			if (cmp(suffixArr[i - 1], suffixArr[i], t))
				newgroup[suffixArr[i]] = newgroup[suffixArr[i - 1]] + 1;
			else
				newgroup[suffixArr[i]] = newgroup[suffixArr[i - 1]];
		}


		//4. 복사
		for (int i = 0; i < N; i++)
			group[i] = newgroup[i];

		t *= 2;
		if (group[suffixArr[N - 1]] == N - 1)break;
	}

}

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
		plcp[now] = L;
		if (L)
			L--;
	}

	for (int i = 0; i < N; i++)
		lcp[i] = plcp[suffixArr[i]];
}

int main() {

	scanf("%s", string);
	for (N = 0; string[N]; N++);
	string[N] = 1;
	for (int i = 0; i < N; i++)
		string[i + N + 1] = string[N - 1 - i];
	N = 2 * N + 1;
	getsuffixArr();
	getlcp();

	int ans = 0;
	for (int i = 0; i < N; i++)
		if (lcp[i] == (N - 1) / 2) {
			ans = 1;
			break;
		}
	printf("%d\n", ans);
	return 0;
}