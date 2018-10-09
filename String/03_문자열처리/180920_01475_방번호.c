#include<stdio.h>
#define Max 1000001
int N;
int check[10];

int main() {
	scanf("%d", &N);

	if (N == 0)
		printf("1\n");
	else {
		for (int i = 0; N; i++) {
			int num = N % 10;
			N /= 10;
			check[num]++;
		}
		if ((check[6] + check[9]) % 2 == 0)
			check[6] = check[9] = (check[6] + check[9]) / 2;
		else
			check[6] = check[9] = (check[6] + check[9]) / 2 + 1;


		int cnt = 0;
		for (int i = 0; i < 10; i++) {
			if (check[i] != 0)
				cnt = cnt > check[i] ? cnt : check[i];
		}

		printf("%d\n", cnt);
	}
	return 0;
}