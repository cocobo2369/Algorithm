#include<stdio.h>

char string[101];
char check[26];
char ans[101];
int main() {

	char cambridge[] = "CAMBRIDGE";
	for (int i = 0; cambridge[i]; i++)
		check[cambridge[i] - 'A'] = 1;

	scanf("%s", string);
	int cnt = 0;
	for (int i = 0; string[i];i++) {
		
		if (check[string[i] - 'A'])continue;
		else
			ans[cnt++] = string[i];
	}
	printf("%s\n", ans);
	return 0;
}