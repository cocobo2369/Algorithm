#include<stdio.h>
#define Max 10
int N;
char sign[Max];
long long num[Max];
int check[Max];
long long numMax[Max],
			numMin[Max];
long long result() {
	long long res = 0;
	for (int i = 0; i < N-1; i++) {
		res += num[i];
		res *= 10;
	}
	res += num[N - 1];
	return res;
}
long long max = 0,
	min = 10000000000;
void factorial(int n, long long number) {
	
	num[n] = number;

	if (n == N-1) {
		long long res = result();
		if (max < res) {
			max = res;
			for (int i = 0; i < N; i++)
				numMax[i] = num[i];
		}
		if (min > res) {
			min = res;
			for (int i = 0; i < N; i++)
				numMin[i] = num[i];
		}
		return;
	}

	for (int i = 9; i >= 0; i--) {
		if (check[i] == 0) {
			if ((sign[n] == '<' && num[n] < i) || (sign[n] == '>' && num[n] > i)) {
				check[i] = 1;
				factorial(n + 1, i);
				check[i] = 0;
			}
		}
	}
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("\n%c", &sign[i]);
	N++;
	for (int i = 9; i >= 0; i--) {
		check[i] = 1;
		factorial(0, i);
		check[i] = 0;
	}

	for (int i = 0; i < N; i++)
		printf("%d", numMax[i]);
	printf(" ");
	for (int i = 0; i < N; i++)
		printf("%d", numMin[i]);
	printf("\n");
	return 0;
}