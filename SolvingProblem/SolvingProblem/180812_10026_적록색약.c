#include<stdio.h>
#define Max 101
int dy[4] = { 0,1,0,-1 },
	dx[4] = { 1,0,-1,0 };
int N;
char map[Max][Max];

typedef struct v {
	int y;
	int x;
}V;

V q[Max*Max];
int in, out;
int check[Max][Max];

void bfs(V start) {
	in = out = 0; //√ ±‚»≠
	q[in++] = start;
	check[start.y][start.x] = 1;

	while (in != out) {
		V from = q[out++];

		for (int i = 0; i < 4; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			if (1 > newy || newy > N || 1 > newx || newx > N)continue;
			if (check[newy][newx] == 0 && map[start.y][start.x] == map[newy][newx]) {
				V to = { newy,newx };
				q[in++] = to;
				check[newy][newx] = 1;
			}
		}
	}
}


int main() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%s", &map[i][1]);
	}
	int cnt = 0;
	for(int y = 1; y <= N;y++)
		for (int x = 1; x <= N; x++) {
			if (check[y][x] == 0) {
				V start = { y,x };
				bfs(start);
				cnt++;
			}
		}

	printf("%d ", cnt);

	for (int y = 1; y <= N; y++)
		for (int x = 1; x <= N; x++) {
			check[y][x] = 0;
			if (map[y][x] == 'G')
				map[y][x] = 'R';
		}

	cnt = 0;
	for (int y = 1; y <= N; y++)
		for (int x = 1; x <= N; x++) {
			if (check[y][x] == 0) {
				V start = { y,x };
				bfs(start);
				cnt++;
			}
		}

	printf("%d\n", cnt);
	return 0;
}