#include<stdio.h>
#define Max 301
int dy[4] = { 0,1,0,-1 },
	dx[4] = { 1,0,-1,0 };
int Y, X;
int map[Max][Max];
int glacier;

typedef struct v {
	int y;
	int x;
}V;
V q[Max*Max];
int in, out;

V qMelting[Max*Max];
int mIn, mOut;

int check[Max][Max];
int melt[Max][Max];
void bfsGlacier(V start){
	in = out = mIn = mOut = 0;
	for (int y = 1; y <= Y; y++)
		for (int x = 1; x < X; x++)
			check[y][x] = 0;
	q[in++] = start;
	check[start.y][start.x] = 1;

	//����ã��
	while (in != out) {
		V from = q[out++];

		int zero = 0;
		for (int i = 0; i < 4; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			if (map[newy][newx] == 0)	zero++;
			else if (check[newy][newx] == 0) {
				V to = { newy, newx };
				q[in++] = to;
				check[newy][newx] = 1;
			}
		}
		//bfsGlacier �� check =1 �� ���� �����̸�, ���� ��Ե� ���� melt�� ����Ǿ�����

		if (zero > 0) {
			melt[from.y][from.x] = zero;
			V temp = { from.y, from.x };
			qMelting[mIn++] = temp;
		}
	}
	//���̱�
	while (mIn != mOut) {
		V from = qMelting[mOut++];
		if (map[from.y][from.x] - melt[from.y][from.x] > 0)
			map[from.y][from.x] -= melt[from.y][from.x];
		else {
			map[from.y][from.x] = 0;
			check[from.y][from.x] = 0;
			glacier--;
		}
	}
}

int bfsCheck(V start) {
	int cnt = 0;
	in = out = 0;
	q[in++] = start;
	check[start.y][start.x] = 0; //1�κκи� ���⶧���� 0���� üũ�� �ٲ�
	cnt++;
	while (in != out) {
		V from = q[out++];

		for (int i = 0; i < 4; i++) {
			int newy = from.y + dy[i],
				newx = from.x + dx[i];
			if (check[newy][newx] == 1) {
				V to = { newy, newx };
				q[in++] = to;
				check[newy][newx] = 0;
				cnt++;
			}
		}
	}
	return cnt == glacier ? 0 : 1;
}


int main() {
	scanf("%d %d", &Y, &X);
	
	for (int y = 1; y <= Y; y++)
		for (int x = 1; x <= X; x++) {
			scanf("%d", &map[y][x]);
			glacier += (map[y][x] > 0 ? 1 : 0);
		}
	while (glacier) {
		int cnt = 0;
		for(int y= 1; y<=Y;y++)
			for(int x =1;x<=X;x++)

				if (map[y][x] != 0) {
					V start = { y,x };
					bfsGlacier(start);
					cnt++;

					for(int yy =1;yy<=Y;yy++)
						for(int xx =1; xx<X;xx++)
							if (check[yy][xx] == 1) {
								V start = { yy,xx };
								if (bfsCheck(start)) {
									printf("%d\n", cnt);
									return 0;
								}
								else {
									yy = Y;
									break;
								}
							}
				}
	}
	printf("0\n");
	return 0;
}
