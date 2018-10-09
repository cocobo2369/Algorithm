#include<stdio.h>
#define Max 1001
#define L 21
#define C 65 
typedef struct node {
	int valid; // 단어완성
	int children[C]; //대소문자,숫자,점
	int erase;
}Node;

Node trie[Max * 2 * L];
int memIdx;

int conv[128];
int init() {
	trie[memIdx].valid = 0;
	for (int i = 0; i < C; i++)
		trie[memIdx].children[i] = -1;
	return memIdx++;
}

void add(int now, char * string, int sLen, int sIdx, int erase) {
	trie[now].erase = erase;
	if (sIdx == sLen) {
		trie[now].valid = 1;
		return;
	}

	int c = conv[string[sIdx]];

	if (trie[now].children[c] == -1) {
		int next = init();
		trie[now].children[c] = next;
	}
	add(trie[now].children[c], string, sLen, sIdx + 1, erase);
}

int search(int now) {
	//종료
	if (trie[now].valid == 1) {
		if (trie[now].erase == 1) {
			return 0;
		}
		else
			return 1;
	}
	int num = 0;
	for (int i = 0; i < C; i++) {
		if (trie[now].children[i] != -1) {
			if (trie[now].erase == 1)
				num += search(trie[now].children[i]);
			else
				num = search(trie[now].children[i]);
		}
	}

	return num;
}

void convert() {
	int num = 0;
	for (int i = '0'; i <= '9'; i++)
		conv[i] = num++;
	for (int i = 'A'; i <= 'Z'; i++)
		conv[i] = num++;
	for (int i = 'a'; i <= 'z'; i++)
		conv[i] = num++;
	conv['.'] = num++;
	conv['\0'] = num++;
}

int T, N;

int main() {
	convert();
	scanf("%d", &T);
	while (T--) {

		memIdx = 0;
		int root = init();

		for (int i = 0; i < 2; i++) {
			scanf("%d", &N);
			for (int n = 0; n < N; n++) {
				char string[L];
				int l;
				scanf("%s", string);
				for (l = 0; string[l]; l++);
				add(root, string, l + 1, 0, i);
			}
		}
		printf("%d\n", search(root));
	}
	return 0;
}