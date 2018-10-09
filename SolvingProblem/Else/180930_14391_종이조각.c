#include<stdio.h>

#define Max 5
int Y, X;

char map[Max][Max], check[Max][Max];
int max;
int cnt;

void dfs(int starty, int startx, int sum) {


	//y방향
	int num = 0;
	int y;
	for (y = starty; y < Y; y++) {
		if (check[y][startx] == 1)
			break;
		else {

			num *= 10;
			num += (map[y][startx] - '0');
			check[y][startx] = 1;
			cnt++;

			if (cnt == Y*X) {
				max = max > sum+num ? max : sum+num;
				check[y][startx] = 0;
				cnt--;
				break;
			}


			for (int yy = 0; yy < Y; yy++)
				for (int xx = 0; xx < X; xx++)
					if (check[yy][xx] == 0)
						dfs(yy, xx, sum + num);
		}
	}
	for (int ty = starty; ty < y; ty++)
		check[ty][startx] = 0, cnt--;


	//x방향
	num = 0;
	int x;
	for (x = startx; x < X; x++) {
		if (check[starty][x] == 1)
			break;
		else {
			num *= 10;
			num += (map[starty][x] - '0');
			check[starty][x] = 1;
			cnt++;

			if (cnt == Y*X) {
				max = max > sum+num ? max : sum+num;
				check[starty][x] = 0;
				cnt--;
				break;
			}


			for (int yy = 0; yy < Y; yy++)
				for (int xx = 0; xx < X; xx++)
					if (check[yy][xx] == 0)
						dfs(yy, xx, sum + num);
		}
	}

	for (int tx = startx; tx < x; tx++)
		check[starty][tx] = 0,cnt--;
}

int main() {
	scanf("%d %d", &Y, &X);
	for (int y = 0; y < Y; y++)
		scanf("%s", map[y]);
	dfs(0, 0, 0);

	printf("%d\n", max);

	return 0;
}
