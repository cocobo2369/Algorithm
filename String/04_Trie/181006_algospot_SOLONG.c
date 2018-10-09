#include<stdio.h>
#define Max 10001
#define L 12
int C, N, M;

char dic[Max][L];
int dicCnt[Max];

typedef struct node {
	char valid;
	int freq;
	int child[27];
}Node;

Node trie[Max*L];
int trieIdx;

int init() {
	trie[trieIdx].valid = 0;
	trie[trieIdx].freq = -1;
	for (int i = 0; i < 27; i++)
		trie[trieIdx].child[i] = -1;
	return trieIdx++;
}

int conv[128];
void convert() {
	int num = 0;
	for (int i = 'A'; i <= 'Z'; i++)
		conv[i] = num++;
}

int cmp(char * ahead, char * behind) {
	for (int i = 0; ahead[i] || behind[i]; i++)
		if (ahead[i] != behind[i])
			return ahead[i] - behind[i];
	return 0;
}


void add(int now, char * string, int sIdx,int freq) {

	if (string[sIdx] == 0) {
		trie[now].valid = 1;
		return;
	}
	int c = conv[string[sIdx]];

	if (trie[now].child[c] == -1) {
		int next = init();
		trie[now].child[c] = next;
	}

	int nn = trie[now].child[c];
	if (trie[nn].freq != -1) {
		int f = trie[nn].freq;
		if (dicCnt[f] < dicCnt[freq])
			trie[nn].freq = freq;
		else if (dicCnt[f] == dicCnt[freq]) {
			if (cmp(dic[f], dic[freq]) > 0)
				trie[nn].freq = freq;
		}
	}
	else
		trie[nn].freq = freq;


	add(trie[now].child[c], string, sIdx + 1,freq);


}
/*
void tree(int now) {
	printf("%d %s %d\n", now, dic[trie[now].freq], dicCnt[trie[now].freq]);

	for (int i = 0; i < 27; i++)
		if (trie[now].child[i] != -1)
			tree(trie[now].child[i]);

}
*/

int find(int now,char * string, int cnt) {
	if (string[cnt] != 0 && cmp(string, dic[trie[now].freq]) == 0) //자동완성으로 리턴
		return cnt+1;
	if (string[cnt] == 0) //수동완성으로 리턴
		return cnt;
	
	int c = conv[string[cnt]];
	if (trie[now].child[c] == -1)
		return find(0, string, cnt + 1);
	else
		return find(trie[now].child[c], string, cnt + 1);
}


int main() {
	convert();
	scanf("%d", &C);
	while (C--) {
		//초기화
		int res = 0;
		trieIdx = 0;
		int root = init();
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++) {
			scanf(" %s %d", dic[i], &dicCnt[i]);
			add(root, dic[i], 0, i);
		}

		//tree(root);

		char string[L];
		for (int i = 0; i < M; i++) {
			scanf("%s", string);
			res += find(root, string, 0);
			//printf("==%d\n", find(root, string, 0));
		}
		printf("%d\n", res+M-1);
	}
	return 0;
}