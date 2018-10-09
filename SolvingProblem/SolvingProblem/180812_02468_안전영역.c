#include<stdio.h>
#define Max 101
int dy[4] = { 0,1,0,-1 },
	dx[4] = { 1,0,-1,0 };

int map[Max][Max];

typedef struct v {
	int y;
	int x;
}V;

V q[Max*Max];
int in, out,
	check[Max][Max];
int N, maxh = 0;

void bfs(V start) {
	in = out = 0;
	q[in++] = start;
	check[start.y][start.x] = 1;

	while (in != out) {
		V from = q[out++];

		for (int i = 0; i < 4; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			if (1 > newy || newy > N || 1 > newx || newx > N)continue;
			if (check[newy][newx] == 0) {
				V temp = { newy,newx };
				q[in++] = temp;
				check[newy][newx] = 1;
			}
		}
	}
}

int main() {
	scanf("%d", &N);
	for(int y= 1 ;y<=N;y++)
		for (int x = 1; x <= N; x++) {
			int h;
			scanf("%d", &h);
			map[y][x] = h;
			maxh = maxh > h ? maxh : h;
		}

	int maxcnt = 0;
	for (int h = 0; h < maxh; h++) {
		// ÃÊ±âÈ­
		for (int y = 1; y <= N; y++)
			for (int x = 1; x <= N; x++)
				if (map[y][x] <= h)
					check[y][x] = 1;
				else
					check[y][x] = 0;
		int cnt = 0;
		for (int y = 1; y <= N; y++)
			for (int x = 1; x <= N; x++) {
				if (check[y][x] == 0) {
					cnt++;
					V start = { y,x };
					bfs(start);
				}
			}
		maxcnt = maxcnt > cnt ? maxcnt : cnt;
	}
	printf("%d\n", maxcnt);
	return 0;
}