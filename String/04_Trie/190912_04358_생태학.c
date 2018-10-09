#include<stdio.h>
#define Len 31
#define MaxC 95
#define Max 10001
typedef struct node {
	int valid;
	int children[MaxC];
}Node;

Node trie[Max*Len];
int trieIdx;

int wordIdx;
int dic[Max*Len];
char word[Max*Len][31];
int init() {
	trie[trieIdx].valid = 0;
	for (int i = 0; i < MaxC; i++)
		trie[trieIdx].children[i] = -1;
	return trieIdx++;
}

void add(int now, char * string, int sIdx) {
	if (string[sIdx] == 0) {
		trie[now].valid = 1;
		
		if(dic[now] == 0)
			for (int i = 0; string[i]; i++)
				word[now][i] = string[i];
		dic[now]++;
		return;
	}

	int c = string[sIdx] - ' ';
	if (trie[now].children[c] == -1) {
		int next = init();
		trie[now].children[c] = next;
	}
	add(trie[now].children[c], string, sIdx + 1);
}

void find(int now) {
	if (trie[now].valid == 1) {
		printf("%s %.4lf\n", word[now],(double)dic[now]/wordIdx*100);
		
		for (int i = 0; i < MaxC; i++)
			if (trie[now].children[i] != -1)
				find(trie[now].children[i]);

		return;
	}

	for (int i = 0; i < MaxC; i++)
		if (trie[now].children[i] != -1)
			find(trie[now].children[i]);

}

int main() {
	int root = init();
	char string[Len];
	while (scanf(" %[^\n]", string) != EOF) {
		wordIdx++;
		add(root, string, 0);
	}
	find(root);
	return 0;
}