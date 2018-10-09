#include<stdio.h>
#define MaxP 50001

int order[123],
pattern[MaxP],
string[500001],sstring[500001];

int N, A, PN, SN;

int back[MaxP];
void getback() {

	int matchIdx = 0;

	back[0] = 0;
	for (int now = 1; now < PN; now++) {

		while (matchIdx > 0 && pattern[now] != pattern[matchIdx])
			matchIdx = back[matchIdx - 1];

		back[now] = 0;
		if (pattern[now] == pattern[matchIdx]) {
			matchIdx++;
			back[now] = matchIdx;
		}
	}
}

int kmp() {
	int cnt = 0;
	int matchIdx = 0;

	for (int now = 0; now < SN; now++) {

		while (matchIdx > 0 && sstring[now] != pattern[matchIdx])
			matchIdx = back[matchIdx - 1];

		if (sstring[now] == pattern[matchIdx]) {
			matchIdx++;
			if (matchIdx == PN) {
				cnt++;
				matchIdx = back[matchIdx - 1];
			}
		}
	}
	return cnt;
}


int shift[63], cnt;
int main() {
	scanf("%d", &N);

	while (N--) {

		//√ ±‚»≠
		cnt = 0;
		for (int i = 0; i < 123; i++)
			order[i] = 0;
		//

		char s[500001];
		scanf("%s", s);
		for (A = 0; s[A]; A++)
			order[s[A] - '0'] = A;

		scanf("%s", s);
		for (PN = 0; s[PN]; PN++)
			pattern[PN] = order[s[PN] - '0'];

		getback();
		
		scanf("%s", s);
		for (SN = 0; s[SN]; SN++)
			string[SN] = order[s[SN] - '0'];

		for (int i = 0; i <A; i++) {
			for (int j = 0; j < SN; j++)
				sstring[j] = (string[j] + A - i) % A;
			
			int res = kmp();
			if (res == 1)
				shift[cnt++] = i;
		}

		if (cnt == 0)
			printf("no solution\n");
		else if (cnt == 1)
			printf("unique: %d\n", shift[0]);
		else {
			printf("ambiguous:");

			for (int i = 0; i < cnt; i++)
				printf(" %d", shift[i]);
			printf("\n");
		}

	}
	return 0;
}