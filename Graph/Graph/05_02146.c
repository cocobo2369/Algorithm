#include<stdio.h>
int dy[4] = { 0, 1, 0, -1 },
	dx[4] = { 1, 0, -1, 0 };
int N;

typedef struct node {
	int y;
	int x;
}Node;
int map[102][102];
int land[102][102];
int check[102][102];

int mIn, mOut, bIn, bOut;
Node mapQ[100001];
Node bridQ[100001];

int LAND, min = 987654321;
void mapBFS(int y, int x) {

	//1.최초한개 넣기, bfs는 넣을 때 check 한다
	Node start = { y,x };
	mapQ[mIn++] = bridQ[bIn++] = start;
	land[y][x] = LAND;
	check[y][x] = 1;

	while (mIn != mOut) {
		//2. 빼기
		Node now = mapQ[mOut++];

		//3. 넣기
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i],
				nx = now.x + dx[i];
			if (check[ny][nx] == 0 && map[ny][nx] == 1) {
				Node n = { ny, nx };
				mapQ[mIn++] = bridQ[bIn++] = n;
				land[ny][nx] = LAND;
				check[ny][nx] = 1;
			}
		}
	}
}

void bfs() {

	//1. 넣기- 벌써 땅이 넣어져있다.
	while (bIn != bOut) {
		//2. 빼기
		Node now = bridQ[bOut++];

		//3. 넣기
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i],
				nx = now.x + dx[i];
			if (check[ny][nx] == 0 && map[ny][nx] == 0) {
				Node n = { ny, nx };
				bridQ[bIn++] = n;
				check[ny][nx] = check[now.y][now.x] + 1;
			}
			if (map[ny][nx] == 1 && land[ny][nx] != LAND) {
				min = min < (check[now.y][now.x] - 1) ? min : (check[now.y][now.x] - 1);
				return;
			}
		}
	}
}
int main() {
	scanf("%d", &N);
	for (int y = 1; y <= N; y++)
		for (int x = 1; x <= N; x++)
			scanf("%d", &map[y][x]);
	for (int i = 0; i <= N + 1; i++)
		land[0][i] = land[N + 1][i] = land[i][0] = land[i][N + 1] =
		check[0][i] = check[N + 1][i] = check[i][0] = check[i][N + 1] = 987654321;

	for (int y = 1; y <= N; y++) {
		for (int x = 1; x <= N; x++) {
			if (land[y][x] != 0 || map[y][x] == 0)continue;
			mIn = mOut = bIn = bOut = 0;
			for (int y = 1; y <= N; y++)
				for (int x = 1; x <= N; x++)
					check[y][x] = 0;
			LAND++;
			mapBFS(y, x);
			bfs();
		}
	}
	printf("%d\n", min);
	return 0;
}

