#include<stdio.h>
#define Max 1002
int dy[4] = { 0,1,0,-1 },
dx[4] = { 1,0,-1,0 };
int T, Y, X;
typedef struct v {
	int y;
	int x;
	int what;
}V;

V q[Max*Max * 2]; //불,상근 두개임
int in, out;
V start;
char map[Max][Max];
int checkF[Max][Max],
checkS[Max][Max];


int bfs() {
	//최초불은 이미 넣어져있음
	q[in++] = start;
	checkS[start.y][start.x] = 1;

	while (in != out) {
		V from = q[out++];
		if (from.what == 1 && (from.y == 1 || from.y == Y || from.x == 1 || from.x == X))
			return checkS[from.y][from.x];
		for (int i = 0; i < 4; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			if (1 > newy || newy > Y || 1 > newx || newx > X)continue;
			if (from.what == 0 && map[newy][newx] != '#' && checkF[newy][newx] == 0) {
				V to = { newy,newx, 0 };
				q[in++] = to;
				checkF[newy][newx] = checkF[from.y][from.x] + 1;
			}
			if (from.what == 1 && map[newy][newx] == '.' && checkS[newy][newx] == 0 && checkF[newy][newx] == 0) {
				V to = { newy,newx, 1 };
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
			for (int x = 1; x <= X; x++)
				checkF[y][x] = checkS[y][x] = map[y][x] = 0;


		for (int y = 1; y <= Y; y++)
			for (int x = 1; x <= X; x++) {
				scanf("\n%c", &map[y][x]); //꿀팁
				if (map[y][x] == '*') {
					V fire = { y,x,0 };
					q[in++] = fire;
					checkF[y][x] = 1;
				}
				else if (map[y][x] == '@')
					start.y = y, start.x = x, start.what = 1;

			}
		int res = bfs();
		if (res == 0)	printf("IMPOSSIBLE\n");
		else			printf("%d\n", res);


	}
	return 0;
}