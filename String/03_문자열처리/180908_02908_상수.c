#include<stdio.h>

int main() {
	char num[2][4];
	scanf("%s\n%s", &num[0], &num[1]);

	for (int i = 0; i < 2; i++) {
		char temp = num[i][2];
		num[i][2] = num[i][0];
		num[i][0] = temp;
	}

	int max = 0;
	for (int i = 0; i < 3; i++) {
		if (num[0][i] < num[1][i]) {
			max = 1;
			break;
		}
		else if (num[0][i] > num[1][i])
			break;
	}
	printf("%s\n", max == 0 ? num[0] : num[1]);
	return 0;
}