#include<stdio.h>

#define Max 101
char check[26];
char string[Max];
int N;
int main() {
	scanf("%d", &N);
	int cnt = 0;
	while (N--) {
		scanf("%s", string);
		int t = 0;
		for (int i = 0; i < 26; i++)
			check[i] = 0;
		for (int i = 0; string[i]; i++) {
			char c = string[i];
			if (check[c-'a'] == 0) {
				check[c-'a'] = 1;
				for (int j = i + 1; string[j];i++) {
					i = j-1;
					if (string[j] == c)j++;
					else 
						break;
				}
			}
			else {
				t = 1;
				break;
			}
		}
		if (t == 0) {
			cnt++;
		}
	}
	printf("%d\n", cnt);
	return 0;
}