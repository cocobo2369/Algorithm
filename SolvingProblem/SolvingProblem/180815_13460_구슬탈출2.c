#include<stdio.h>
#define Max 11
int dy[4] = { 0,1,0,-1 },
	dx[4] = { 1,0,-1,0 };

int Y, X;
char map[Max][Max];

typedef struct v {
	int y;
	int x;
	int color; // red : 0 blue : 1
	int d;
}V;

V red, blue, hole;
char check[2][Max][Max];

V q[2][Max*Max];
int in, out;

int bfs() {
	q[0][in] = red;
	q[1][in] = blue;
	in++;
	check[0][red.y][red.x] = check[1][blue.y][blue.x] = 1;

	while (in != out) {
		V fromR = q[0][out];
		V fromB = q[1][out];
		out++;

		//������ R�� �ִ� �Ͱ� B�� �ִ°� �ٸ� �� ���� �ʳ�
		//R�� 4���� ��� �̵��� �Ϳ� ���� �ִµ�
		//B�� 2���⸸ �̵������ؼ� �־����ٸ�?? ==> �����ڸ��� �־������ ������ check���� �ɷ����ϱ�

		for (int i = 0; i < 4; i++) {

			int newyR = fromR.y + dy[i],
				newxR = fromR.x + dx[i],
				newyB = fromB.y + dy[i],
				newxB = fromB.x + dx[i];

			if (1 > newyR || newyR > Y || 1 > newxR || newxR > X)continue;
			if (1 > newyB || newyB > Y || 1 > newxB || newxB > X)continue;

			
			//red �ֱ�
			V to[2];
			if (map[newyR][newxR] == '.' && check[0][newyR][newxR] == 0)
				to[0].color= 0, to[0].d = i, to[0].y = newyR, to[0].x=newxR;
			else 
				to[0].color = 0, to[0].d = i, to[0].y = fromR.y, to[0].x = fromR.x;
			//blue �ֱ�
			if (map[newyB][newxB] == '.' && check[1][newyB][newxB] == 0)
				to[1].color = 1, to[1].d = i, to[1].y = newyB, to[1].x = newxB;
			else
				to[1].color = 1, to[1].d = i, to[1].y = fromB.y, to[1].x = fromB.x;

			for (int n = 0; n < 10; n++) {
				int yR = to[0].y + dy[to[0].d]
			}


		}




	}
}

int main() {
	scanf("%d %d", &Y, &X);
	for(int y= 1;y<=Y;y++)
		for (int x = 1; x <= X; x++) {
			scanf("\n%c", &map[y][x]);
			if (map[y][x] == 'R')		map[y][x] = '.', red.y = y, red.x = x, red.color = 'R';
			else if (map[y][x] == 'B')	map[y][x] = '.', blue.y = y, blue.x = x, blue.color = 'B';
			else if (map[y][x] == 'O')	hole.y = y, hole.x = x, hole.color = 'O';
		}

}