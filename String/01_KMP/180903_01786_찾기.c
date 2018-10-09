#include<stdio.h>

#define Max 1000001

char string[Max], pattern[Max];

int back[Max];
int N, PN;

void getBack() {

	back[0] = 0;

	int matchIdx = 0;
	//newstart �ۼ�

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

		//string�� pattern�� �ٸ���
		//pattern�� ó�����ַ� �ٽ� ���ư���.
		//while�� �ݺ��ɼ��� ������ ����.
		while (pIdx > 0 && string[sIdx] != pattern[pIdx])
			pIdx = back[pIdx - 1];


		// string�� pattern�� ������
		if (string[sIdx] == pattern[pIdx])
			//case�� 2����
			// pattern�� �ϼ��߰ų�
			if (pIdx == PN - 1) {
				found[cnt++] = sIdx + 1 - (PN - 1);
				pIdx = back[pIdx];
			}
		// �ϼ����� �ʾҰų�
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