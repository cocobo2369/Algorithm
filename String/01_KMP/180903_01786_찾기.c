#include<stdio.h>

#define Max 1000001

char string[Max], pattern[Max];

int back[Max];
int N, PN;

void getBack() {

	back[0] = 0;

	int matchIdx = 0;
	//newstart 작성

	for (int i = 1; i < PN; i++) {
		matchIdx = back[i - 1];
		while (matchIdx > 0 && pattern[i] != pattern[matchIdx])
			matchIdx = back[matchIdx - 1];

		if (pattern[i] == pattern[matchIdx])
			back[i] = matchIdx + 1;
		else back[i] = 0;
	}
}
int cnt, found[Max];
void kmp() {
	int sIdx, pIdx = 0;
	for (sIdx = pIdx = 0; sIdx < N; sIdx++) {

		//string과 pattern이 다르면
		//pattern의 처음위주로 다시 돌아간다.
		//while이 반복될수록 앞으로 간다.
		while (pIdx > 0 && string[sIdx] != pattern[pIdx])
			pIdx = back[pIdx - 1];


		// string과 pattern이 같으면
		if (string[sIdx] == pattern[pIdx])
			//case는 2가지
			// pattern을 완성했거나
			if (pIdx == PN - 1) {
				found[cnt++] = sIdx + 1 - (PN - 1);
				pIdx = back[pIdx];
			}
		// 완성하지 않았거나
			else
				pIdx++;
	}
}

int myscanf(char *string) {
	int i = 0;
	char idx;
	do {
		int t = scanf("%c", &idx);
		if (t == EOF || idx == '\n') break;
		string[i++] = idx;
	} while (1);
	return i;
}

int main() {
	N = myscanf(string);
	PN = myscanf(pattern);

	getBack();
	kmp();
	printf("%d\n", cnt);
	for (int i = 0; i < cnt; i++)
		printf("%d\n", found[i]);
	return 0;
}