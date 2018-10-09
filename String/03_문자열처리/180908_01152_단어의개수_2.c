#include<stdio.h>
#define Max 1000001
char string[Max];
int main() {
	int cnt = 0;
	string[0] = ' ';
	scanf("%[^\n]s", &string[1]);
	for(int i = 1;1;i++){
		if (string[i-1] != ' ' && (string[i] == ' ' || string[i] == 0))
			cnt++;
		if (string[i] == 0)break;
	}
	printf("%d\n", cnt);
	return 0;
}