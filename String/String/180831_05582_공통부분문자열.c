#include<stdio.h>
#define Max 4001

char string[Max * 2];
int n, N;

int suffixArr[Max * 2];
int group[Max * 2], newgroup[Max * 2];

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

		while(cmp(suffixArr[++left], pivot, t));
		while(cmp(pivot, suffixArr[--right], t));

		if (left >= right)
			break;
		int temp = suffixArr[left];
		suffixArr[left] = suffixArr[right];
		suffixArr[right] = temp;
	}
	quick(above, left - 1, t);
	quick(right + 1, below, t);
}

void getsuffixArr() {
	for (int i = 0; i < N; i++) {
		group[i] = string[i];
		suffixArr[i] = i;
	}
	group[N] = -1;

	int t = 1;
	while (t < N) {
		quick(0, N - 1, t);

		newgroup[suffixArr[0]] = 0;
		newgroup[N] = -1;
		for (int now = 1; now < N; now++)
			if (cmp(suffixArr[now - 1], suffixArr[now], t))
				newgroup[suffixArr[now]] = newgroup[suffixArr[now - 1]] + 1;
			else
				newgroup[suffixArr[now]] = newgroup[suffixArr[now - 1]];

		for (int i = 0; i < N; i++)
			group[i] = newgroup[i];
		t *= 2;
		if (group[suffixArr[N - 1]] == N - 1)break;
	}
}


int before[Max * 2], plcp[Max * 2], lcp[Max * 2];

int getlcp() {
	int max = 0;
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
		if ((now- n)*(before[now] - n) < 0) // 처음 길이 n 보다 작은 접미사 ,n보다 큰 접미사일 경우만 max 비교
			max = max > L ? max : L;
		plcp[now] = L;
		if (L)
			L--;
	}
	for (int i = 0; i < N; i++)
		lcp[i] = plcp[suffixArr[i]];
	return max;
}
int main() {
	scanf("%s", string);
	for (n = 0; string[n]; n++);
	string[n] = 1; // '\0' = 0 이니까 다음 문자가 뭔진몰라도 ascii값 1을 넣어준다.
	scanf("%s", &string[n + 1]);
	for (N = n + 1; string[N]; N++);

	getsuffixArr();
	printf("%d\n", getlcp());

	return 0;
}