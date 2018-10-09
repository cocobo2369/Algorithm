#include<stdio.h>
#define Max 1000001

char string[Max];
int back[Max];
long long memo[Max];
int N;
void getback() {

	int sum = 0;
	back[0] = 0;

	int matchIdx = 0;
	for (int i = 1; i < N; i++) {
		while (matchIdx > 0 && string[i] != string[matchIdx])
			matchIdx = back[matchIdx - 1];

		back[i] = 0;
		if (string[i] == string[matchIdx])
		{
			matchIdx++;
			back[i] = matchIdx;
		}
	}

	return; 
}

long long result(int i) {
	if (memo[i] != -1) return memo[i];
	int L = i + 1;
	if (back[i] == 0)return memo[i] = 0;
	if (back[i - (L - back[i])] == 0)
		return  memo[i] = (long long)back[i];
	else 
		return memo[i] = result(i - (L - back[i]));
}


int main() {
	scanf("%d %s", &N, &string);

	getback();

	long long sum = 0;

	for (int i = 0; i < N; i++) {
		memo[i] = -1;
		result(i);
		if(memo[i])
			sum += (i+1-memo[i]);

	}
	printf("%lld\n", sum);
	return 0;
}