#include<stdio.h>
#define Max 10001
#define MaxL 501
#define C 26

int N, M;
int conv[128];
void convert() {
	int num = 0;
	for (int i = 'a'; i <= 'z'; i++)
		conv[i] = num++;

}

typedef struct node {
	char valid;
	int children[C];
}Node;

Node trie[Max*MaxL];
int memIdx;

int init() {
	trie[memIdx].valid = 0;
	for (int i = 0; i < C; i++)
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

int search(int now, char * string, int sIdx) {

	if (string[sIdx] == 0) //
		return 1;

	int c = conv[string[sIdx]];
	if (trie[now].children[c] != -1)
		return search(trie[now].children[c], string, sIdx + 1);
	else
		return 0;
}

int main() {
	convert();
	int root = init();
	scanf("%d %d", &N, &M);
	char string[MaxL];
	while (N--) {
		scanf("%s", string);
		add(root, string, 0);
	}
	int ans = 0;
	while (M--) {
		scanf("%s", string);
		ans += search(root, string, 0);
	}
	printf("%d\n", ans);
	return 0;
}