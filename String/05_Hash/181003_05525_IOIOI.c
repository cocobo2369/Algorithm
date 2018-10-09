#include<stdio.h>
#define Max 1000001
#define mod 1000000007
char string[Max];
char pattern[Max];
int N,S;

int main() {
	scanf("%d %d %s", &N, &S, string);
	N = 2 * N + 1;
	long long key, temp, power=1;
	int cnt;
	key = temp = cnt = 0;
	for (int i = 0; i < N; i++) {
		key <<= 1;
		key %= mod;
		if (i % 2 == 0) {
			key += 'I';
			pattern[i] = 'I';
		}
		else {
			key += 'O';
			pattern[i] = 'O';
		}

		temp <<= 1;
		temp %= mod;
		temp += string[i];
		power = (power * 2) % mod;
	}
	power /= 2;

	for (int i = 1; i < S-N; i++) {
		temp -= (string[i - 1] * power);
		temp <<= 1;
		temp %= mod;
		temp += string[i + N - 1];
		if (key == temp) cnt++;
	}

	printf("%d\n", cnt);
	
	return 0;
}