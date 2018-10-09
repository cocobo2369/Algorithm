#include<stdio.h>
#define Max 100
int dy[4] = { 0,1,0,-1 },
dx[4] = { 1,0,-1,0 };

int Y, X, K;
int map[Max][Max];

typedef struct v {
	int y;
	int x;
}V;
V q[Max*Max];
int in, out;

int res[Max], resIdx;
int bfs(V start) {
	int cnt = 0;
	in = out = 0;

	q[in++] = start;
	map[start.y][start.x] = 1;
	cnt++;
	while (in != out) {
		V from = q[out++];

		for (int i = 0; i < 4; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			if (newy <0 || newy > Y - 1 || newx <0 || newx >X - 1)continue;
			if (map[newy][newx] == 0) {
				V temp = { newy, newx };
				q[in++] = temp;
				map[newy][newx] = 1;
				cnt++;
			}
		}
	}
	return cnt;
}
int main() {
	scanf("%d %d %d", &Y, &X, &K);
	while (K--) {
		int sx, sy, ex, ey;
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
		for (int y = sy; y < ey; y++)
			for (int x = sx; x < ex; x++)
				map[y][x] = 1;
	}

	for (int y = 0; y<Y; y++)
		for (int x = 0; x<X; x++)
			if (map[y][x] == 0) {
				V start = { y,x };
				res[resIdx++] = bfs(start);
			}


	printf("%d\n", resIdx);
	//버블정렬
	int idx = 0;
	for (int n = 0; n < resIdx; n++) {
		for (int i = 1; i < resIdx - n; i++) {
			if (res[i - 1] > res[i]) {
				int temp = res[i - 1];
				res[i - 1] = res[i];
				res[i] = temp;
			}
		}
	}
	for (int i = 0; i < resIdx; i++)
		printf("%d ", res[i]);
	printf("\n");
	return 0;
}