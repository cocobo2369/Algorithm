//멤버 마이어스 알고리즘 O(NlongN*longN)
//radix sort로 O(NlogN)이 가능하지만 외우기 너무 어려움
//다소 헷깔릴 수 있는 부분이 있다.
//바로 suffixArr[i], group[i], string[i] 들
/*
group[i] 에서 i = string의 i접미사
suffixArr[i] 에서 i = i번째
즉 suffixArr[i]=k 는 i번째 순서가 string의 k접미사 라는 말이다.
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
	
	//1. 순서 초기화
	for (N = 0; string[N]; N++)
		suffixArr[N] = N;

	//2. 그룹 초기화 - 문자의 ascii값
	//3. N범위를 초과하지 않게 하도록 위한 group[N]=-1
	for (int i = 0; i < N; i++)
		group[i] = string[i]-'a';
	group[N] = -1;

	//4. t의 범위가 글자를 넘지 않도록
	//같아도 안되는 것이 string의 i번째에서 +t 하면 무조건 초과된다.
	while (t < N) {

		quick(0, N - 1, t);
		
		//suffixArr[0] = 가장 빠른 string의 접미사
		//이 string의 접미사의 group이 가장 빠른 0 을 지님
		newGroup[suffixArr[0]] = 0;
		newGroup[N] = -1;

		//5. suffixArr가 t단계일 때로 정렬되어있는데
		// t단계일 때 동일한 group이지만 2t단계일 때는 순서가 구분될 수 있으므로 세분히 group화하는 것
		for (int i = 1; i < N; i++) {
			if (cmp(suffixArr[i - 1], suffixArr[i], t))
				newGroup[suffixArr[i]] = newGroup[suffixArr[i - 1]] + 1;
			else
				newGroup[suffixArr[i]] = newGroup[suffixArr[i - 1]];
		}

		for (int i = 0; i < N; i++)
			group[i] = newGroup[i];

		//6. 단계 높여줌
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