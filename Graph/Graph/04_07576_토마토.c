#include<stdio.h>
int dy[4] = { 0,1,0,-1 },
dx[4] = { 1,0,-1,0 };

int X, Y;
int map[1002][1002];

typedef struct node {
	int y;
	int x;
}Node;
Node q[1000002];
int in, out;
int check[1002][1002];

int cnt, day = 1;

void bfs() {

	while (in != out) {
		Node now = q[out++];

		for (int i = 0; i < 4; i++) {
			Node next = { now.y + dy[i], now.x + dx[i] };
			if (1 > next.y || next.y > Y || 1 > next.x || next.x > X)continue;
			if (map[next.y][next.x] == 0 && check[next.y][next.x] == 0) {
				cnt--;
				q[in++] = next;
				check[next.y][next.x] = check[now.y][now.x] + 1;
				day = day > check[next.y][next.x] ? day : check[next.y][next.x];
			}
		}
	}

}
int main() {
	scanf("%d %d", &X, &Y);
	cnt = X*Y;
	for (int y = 1; y <= Y; y++)
		for (int x = 1; x <= X; x++) {
			scanf("%d", &map[y][x]);
			if (map[y][x] != 0)cnt--;
			if (map[y][x] == 1) {
				Node start = { y,x };
				q[in++] = start;
				check[y][x] = 1;
			}
		}
	bfs();
	if (cnt == 0)
		printf("%d\n", day - 1);
	else
		printf("-1\n");
	return 0;
}