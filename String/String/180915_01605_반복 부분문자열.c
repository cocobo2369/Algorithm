//suffixArray_03033_가장 긴 문자열
#include<stdio.h>
#define Max 200001//

//1.cmp
int group[Max];
int cmp(int small, int big, int t) {
	if (group[small] != group[big])
		return group[small] < group[big];
	else
		return group[small + t] < group[big + t];
}

//2. quick
int suffixArr[Max];
void quick(int above, int below, int t) {
	if (above >= below)return;

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

//3. suffixArr
char string[Max];
int N;

int newgroup[Max];
void getsuffixArr() {

	//1)초기화
	for (int i = 0; i < N; i++) {
		group[i] = string[i];
		suffixArr[i] = i;
	}
	group[N] = -1; //

				   //2)정렬
	int t = 1;
	while (t < N) {

		quick(0, N - 1, t);

		//3) newgroup작성
		newgroup[suffixArr[0]] = 0;
		newgroup[N] = -1;
		for (int now = 1; now < N; now++) {
			if (cmp(suffixArr[now - 1], suffixArr[now], t))
				newgroup[suffixArr[now]] = newgroup[suffixArr[now - 1]] + 1;
			else
				newgroup[suffixArr[now]] = newgroup[suffixArr[now - 1]];
		}


		//4) group 최신화
		for (int i = 0; i < N; i++)
			group[i] = newgroup[i];

		t *= 2;
		if (group[suffixArr[N - 1]] == N - 1)break;
	}
}

//4. lcp
int before[Max], plcp[Max], lcp[Max];
void getlcp() {
	//1)before
	before[suffixArr[0]] = -1; //
	for (int i = 1; i < N; i++)
		before[suffixArr[i]] = suffixArr[i - 1];

	//2)plcp
	int L = 0;
	for (int now = 0; now < N; now++) {
		if (before[now] == -1)
			plcp[now] = 0;

		while (string[now + L] == string[before[now] + L])L++;
		plcp[now] = L;

		if (L)
			L--;
	}

	//3)lcp
	for (int i = 0; i < N; i++)
		lcp[i] = plcp[suffixArr[i]];
}

int main() {
	scanf("%d %s", &N, string);

	getsuffixArr();
	getlcp();
	int max = 0;
	for (int i = 0; i < N; i++)
		max = max > lcp[i] ? max : lcp[i];
	printf("%d\n", max);
	return 0;
}