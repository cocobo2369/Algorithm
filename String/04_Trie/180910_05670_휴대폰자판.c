#include<stdio.h>

#define Len 81
#define C 26
#define Max 1000001

typedef struct node {
	char valid;
	char cnt;
	int children[C];
}Node;

Node trie[Max];
int trieIdx;

int init() {
	trie[trieIdx].valid = 0;
	trie[trieIdx].cnt = 0;
	for (int i = 0; i < C; i++)
		trie[trieIdx].children[i] = -1;

	return trieIdx++;
}

void add(int now, char * string, int sLen, int sIdx) {
	if (sLen == sIdx) {
		trie[now].valid = 1;
		return;
	}

	int c = string[sIdx] - 'a';
	if (trie[now].children[c] == -1) {
		int next = init();
		trie[now].cnt++;
		trie[now].children[c] = next;
	}
	add(trie[now].children[c], string, sLen, sIdx + 1);
}
int ans = 0;
void sum(int now, int cost) {
	if (trie[now].valid == 1) {
		ans += cost;
		//printf("%d %d\n", now, cost);
		if (trie[now].cnt == 0)
			return;
		
		else
			for (int i = 0; i < C; i++)
				if (trie[now].children[i] != -1)
					sum(trie[now].children[i], cost + 1);
	}
	else {
		for (int i = 0; i < C; i++)
			if (trie[now].children[i] != -1)
				if (trie[now].cnt > 1)
					sum(trie[now].children[i], cost + 1);
				else if (trie[now].cnt == 1)
					sum(trie[now].children[i], cost);
	}
}

int main() {
	int N;
	
	while (scanf("%d", &N) != EOF) {
		

		trieIdx = ans = 0;

		//Áß¿ä
		int root = init();

		for (int i = 0; i < N; i++) {
			char string[Len];
			scanf("%s", string);

			int len;
			for (len = 0; string[len]; len++);
			add(root, string, len, 0);
		}
		for (int i = 0; i < C; i++)
			if (trie[root].children[i] != -1)
				sum(trie[root].children[i], 1);
		printf("%.2lf\n", (double)ans / N);
	}
	return 0;
}