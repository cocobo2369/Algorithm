#include<stdio.h>

#define Max 100001
#define MaxL 21
#define MaxC 52
typedef struct node {
	char vaild;
	int children[MaxC];
}Node;

Node trie[Max];
int trieIdx;

int init() {
	trie[trieIdx].vaild = 0;

	for (int i = 0; i < MaxC; i++)
		trie[trieIdx].children[i] = -1;
	return trieIdx++;
}

int add(int now, char * string, int sIdx) {
	if (string[sIdx] == '\0') {
		trie[now].vaild = 1;
		return now;
	}

	int c;
	if ('A' <= string[sIdx] && string[sIdx] <= 'Z')
		c = string[sIdx] - 'A';
	else
		c = string[sIdx] - 'a' + MaxC / 2;

	if (trie[now].children[c] == -1) {
		int next = init();
		trie[now].children[c] = next;
	}
	return add(trie[now].children[c], string, sIdx + 1);
}

int set[Max*MaxL];
void makeSet() {
	for (int i = 0; i < Max; i++)
		set[i] = i;
}

int find(int element) {
	if (set[element] == element)
		return element;
	else
		return find(set[element]);
}
int cnt[Max*MaxL];
int cnt[Max*MaxL];
void Union(int root, int sub) {
	root = find(root);
	sub = find(sub);
	if (root > sub) {
		int temp = root;
		root = sub;
		sub = temp;
	}
	if (root != sub) {
		set[sub] = root;
		cnt[root] += cnt[sub];
		cnt[sub] = 1;
	}
}



int T, F;

int main() {

	scanf("%d", &T);
	while (T--) {
		//1. √ ±‚»≠
		trieIdx = 0;
		int root = init();
		char name[MaxL];
		for (int i = 0; i < Max*MaxL; i++)
			cnt[i] = 1;
		makeSet();
		int ans = 0;
		scanf("%d", &F);
		for (int i = 0; i < F; i++) {
			scanf("%s", name);
			int key1 = add(root, name, 0);

			scanf("%s", name);
			int key2 = add(root, name, 0);
			Union(key1, key2);


			printf("%d\n", cnt[find(key1)]);
		}
	}
	return 0;
}