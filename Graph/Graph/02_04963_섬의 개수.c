#include<stdio.h>

int dy[8] = { 0,1,1,1,0,-1,-1,-1 },
	dx[8] = { 1,1,0,-1,-1,-1,0,1 };

typedef struct node {
	int y;
	int x;
}Node;

Node q[2500];
int in, out;
int check[52][52];

int map[52][52];
int W = 1, H = 1;

int land;

void bfs(int y, int x) {
	Node start = { y,x };
	q[in++] = start;
	check[y][x] = 1;

	while (in != out) {

		Node now = q[out++];

		for (int i = 0; i < 8; i++) {
			Node next = { now.y + dy[i], now.x + dx[i] };
			if (1 > next.y || next.y > H || 1 > next.x || next.x > W)continue;
			if (map[next.y][next.x] == 1 && check[next.y][next.x] == 0) {
				q[in++] = next;
				check[next.y][next.x] = 1;
			}
		}
	}
}
int main() {
	
	while (1) {
		land = in = out = 0;
		for (int y = 1; y <= H; y++)
			for (int x = 1; x <= W; x++) {
				check[y][x] = 0;
			}

		scanf("%d %d", &W, &H);
		if (W == 0 && H == 0)break;
		for (int y = 1; y <= H; y++)
			for (int x = 1; x <= W; x++) {
				scanf("%d", &map[y][x]);
			}
		for (int y = 1; y <= H; y++)
			for (int x = 1; x <= W; x++)
				if (map[y][x] == 1 && check[y][x] == 0) {
					land++;
					bfs(y, x);
				}
		printf("%d\n", land);
	}
}