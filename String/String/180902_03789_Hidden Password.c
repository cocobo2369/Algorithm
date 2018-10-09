#include<stdio.h>
#define Max 200002
int T,n, N;
//이번에는 같은문자열은 딱붙여버리고 마지막꺼는 뗀다

char string[Max];

int group[Max], newgroup[Max];
int suffixArr[Max];

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
		if (left >= right)
			break;
		int temp = suffixArr[left];
		suffixArr[left] = suffixArr[right];
		suffixArr[right] = temp;
	}
	//이부분을 뺐을 줄이야....
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
		if (L) //주의해라
			L--;
	}

	for (int i = 0; i < N; i++)
		lcp[i] = plcp[suffixArr[i]];
}



int main() {
	scanf("%d\n", &T);
	while (T--) {
		scanf("%d\n%s",&n, string);
		N = 2 * n - 1;
		for (int i = n; i < N; i++)
			string[i] = string[i - n];

		getsuffixArr();
		getlcp();

		int ans = 0;
		for (int i = 0; i < N; i++) {
			if (suffixArr[i] < n) {
				ans = i;
				break;
			}
			
		}
		for (int i = ans+1; i < N; i++) {
			if (suffixArr[i] < n && lcp[i] >= n)
				ans = i;
			else break;
		}

		printf("%d\n", suffixArr[ans]);
	}
	return 0;
}