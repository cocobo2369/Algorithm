#include<stdio.h>
#define Len 11
#define Max 10001 * Len

typedef struct node {
	int valid;
	int children[Len];
}Node;

Node trie[Max];
int trieIdx;

int init() {
	trie[trieIdx].valid = 0;
	
	for (int i = 0; i < Len; i++)
		trie[trieIdx].children[i] = -1; //0 도 idx로 의미가 있기에 '0'
	return trieIdx++;
}

void add(int now, char * string, int sLen, int sIdx) {
	if (sLen == sIdx) {
		trie[now].valid = 1;
		return;
	}

	int c = string[sIdx] - '0';
	if (trie[now].children[c] == -1) {
		int next = init();
		trie[now].children[c] = next;
	}
	add(trie[now].children[c], string, sLen, sIdx + 1);
}

int search(int now) {

	for (int i = 0; i < 10; i++) {
		if (trie[now].children[i] != -1) {
			if (trie[now].valid == 1)
				return 0;
			else
				if (search(trie[now].children[i]) == 0)
					return 0;
		}
	}
	return 1;
}

int T;
int main() {
	scanf("%d", &T);
	while (T--) {
		int N;
		scanf("%d", &N);

		trieIdx = 0;
		int root = init();
		for (int i = 0; i < N; i++) {
			char string[11];
			scanf("%s", string);
			int len = 0;
			for (len = 0; string[len]; len++);
			add(root, string, len, 0);
		}
		printf("%s\n", search(root) == 0 ? "NO" : "YES");

	}
	return 0;
}