#include<stdio.h>
#define Max 300
int dy[8] = { -1, 1, 2, 2 , 1, -1, -2, -2 },
	dx[8] = { 2, 2, 1, -1, -2, -2,-1, 1 };
int L;
typedef struct v {
	int y;
	int x;
}V;

V q[Max*Max];
int in, out;

int check[Max][Max];
int sy, sx, ey, ex;
int bfs(V start) {

	in = out = 0;
	for (int y = 0; y < L; y++)
		for (int x = 0; x < L; x++)
			check[y][x] = 0;
	q[in++] = start;
	check[start.y][start.x] = 1;

	while (in != out) {
		V from = q[out++];
		if (from.y == ey && from.x == ex)
			return check[ey][ex]-1;
		for (int i = 0; i < 8; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			if (0 > newy || newy > L-1 || 0 > newx || newx > L-1)continue;
			if (check[newy][newx] == 0) {
				V to = { newy, newx };
				check[newy][newx] = check[from.y][from.x] + 1;
				q[in++] = to;
			}
		}

	}
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d %d %d", &L, &sy, &sx, &ey, &ex);
		V start = { sy, sx };
		printf("%d\n", bfs(start));
	}
	return 0;
}