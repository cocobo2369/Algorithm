#include<stdio.h>
#define Max 1000001
char string[Max];
int alphabet[30];
int main() {
	scanf("%s", string);

	for (int i = 0; string[i]; i++) {
		if ('a' <= string[i] && string[i] <= 'z')
			alphabet[string[i] - 'a']++;
		else
			alphabet[string[i] - 'A']++;
	}

	int max = 0, same = 0;
	for (int i = 1; i <='Z'-'A'; i++) {
		if (alphabet[max] < alphabet[i]) {
			max = i;
			same = 0;
		}
		else if (alphabet[max] == alphabet[i])
			same = 1;
	}

	if (same == 1)
		printf("?\n");
	else
		printf("%c\n", max + 'A');
	return 0;

}