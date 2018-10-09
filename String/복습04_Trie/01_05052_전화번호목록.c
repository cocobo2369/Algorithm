#include<stdio.h>
#define MaxL 11
#define Max 10001

int T, N;

typedef struct node {
	char valid;
	int children[MaxL];
}Node;

Node trie[MaxL*Max];
int memIdx;

int conv[128];

void convert() {
	int n = 0;
	for (int i = '0'; i <= '9'; i++)
		conv[i] = n++;
}

int init() {
	trie[memIdx].valid = 0;
	for (int i = 0; i < MaxL; i++)
		trie[memIdx].children[i] = -1;
	return memIdx++;
}

void add(int now, char * string, int sIdx) {
	if (string[sIdx] == 0) {
		trie[now].valid = 1;
		return;
	}


	int c = conv[string[sIdx]];
	if (trie[now].children[c] == -1) {
		int next = init();
		trie[now].children[c] = next;
	}
	add(trie[now].children[c], string, sIdx + 1);
}

int search(int now) {

	for (int i = 0; i < MaxL; i++) {
		if (trie[now].children[i] != -1) {
			if (trie[now].valid == 1)
				return 1;
			else
				if (search(trie[now].children[i]))
					return 1;
		}
	}
	return 0;
}

int main() {
	convert();
	scanf("%d", &T);
	while (T--) {

		memIdx = 0;
		int root = init();
		scanf("%d", &N);
		while (N--) {
			char string[MaxL];
			scanf("%s", string);
			add(root, string, 0);
		}
		if (search(root))
			printf("NO\n");
		else
			printf("YES\n");

	}
	return 0;
}