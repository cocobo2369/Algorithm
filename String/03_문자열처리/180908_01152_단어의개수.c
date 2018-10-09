#include<stdio.h>
#define Max 1000000
char c;
int main() {
	int cnt = 0;
	char bef = ' ';
	while (scanf("%c", &c)) {
		if (bef != ' ' && (c == ' ' || c == '\n'))cnt++;
		if (c == '\n')break;
		bef = c;
	}
	printf("%d\n", cnt);
	return 0;
}