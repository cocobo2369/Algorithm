#include<stdio.h>
#define Max 101 
int Y, X;
int dy[5] = { 0, 0, 0, 1, -1 },
dx[5] = { 0, 1,-1, 0, 0 };
int left[5] = { 0, 4, 3, 1, 2 },
right[5] = { 0, 3, 4, 2, 1 };
typedef struct v {
	int y;
	int x;
	int d;
}V;

V q[Max*Max * 4]; //tip q�� ���� ����� y, x, d �̴�. y <Max, x <Max, d<4 �̹Ƿ� Max*Max*4��
int in, out;
int check[5][Max][Max];

char map[Max][Max];
V start, end;

int bfs(V start) {
	//1. ���� �ֱ�
	q[in++] = start;
	check[start.d][start.y][start.x] = 1;

	while (in != out) {
		V from = q[out++];

		//4. �ִ� �� ������ ���� ������ ���� üũ
		if ((from.d == end.d) && (from.y == end.y) && (from.x == end.x))
			return check[end.d][end.y][end.x] - 1;
		//5���� ���̽�
		int newy, newx, newd;

		//1. left ���� �ٲٱ� - ������ġ�� map[y][x] = 0 �� ��Ȳ
		if (check[left[from.d]][from.y][from.x] == 0) {
			newy = from.y, newx = from.x, newd = left[from.d];
			V to = { newy, newx, newd };
			q[in++] = to;
			check[to.d][to.y][to.x] = check[from.d][from.y][from.x] + 1;
		}
		//2. right ���� �ٲٱ� - ������ġ�� map[y][x] = 0 �� ��Ȳ
		if (check[right[from.d]][from.y][from.x] == 0) {
			newy = from.y, newx = from.x, newd = right[from.d];
			V to = { newy, newx, newd };
			q[in++] = to;
			check[to.d][to.y][to.x] = check[from.d][from.y][from.x] + 1;
		}

		//3. �� ���⿡�� �����ϱ�
		newy = from.y, newx = from.x, newd = from.d;
		for (int i = 0; i < 3; i++) {
			newy += dy[newd], newx += dx[newd];
			//��ġ�̵� �׻� ���� üũ
			if (map[newy][newx] == 1 || 1 > newy || newy > Y || 1 > newx || newx > X)break;
			if (check[newd][newy][newx] == 0) {
				V to = { newy, newx, newd };
				q[in++] = to;
				check[newd][newy][newx] = check[from.d][from.y][from.x] + 1;
			}
		}
	}
}

int main() {
	scanf("%d %d", &Y, &X);

	for (int y = 1; y <= Y; y++)
		for (int x = 1; x <= X; x++)
			scanf("%d", &map[y][x]);
	scanf("%d %d %d %d %d %d", &start.y, &start.x, &start.d,
		&end.y, &end.x, &end.d);
	printf("%d\n", bfs(start));
	return 0;
}