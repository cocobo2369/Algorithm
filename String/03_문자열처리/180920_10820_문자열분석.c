#include<stdio.h>

#define Max 101

int main() {
	char string[Max];

	while(scanf("%[^\n]", string) != EOF){
		getchar();
		int big = 0, small = 0, space = 0, num = 0;
		for (int i = 0; string[i] != 0; i++) {
			if ('A' <= string[i] && string[i] <= 'Z')
				big++;
			else if ('a' <= string[i] && string[i] <= 'z')
				small++;
			else if (string[i] == ' ')
				space++;
			else
				num++;
		}
		printf("%d %d %d %d\n", small,big, num, space);
	}
	return 0;
}