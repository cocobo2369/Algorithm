#include<stdio.h>

#define Max 100001

char string[Max];

int N;
int suffix[Max],
	group[Max],
	newGroup[Max];

int cmp(int small, int big, int t) {
	if (group[small] != group[big])
		return group[small] < group[big];
	else
		return group[small + t] < group[big + t];
}

void quick(int above, int below, int t) {
	//1. ��������
	if (above >= below)
		return;

	int left = above - 1,
		right = below + 1,
		pivot = suffix[left + (right - left) / 2];
	//�̹� ������ i���̻��� group �� pivot���̻��� group�� �񱳴�.
	while (left < right) {
		while (cmp(suffix[++left], pivot, t));
		while (cmp(pivot, suffix[--right], t));

		//�ݵ�� �ʿ��� �κ�
		if (left >= right)
			break;
		//�׸��� ������ ����� suffix��.
		//suffix�� ������� i���̻縦 ������ �迭�̴ϱ�
		int temp = suffix[left];
		suffix[left] = suffix[right];
		suffix[right] = temp;
	}
	quick(above, left - 1, t);
	quick(right + 1, below, t);
}

void getSuffixArray() {

	//1. string ���� �� suffix �ʱ�ȭ
	for (N = 0; string[N]; N++)
		suffix[N] = N;

	//2. group �ʱ�ȭ
	for (int i = 0; i < N; i++)
		group[i] = string[i];
	group[N] = -1;//����!

	//3. ��
	int t = 1;
	while (t < N) {
		// 1) group - ������ ����
		quick(0, N - 1, t);

		// 2) group - �ֽ�ȭ
		newGroup[suffix[0]] = 0; // ù������ ������ 0
		newGroup[N] = -1; // N�� ���� ���ѿ� 
		for (int i = 1; i < N; i++) {
			if (cmp(suffix[i - 1], suffix[i], t))
				newGroup[suffix[i]] = newGroup[suffix[i - 1]] + 1;
			else
				newGroup[suffix[i]] = newGroup[suffix[i - 1]];
		}
		for (int i = 0; i < N; i++)
			group[i] = newGroup[i];

		t *= 2;
	}
	
}

int main() {
	scanf("%s", string);
	getSuffixArray();
	for (int i = 0; i < N; i++)
		printf("%d\n", suffix[i]);
	return 0;
}