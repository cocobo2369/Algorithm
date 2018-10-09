#include<stdio.h>

#define Max 1000001 // �����ϸ� 1000000 --> ���� ���� for���ƴ϶�� ��

char pattern[Max];
int back[Max], N;

void getback() {

	back[0] = 0;
	int matchIdx = 0;
	for (int i = 1; i < N; i++) {
		while (matchIdx > 0 && pattern[i] != pattern[matchIdx])
			matchIdx = back[matchIdx - 1];

		//�׽�Ʈ ���̽� ���� �� ���� �ʱ�ȭ�������� ���⼭ �س���
		back[i] = 0;
		if (pattern[i] == pattern[matchIdx]) {
			matchIdx++;
			back[i] = matchIdx;
		}
	}
}

int main() {
	int t = 0;
	while (++t) {
		scanf("%d", &N);
		if (N == 0)break;
		scanf("%s", pattern);

		getback();
		printf("Test case #%d\n", t);
		for (int i = 1; i < N; i++) {
			int len = i + 1;
			if (back[i]==0 || len % (len - back[i]))continue;
			printf("%d %d\n", len, len / (len - back[i]));
		}
		printf("\n");
	}
	return 0;
}