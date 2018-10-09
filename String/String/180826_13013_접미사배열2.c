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
	//1. 종료조건
	if (above >= below)
		return;

	int left = above - 1,
		right = below + 1,
		pivot = suffix[left + (right - left) / 2];
	//이번 조건은 i접미사의 group 과 pivot접미사의 group의 비교다.
	while (left < right) {
		while (cmp(suffix[++left], pivot, t));
		while (cmp(pivot, suffix[--right], t));

		//반드시 필요한 부분
		if (left >= right)
			break;
		//그리고 정렬의 대상은 suffix다.
		//suffix는 순서대로 i접미사를 정렬한 배열이니까
		int temp = suffix[left];
		suffix[left] = suffix[right];
		suffix[right] = temp;
	}
	quick(above, left - 1, t);
	quick(right + 1, below, t);
}

void getSuffixArray() {

	//1. string 길이 및 suffix 초기화
	for (N = 0; string[N]; N++)
		suffix[N] = N;

	//2. group 초기화
	for (int i = 0; i < N; i++)
		group[i] = string[i];
	group[N] = -1;//주의!

	//3. 비교
	int t = 1;
	while (t < N) {
		// 1) group - 기준한 정렬
		quick(0, N - 1, t);

		// 2) group - 최신화
		newGroup[suffix[0]] = 0; // 첫기준은 무조건 0
		newGroup[N] = -1; // N은 범위 제한용 
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