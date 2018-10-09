//KMP_01786_ã�� ������
#include<stdio.h>

#define Max 1000001

char string[Max], pattern[Max];
int N, PN;


//�����Լ�
int back[Max];

void getback() {

	int matchIdx = 0;

	back[0] = 0;
	for (int now = 1; pattern[now]; now++) {

		//�ٸ���
		while (matchIdx > 0 && pattern[now] != pattern[matchIdx])
			matchIdx = back[matchIdx - 1];

		//������
		back[now] = 0; //����������
		if (pattern[now] == pattern[matchIdx]) {
			matchIdx++;
			back[now] = matchIdx;
		}
	}
}


int cnt, found[Max];
//kmp
void kmp() {

	int matchIdx = 0;
	for (int now = 0; string[now]; now++) {

		//�ٸ���
		while (matchIdx > 0 && string[now] != pattern[matchIdx])
			matchIdx = back[matchIdx - 1];

		//������
		if (string[now] == pattern[matchIdx]) {
			matchIdx++;

			if (matchIdx == PN) {

				found[cnt++] = now + 1 - (PN - 1);//pattern�� ã���� �� ó��
				matchIdx = back[matchIdx - 1];
			}
		}
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

	getback();
	kmp();
	printf("%d\n", cnt);
	for (int i = 0; i < cnt; i++)
		printf("%d\n", found[i]);
	return 0;
}