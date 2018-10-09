#include<stdio.h>
int dy[4] = { 0,1,0,-1 },
	dx[4] = { 1,0,-1,0 };

typedef struct node {
	int y;
	int x;
}Node;
int N;
char map[27][27];

Node q[700];
int in, out;
int check[27][27];

int land;
int landNum[350];
void bfs(int y, int x) {
	//1. 넣기
	Node start = { y,x };
	q[in++] = start;
	check[y][x] = 1;
	landNum[land] ++;

	while (in != out) {
		//2. 빼기
		Node now = q[out++];

		//3. 넣기
		for (int i = 0; i < 4; i++) {
			Node next = { now.y + dy[i], now.x + dx[i] };
			if (1 > next.y || next.y > N || 1 > next.x || next.x > N)continue;
			//항상 다음 위치에 대한 판단을 할 땐 다음 위치의 범위를 신경써야한다.
			
			if (check[next.y][next.x] == 0 && map[next.y][next.x] == '1') {
				q[in++] = next;
				check[next.y][next.x] = 1;
				landNum[land]++;
			}
		}
	}
}

int main() {
	scanf("%d", &N);
	for (int y = 1; y <= N; y++)
		scanf("%s", &map[y][1]);

	for(int y= 1 ;y<=N;y++)
		for (int x = 1; x <= N; x++) {
			if (map[y][x] == '1' && check[y][x] == 0) {
				land++;
				bfs(y, x);
			}
		}

	for (int i = 1; i <= land; i++) {
		for (int j = i+1; j <= land; j++) {
			if (landNum[i] > landNum[j]) {
				int temp = landNum[i];
				landNum[i] = landNum[j];
				landNum[j] = temp;
			}
		}
	}
	printf("%d\n", land);
	for (int i = 1; i <= land; i++)
		printf("%d\n", landNum[i]);
	return 0;
}