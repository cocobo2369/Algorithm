#include<stdio.h>

int main() {
	char name[101];
	scanf("%s", name);
	for (int i = 0; name[i]; i++)
		if ('A' <= name[i] && name[i] <= 'Z')
			printf("%c", name[i]);
	printf("\n");
	return 0;
}