#include<stdio.h>

#define Max 200001
int N;
int string[Max*2], pattern[Max];

int back[Max];
void getback() {

	int matchIdx = 0;
	back[0] = 0;
	for (int now = 1; now < N; now++) {

		while (matchIdx > 0 && pattern[now] != pattern[matchIdx])
			matchIdx = back[matchIdx - 1];

		back[now] = 0;
		if (pattern[now] == pattern[matchIdx]) {
			matchIdx++;
			back[now] = matchIdx;
		}
	}
}

void kmp() {

	int matchIdx = 0;

	for (int now = 0; now < N*2; now++) {

		while (matchIdx > 0 && string[now] != pattern[matchIdx])
			matchIdx = back[matchIdx - 1];

		if (string[now] == pattern[matchIdx]) {
			matchIdx++;
			if (matchIdx == N) {
				printf("possible\n");
				return;
			}
		}
	}
	printf("impossible\n");
	return;
}



void quick(int above, int below, int * arr) {

	if (above >= below) return;

	int left = above - 1,
		right = below + 1,
		pivot = arr[left + (right - left) / 2];

	while (left < right) {

		while (arr[++left] < pivot);
		while (pivot < arr[--right]);

		if (left >= right)break;

		int temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
	}
	quick(above, left - 1, arr);
	quick(right + 1, below, arr);

}


int main() {
	scanf("%d", &N);
	string[N] = pattern[N] = 360000;
	for (int i = 0; i < N; i++)
		scanf("%d", &string[i]);
	quick(0, N - 1, string);
	int stringmax = 360000 - (string[N-1] - string[0]);

	for (int i = 0; i < N; i++)
		scanf("%d", &pattern[i]);
	quick(0, N - 1, pattern);
	int patternmax = 360000 - (pattern[N - 1] - pattern[0]);

	for (int i = 1; i <= N; i++) {
		string[i - 1] = string[i] - string[i - 1];
		pattern[i - 1] = pattern[i] - pattern[i - 1];
	}
	string[N-1] = stringmax;
	pattern[N-1] = patternmax;
	for (int i = 0; i < N; i++)
		string[N + i] = string[i];
	getback();
	kmp();

	return 0;
}