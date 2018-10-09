#include<stdio.h>
#define Max 1001

char string[Max];
int N;

int suffixArr[Max],
	group[Max],
	newgroup[Max];

int cmp(int small, int big, int t) {
	if (group[small] != group[big])
		return group[small] < group[big];
	else
		return group[small + t] < group[big + t];
}

void quick(int above, int below, int t) {
	if (above >= below)
		return;

	int left = above - 1,
		right = below + 1,
		pivot = suffixArr[left + (right - left) / 2];
	while (left < right) {

		while (cmp(suffixArr[++left], pivot, t));
		while (cmp(pivot, suffixArr[--right], t));
		if (left >= right)break;
		int temp = suffixArr[left];
		suffixArr[left] = suffixArr[right];
		suffixArr[right] = temp;
	}
	quick(above, left - 1, t);
	quick(right + 1, below, t);
}

void getSuffixArr() {
	//1.초기화 , 그룹, suffixArr

	for (N = 0; string[N]; N++)
		suffixArr[N] = N,
		group[N] = string[N];
group[N] = -1;
	//2. 정렬
	int t = 1;
	while (t < N) {
		quick(0, N - 1, t);

		newgroup[suffixArr[0]] = 0;
		newgroup[N] = -1;
		for (int i = 1; i < N; i++)
			if (cmp(suffixArr[i - 1], suffixArr[i], t))
				newgroup[suffixArr[i]] = newgroup[suffixArr[i - 1]] + 1;
			else
				newgroup[suffixArr[i]] = newgroup[suffixArr[i - 1]];

		//3. 그룹최신화
		for (int i = 0; i < N; i++)
			group[i] = newgroup[i];
		t *= 2;
	}
	
}

int getLcp() {
	int total = N*(N + 1) / 2;
	for (int i = 1; i < N; i++) {

		int start1 = suffixArr[i - 1],
			start2 = suffixArr[i];
		
		int c = 0;
		for (c = 0; string[start1 + c] == string[start2 + c]; c++);
			
		total -= c;
	}
	return total;
}
int main() {
	scanf("%s", string);
	getSuffixArr();

	printf("%d\n", getLcp());



	return 0;
}