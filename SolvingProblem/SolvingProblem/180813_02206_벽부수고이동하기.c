#include<stdio.h>
#define Max 1001
#define INF 100000000
int dy[4] = { 0,1,0,-1 },
	dx[4] = { 1,0,-1,0 };
int Y, X;
char map[Max][Max];
int course[Max][Max];
int check[3][Max][Max]; 
//check[0] 경로길이, check[1] 출발체크, check[2] 도착체크
typedef struct v {
	int y;
	int x;
}V;

V q[Max*Max];
int in, out;

V wall[Max*Max];
int wallIdx;
void bfs(V start, int who) {
	in = out = 0;
	q[in++] = start;
	check[who][start.y][start.x] = who;
	if (who == 1) {
		course[start.y][start.x] = check[1][start.y][start.x];
		check[0][start.y][start.x] = 1;
	}
	while (in != out) {
		V from = q[out++];

		for (int i = 0; i < 4; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			if (1 > newy || newy > Y || 1 > newx || newx > X)continue;
			V to = { newy, newx };
			if (check[who][newy][newx] == 0) {
				if (map[newy][newx] == '0') {
					q[in++] = to;
					check[0][newy][newx] = check[0][from.y][from.x] + 1;
				}
				check[who][newy][newx] = who;
				if(who == 1)
					course[newy][newx] = check[1][newy][newx];

				if (map[newy][newx] == '1') {
					if (check[1][newy][newx] == 1 && check[2][newy][newx] == 2)
						wall[wallIdx++] = to;
				}
			}
		}
	}
}

void bfsWall(V start) 
{
	in = out = 0;
	/*시작
	1. 1이 check되어있다
	2. map == '0' 인 길이다
	3. 경로중 최소길이*/

	V go;
	int min = INF;
	for (int i = 0; i < 4; i++) {
		int newy = start.y + dy[i],
			newx = start.x + dx[i];
		if (1 > newy || newy > Y || 1 > newx || newx > X)continue;
		if (check[1][newy][newx] == 1 && map[newy][newx] == '0') {
			if (check[0][newy][newx] < min) {
				go.y = newy, go.x = newx;
				min = check[0][newy][newx];
			}
		}
	}
	q[in++] = start;
	check[0][start.y][start.x] = check[0][go.y][go.x] + 1;

	while (in != out) {
		V from = q[out++];
		if (from.y == Y && from.x == X)
			return;
		for (int i = 0; i < 4; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			if (1 > newy || newy > Y || 1 > newx || newx > X)continue;
			if (map[newy][newx] == '0' && check[1][newy][newx] == 0) {
				V to = { newy, newx };
				q[in++] = to;
				check[0][newy][newx] = check[0][from.y][from.x] + 1;
				check[1][newy][newx] = 1;
			}
		}
	}
}
int main() {
	scanf("%d %d", &Y, &X);

	for(int y = 1 ;y<=Y;y++)
		scanf("%s" , &map[y][1]);

	V start = { 1,1 };
	bfs(start, 1);
	start.y = Y, start.x = X;
	bfs(start, 2);

	check[0][Y][X] = check[0][Y][X] == 0 ? INF : check[0][Y][X];
	int min = check[0][Y][X];
	for (int i = 0; i < wallIdx; i++) {
		for (int y = 1; y <= Y; y++)
			for (int x = 1; x <= X; x++)
				check[1][y][x] = course[y][x];
		bfsWall(wall[i]);
		check[0][Y][X] = check[0][Y][X] == 0 ? INF : check[0][Y][X];
		min = min < check[0][Y][X] ? min : check[0][Y][X];
	}

	printf("%d\n", min >= INF ? -1 : min );
	return 0;
}