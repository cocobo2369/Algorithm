#include<stdio.h>
#define Max 1000001

char string[Max];

int back[Max];
int N;
void getback() {
	int matchIdx = 0;
	back[0] = 0;

	for (N = 1; string[N]; N++) {

		while (matchIdx > 0 && string[N] != string[matchIdx])
			matchIdx = back[matchIdx - 1];

		back[N] = 0;
		if (string[N] == string[matchIdx]) {
			matchIdx++;
			back[N] = matchIdx;
		}

	}
}

int main() {

	while (1) {
		scanf("%s", &string);
		if (string[0] == '.' && string[1] == 0)break;
		getback();
		

		int ans = N / (N - back[N - 1]);
		if (N % ans != 0)
			printf("1\n");
		else
			printf("%d\n", ans);

	}
	return 0;
}
