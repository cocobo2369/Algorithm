#include<stdio.h>

#define Max 1000001

int back[Max];
char pattern[Max];
int N, PN;
void getback() {

	back[0] = 0;
	int matchIdx = 0;
	for (int now = 1; now < PN; now++) {
		while (matchIdx > 0 && pattern[now] != pattern[matchIdx])
			matchIdx = back[matchIdx - 1];

		back[now] = 0;
		if (pattern[now] == pattern[matchIdx]) {
			matchIdx++;
			back[now] = matchIdx;
		}
	}
}

char string[Max];
int cnt = 0;
void kmp() {
	int sIdx, pIdx = 0;
	for (sIdx = pIdx = 0; sIdx < N; sIdx++) {

		while (pIdx > 0 && string[sIdx] != pattern[pIdx])
			pIdx = back[pIdx - 1];

		if (string[sIdx] == pattern[pIdx]) {
			pIdx++;
			if (pIdx == PN) {
				cnt++;
				pIdx = back[pIdx - 1];
			}
		}
	}
}

int main() {

	scanf("%d\n%d\n%s", &PN, &N,string);
	PN = 2 * PN + 1;
	for (int i = 0; i < PN; i++)
		if (i % 2) pattern[i] = 'O';
		else pattern[i] = 'I';
	getback();
	kmp();
	printf("%d\n", cnt);
	return 0;

}