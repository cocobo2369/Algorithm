//��� ���̾ �˰��� O(NlongN*longN)
//radix sort�� O(NlogN)�� ���������� �ܿ�� �ʹ� �����
//�ټ� ��� �� �ִ� �κ��� �ִ�.
//�ٷ� suffixArr[i], group[i], string[i] ��
/*
group[i] ���� i = string�� i���̻�
suffixArr[i] ���� i = i��°
�� suffixArr[i]=k �� i��° ������ string�� k���̻� ��� ���̴�.
*/

#include<stdio.h>
#define Max 1001
char string[Max];
int suffixArr[Max], N,
	group[Max],
	newGroup[Max];
int cmp(int small, int big, int t) {
	if (group[small] != group[big])
		return group[small] < group[big];
	else
		return group[small + t] < group[big + t];
}
void quick(int above, int below, int t) {
	if (above >= below)
		return;

	int left = above-1,
		right = below+1;
	int pivot = suffixArr[above + (below - above) / 2];

	while (left < right) {
		while (cmp(suffixArr[++left], pivot, t));
		while (cmp(pivot, suffixArr[--right], t));

		if (left >= right)
			break;
		int temp = suffixArr[left];
		suffixArr[left] = suffixArr[right];
		suffixArr[right] = temp;
	}
	quick(above, left - 1, t);
	quick(right + 1, below, t);
	
}
void getSuffixArr() {
	int t = 1;
	
	//1. ���� �ʱ�ȭ
	for (N = 0; string[N]; N++)
		suffixArr[N] = N;

	//2. �׷� �ʱ�ȭ - ������ ascii��
	//3. N������ �ʰ����� �ʰ� �ϵ��� ���� group[N]=-1
	for (int i = 0; i < N; i++)
		group[i] = string[i]-'a';
	group[N] = -1;

	//4. t�� ������ ���ڸ� ���� �ʵ���
	//���Ƶ� �ȵǴ� ���� string�� i��°���� +t �ϸ� ������ �ʰ��ȴ�.
	while (t < N) {

		quick(0, N - 1, t);
		
		//suffixArr[0] = ���� ���� string�� ���̻�
		//�� string�� ���̻��� group�� ���� ���� 0 �� ����
		newGroup[suffixArr[0]] = 0;
		newGroup[N] = -1;

		//5. suffixArr�� t�ܰ��� ���� ���ĵǾ��ִµ�
		// t�ܰ��� �� ������ group������ 2t�ܰ��� ���� ������ ���е� �� �����Ƿ� ������ groupȭ�ϴ� ��
		for (int i = 1; i < N; i++) {
			if (cmp(suffixArr[i - 1], suffixArr[i], t))
				newGroup[suffixArr[i]] = newGroup[suffixArr[i - 1]] + 1;
			else
				newGroup[suffixArr[i]] = newGroup[suffixArr[i - 1]];
		}

		for (int i = 0; i < N; i++)
			group[i] = newGroup[i];

		//6. �ܰ� ������
		t *= 2;
	}
}

int main() {
	scanf("%s", string);

	getSuffixArr();

	for (int i = 0 ;i < N; i++)
		printf("%s\n", &string[suffixArr[i]]);
	return 0;
}