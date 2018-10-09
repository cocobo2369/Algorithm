#include<stdio.h>
int dy[4] = { 0,1,0,-1 },
	dx[4] = { 1,0,-1,0 };

typedef struct node {
	int y;
	int x;
}Node;

Node q[10002];
int in, out;
int check[102][102];

int Y, X;
char map[102][102];

int bfs(int y, int x) {
	Node start = { 1,1 };
	q[in++] = start;
	check[1][1] = 1;

	while (in != out) {
		Node now = q[out++];

		if (now.y == Y && now.x == X)
			return check[now.y][now.x];
		for (int i = 0; i < 4; i++) {
			Node next = { now.y + dy[i] , now.x + dx[i] };
			if (1 > next.y || next.y > Y || 1 > next.x || next.x > X)continue;
			if (check[next.y][next.x] == 0 && map[next.y][next.x] == '1') {
				q[in++] = next;
				check[next.y][next.x] = check[now.y][now.x] + 1;
			}
		}
	}
}
int main() {
	scanf("%d %d", &Y, &X);
	for (int y = 1; y <= Y; y++)
		scanf("%s", &map[y][1]);
	printf("%d\n", bfs(Y, X));
}