#include<stdio.h>
#define Max 52

int main() {
	char num[Max];
	scanf("%s", num + 1);

	int N = 1;
	while (num[N])
		N++;
	int mid = N / 2;

	int s = 1;
	for (int i = mid + 1; i <N; i++) {
		if (num[N - i] == num[i])continue;
		s = 0;
		if (num[N - i] < num[i])
			num[i - 1] = num[N - i + 1] = ((num[i - 1] + 1-'0')%10)+'0';

		for (int j = i; j < N; j++)
			num[j] = num[N - j]; 
		break;
	}

	if (s) {
		if ((N - 1) % 2 == 0)
			num[mid] = num[mid + 1] = ((num[mid] + 1 - '0') % 10) + '0';
		else
			num[mid] = ((num[mid] + 1 - '0') % 10) + '0';
	}
	printf("%s\n", num + 1);
	return 0;

}