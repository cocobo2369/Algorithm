#include<stdio.h>
#define Max 400002
int N, midN;

int group[Max];
int cmp(int small, int big, int t) {
	if (group[small] != group[big])
		return group[small] < group[big];
	else
		return group[small + t] < group[big + t];
}

char suffixArr[Max];
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

char string[Max],string2[Max];
int newgroup[Max];
void getsuffixArr() {

	//초기화
	for (int i = 0; i < N; i++) {
		group[i] = string[i];
		suffixArr[i] = i;
	}
	group[N] = -1;

	//정렬
	int t = 1;
	while (t < N) {

		quick(0, N - 1,t);

		//newgroup
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

int max = 0, start=0;
int before[Max], plcp[Max], lcp[Max];
void getlcp() {

	before[suffixArr[0]] = -1;//
	for (int now = 1; now < N; now++)
			before[suffixArr[now]] = suffixArr[now - 1];
	
	int L = 0;
	for (int now = 0; now < N; now++) {
		if (before[now] == -1)
			plcp[now] = 0;
		while (string[now + L] == string[before[now] + L])L++;
		plcp[now] = L;
		
		//항상말했잖니 여기조심하라고 곱하면 넘친다고
		if ((long long)(midN - now) *(long long)(midN - before[now]) < 0) {
			if (max < L) {
				max = L;
				start = now < before[now] ? now : before[now];
			}
		}
		if (L)
			L--;
	}

	for (int i = 0; i < N; i++)
		lcp[i] = plcp[suffixArr[i]];
}

int main() {

	scanf("%s\n%s", string,string2);
	for (midN = 0; string[midN]; midN++);
	string[midN] = 1;
	for (N = 0; string2[N]; N++) {
		string[N+midN+1] = string2[N];
	}
	N += (midN + 1);
	getsuffixArr();
	getlcp();
	printf("%d\n",max);
	for (int i = 0; i < max; i++)
		printf("%c", string[start+i]);
	printf("\n");
	return 0;

}