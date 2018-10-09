#include<stdio.h>

#define Max 300001
#define MaxC 26
#define MaxL 9
int W, BB;
char board[4][4], string[MaxL];

typedef struct node {
	char valid;
	int children[MaxC];
}Node;

Node trie[Max*MaxL];
int trieIdx;
int init() {
	trie[trieIdx].valid = 0;
	for (int i = 0; i < MaxC; i++)
		trie[trieIdx].children[i] = -1;

	return trieIdx++;
}

void add(int now, char * string, int sIdx) {
	if (string[sIdx] == 0) {
		trie[now].valid = 1;
		return;
	}

	int c = string[sIdx] - 'A';
	if (trie[now].children[c] == -1) {
		int next = init();
		trie[now].children[c] = next;
	}
	add(trie[now].children[c], string, sIdx + 1);
}


int dy[8] = { 0,1,1,1,0,-1,-1,-1 },
	dx[8] = { 1,1,0,-1,-1,-1,0,1 };

char check[4][4];
typedef struct b {
	int y;
	int x;
}B;

B queue[16];
int in, out;

void func() {

	//초기화
	in = out = 0;
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++)
			check[y][x] = 0;


	for(int y =0 ;y<4;y++)
		for (int x = 0; x < 4; x++) {
			//1. 넣기
			B start = { y,x };
			check[y][x] = 1;
			queue[in++] = start;

			while (in != out) {
				B now = queue[out++];


			}
		}



}




int main() {
	scanf("%d", &W);
	int root = init(); //
	for (int i = 0; i < W; i++) {
		scanf("%s", string);
		add(root, string, 0);
	}
	
	scanf("\n%d", &BB);
	for (int b = 0; b < BB; b++) {

		for (int y = 0; y < 4; y++)
			scanf("\n%s", board[y]);

	}

	return 0;
}