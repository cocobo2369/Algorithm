#include<stdio.h>
#define Max 50
int dy[4] = { 0,1,0,-1 },
dx[4] = { 1,0,-1,0 };

int T, Y, X, B;
int map[Max][Max];

//bfs , q, check-->배추를 표시한 곳을 0으로 만듦으로써 check 생략
typedef struct v {
	int y;
	int x;
}V;
V q[Max*Max];
int in, out;

void bfs(V start) {
	in = out = 0;
	q[in++] = start;
	map[start.y][start.x] = 0;

	while (in != out) {
		V from = q[out++];

		for (int i = 0; i < 4; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			//주의 bfs 넣을 때 범위!!!!
			if (newy <0 || newy >Y - 1 || newx <0 || newx >X - 1)continue;
			if (map[newy][newx] == 1) {
				V temp = { newy,newx };
				q[in++] = temp;
				map[newy][newx] = 0;
			}
		}
	}

}
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &X, &Y, &B);

		while (B--) {
			int y, x;
			scanf("%d %d", &x, &y);
			map[y][x] = 1;
		}
		int cnt = 0;
		for (int y = 0; y<Y; y++)
			for (int x = 0; x < X; x++) {
				if (map[y][x] == 1) {
					cnt++;
					V start = { y,x };
					bfs(start);
				}
			}
		printf("%d\n", cnt);
	}
	return 0;
}