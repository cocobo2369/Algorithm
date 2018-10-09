#include<stdio.h>
#define Max 1002
#define INF 1000000
int dy[4] = { 0,1,0,-1 },
	dx[4] = { 1,0,-1,0 };
int T, Y, X;
typedef struct v {
	int y;
	int x;
}V;

V q[Max*Max];
int in, out;
V start;
char map[Max][Max];
int checkF[Max][Max],
	checkS[Max][Max];


void bfsF() {
	//최초는 이미 넣어져있음
	while (in != out) {
		V from = q[out++];

		for (int i = 0; i < 4; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			if (1 > newy || newy > Y || 1 > newx || newx > X)continue;
			if (map[newy][newx] != '#' && checkF[newy][newx] == INF) {
				V to = { newy,newx };
				q[in++] = to;
				checkF[newy][newx] = checkF[from.y][from.x] + 1;
			}
		}
	}
}

int bfsS() {
	in = out = 0;
	q[in++] = start;
	checkS[start.y][start.x] = 1;

	while (in != out) {
		V from = q[out++];
		if (from.y == 1 || from.y == Y || from.x == 1 || from.x == X)
			return checkS[from.y][from.x];
		for (int i = 0; i < 4; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			if (1 > newy || newy > Y || 1 > newx || newx > X)continue;
			if (map[newy][newx] == '.' && checkS[newy][newx] == 0 && checkF[newy][newx] > (checkS[from.y][from.x]+1)) {
				V to = { newy,newx };
				q[in++] = to;
				checkS[newy][newx] = checkS[from.y][from.x] + 1;
			}
		}
	}
	return 0;
}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &X, &Y);
		
		//초기화
		in = out = 0;
		for (int y = 1; y <= Y; y++)
			for (int x = 1; x <= X; x++) {
				checkF[y][x] = INF;
				checkS[y][x] = map[y][x] = 0;
			}

		for (int y = 1; y <= Y; y++)
			for (int x = 1; x <= X; x++) {
				scanf("\n%c", &map[y][x]); //꿀팁
				if (map[y][x] == '*') {
					V fire = { y,x };
					q[in++] = fire;
					checkF[y][x] = 1;
				}
				else if (map[y][x] == '@')
					start.y = y, start.x = x;

			}
		bfsF();
		int res = bfsS();
		if (res == 0)	printf("IMPOSSIBLE\n");
		else			printf("%d\n", res);


	}
	return 0;
}