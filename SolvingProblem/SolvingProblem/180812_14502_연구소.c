#include<stdio.h>
#define Max 9
int Y, X;
int max = 0;
int dy[4] = { 0,1,0,-1 },
	dx[4] = { 1,0,-1,0 };
typedef struct v {
	int y;
	int x;
}V;
V space[Max*Max];
int spaceCheck[Max*Max];
int spaceIdx;
//백트래킹으로 구현
int map[Max][Max];
int check[Max][Max];
V q[Max*Max];
int in, out;
int bfs(V start) {
	int cnt = 0;
	in = out = 0;

	q[in++] = start;
	check[start.y][start.x] = 2;

	while (in != out) {
		V from = q[out++];

		for (int i = 0; i < 4; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			if (1 > newy || newy > Y || 1 > newx || newx > X)continue;
			if ((check[newy][newx] == 0) && (map[newy][newx] == 0)) {
				V temp = { newy, newx };
				q[in++] = temp;
				check[newy][newx] = 2;
				cnt++;
			}
		}
	}

	return cnt;
}

void makeWall(V now, int cnt) {
	if (cnt == 0) {
		int res = spaceIdx-3;

		for (int y = 1; y <= Y; y++)
			for (int x = 1; x <= X; x++)
				check[y][x] = 0;

		for(int i = 0 ;i<spaceIdx;i++)
			if (spaceCheck[i]) {
				int y = space[i].y,
					x = space[i].x;
				check[y][x] = 3;
			}

		for(int y= 1; y<=Y;y++)
			for (int x = 1; x <= X; x++)
			{
				if (map[y][x] == 2) {
					V start = { y,x };
					res = res - bfs(start);
				}
			}
		max = max > res ? max : res;
		return;
	}

	for (int i = 0; i < spaceIdx; i++) {
		if (spaceCheck[i] == 0) {
			spaceCheck[i] = 1;
			makeWall(space[i], cnt-1);
			spaceCheck[i] = 0;
		}
	}	
}

int main() {
	scanf("%d %d", &Y, &X);
	for(int y = 1; y <=Y;y++)
		for (int x = 1; x <= X; x++) {
			scanf("%d", &map[y][x]);
			if (map[y][x] == 0) {
				V temp = { y,x };
				space[spaceIdx++] = temp;
			}
		}
	makeWall(space[0], 3);
	printf("%d\n",max);
	return 0;
}