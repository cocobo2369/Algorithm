#include<stdio.h>
#define Max 1000001

char string[Max];
int N;

int back[Max];
void getback() {
	back[0] = 0;

	int matchIdx = 0;
	for (int i = 1; i < N; i++) {
		back[i] = 0;

		while (matchIdx > 0 && string[i] != string[matchIdx])
			matchIdx = back[matchIdx - 1];

		if (string[i] == string[matchIdx]) {
			matchIdx++;
			back[i] = matchIdx;
		}
	}
}

int main() {
	scanf("%d %s", &N, string);
	getback();
	printf("%d\n", N - back[N - 1]);

	return 0;
}