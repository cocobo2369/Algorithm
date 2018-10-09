#include<stdio.h>

#define Max 300001
#define MaxC 26
#define MaxL 9
int W, B;
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


char selected[Max*MaxL];
int selectedcnt;

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

typedef struct q {
	int y;
	int x;
	int cnt;
	int now;
}Q;

int in, out;
char check[4][4];

int dy[] = { 0,1,1,1,0,-1,-1,-1 },
dx[] = { 1,1,0,-1,-1,-1,0,1 };
int score = 0;

char nowStr[MaxL], ansstr[MaxL];
int ansLen;
void find(Q now, char * nowStr) {

	if (now.cnt == 9)
		return;
	nowStr[now.cnt - 1] = board[now.y][now.x];

	if (trie[now.now].valid == 1) {
		if (selected[now.now] == 0) {
			nowStr[now.cnt] = 0;

			if (ansLen == now.cnt) {
				for (int i = 0; i < now.cnt; i++)
					if (nowStr[i] > ansstr[i])break;
					else if (nowStr[i] < ansstr[i]) {
						int j;
						for (j = i; j < now.cnt; j++)
							ansstr[j] = nowStr[j];
						ansstr[j] = 0;
						break;
					}
			}
			else if (ansLen < now.cnt) {
				int j;
				for (j = 0; j < now.cnt; j++)
					ansstr[j] = nowStr[j];
				ansstr[j] = 0;
				ansLen = now.cnt;
			}

			selected[now.now] = 1;
			selectedcnt++;
			if (now.cnt == 3 || now.cnt == 4)
				score += 1;
			else if (now.cnt == 5)
				score += 2;
			else if (now.cnt == 6)
				score += 3;
			else if (now.cnt == 7)
				score += 5;
			else if (now.cnt == 8)
				score += 11;
		}
	}


	for (int i = 0; i < 8; i++) {
		int newy = now.y + dy[i],
			newx = now.x + dx[i];
		if (0 > newy || newy > 3 || 0 > newx || newx > 3)continue;
		int c = board[newy][newx] - 'A';
		if (check[newy][newx] != 1 && trie[now.now].children[c] != -1) {
			Q next = { newy,newx,now.cnt + 1, trie[now.now].children[c] };
			check[newy][newx] = 1;
			find(next, nowStr);
			check[newy][newx] = 0;
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

	scanf("\n%d", &B);
	for (int b = 0; b < B; b++) {
		//1.ÃÊ±âÈ­
		score = selectedcnt = ansLen = 0;
		ansstr[0] = 'Z';
		for (int i = 0; i < Max*MaxL; i++)
			selected[i] = 0;

		for (int y = 0; y < 4; y++)
			scanf("\n%s", board[y]);

		for (int y = 0; y<4; y++)
			for (int x = 0; x < 4; x++) {
				int c = board[y][x] - 'A';
				if (trie[root].children[c] != -1) {
					Q start = { y,x,1,trie[root].children[c] };

					check[y][x] = 1;
					find(start, nowStr);
					check[y][x] = 0;
				}
			}
		printf("%d %s %d\n", score, ansstr, selectedcnt);
	}
	return 0;
}