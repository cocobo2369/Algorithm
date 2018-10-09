#include<stdio.h>
#define Max 20

int map[1365][Max][Max], idx;
int N,max;
int brute(int cnt, int step) {
	if (step == 5)
		return max;
	//1. �������� ���̱�
	idx++;
	for (int y = 0; y < N; y++) {
		int now=0,plus = 0;
		for (int x = 0; x < N; x++) {
			if (map[cnt][y][x] != 0) {
				if (now == 0)
					now = map[cnt][y][x];
				else{
					if (now == map[cnt][y][x]) {
						map[idx][y][plus++] = 2 * now;
						max = max > now * 2 ? max : now * 2;
						now = 0;
					}
					else {
						map[idx][y][plus++] = now;
						now = map[cnt][y][x];
					}
				}
			}
		}
		if (now != 0)
			map[idx][y][plus++] = now;
	}
	brute(idx,step+1);

	//2. �������� ���̱�
	idx++;
	for (int y = 0; y < N; y++) {
		int now = 0, plus = N-1;
		for (int x = N - 1; x >= 0; x--) {
			if (map[cnt][y][x] != 0) {
				if (now == 0)
					now = map[cnt][y][x];
				else {

					if (now == map[cnt][y][x]) {
						map[idx][y][plus--] = now * 2;
						max = max > now * 2 ? max : now * 2;
						now = 0;
					}
					else {
						map[idx][y][plus--] = now;
						now = map[cnt][y][x];
					}
				}
			}
		}
		if (now != 0)
			map[idx][y][plus--] = now;
	}
	brute(idx,step+1);
	//3. ���� ���̱�
	idx++;
	for (int x = 0; x < N; x++) {
		int flag = 0, now = 0, plus = 0;
		for (int y = 0; y < N; y++) {
			if (map[cnt][y][x] != 0) {
				if (now == 0)
					now = map[cnt][y][x];
				else {

					if (now == map[cnt][y][x]) {
						map[idx][plus++][x] = now * 2;
						max = max > now * 2 ? max : now * 2;
						now = 0;
					}
					else {
						map[idx][plus++][x] = now;
						now = map[cnt][y][x];
					}
				}
			}
		}
		if (now != 0)
			map[idx][plus++][x] = now;
	}
	brute(idx,step+1);
	//4. �Ʒ��� ���̱�
	idx++;
	for (int x = 0; x < N; x++) {
		int now = 0, plus = N-1;
		for (int y = N - 1; y >= 0; y--) {
			if (map[cnt][y][x] != 0) {
				if (now == 0)
					now = map[cnt][y][x];
				else {

					if (now == map[cnt][y][x]) {
						map[idx][plus--][x] = now * 2;
						max = max > now * 2 ? max : now * 2;
						now = 0;
					}
					else {
						map[idx][plus--][x] = now;
						now = map[cnt][y][x];
					}
				}
			}
		}
		if (now != 0)
			map[idx][plus--][x] = now;
	}
	brute(idx,step+1);
}
//�̷����� ���� �߿��Ѱ� �ʹ��� ���鵵 max�� �ĺ��� �� �� �ִٴ� ���
//�� ���ϰ� ������ ���� max�� ������ �ȵ�!!!
int main() {
	scanf("%d", &N);
	for(int y = 0 ;y<N;y++)
		for (int x = 0; x < N; x++) {
			scanf("%d", &map[idx][y][x]);
			max = max > map[idx][y][x] ? max : map[idx][y][x];
		}
	brute(idx, 0);
	printf("%d\n", max);
	return 0;
}