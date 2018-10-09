//2. 인접행렬 indegree 이용
#include<stdio.h>
#define Max 1001
int N, PD;
int map[Max][Max];

int q[Max*Max], in, out;
int indegree[Max];

int print[Max], pIdx;
//indegree가 check를 대신한다!
void tplSort() {
	//1.넣기
	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0)
			q[in++] = i;

	while (in != out) {
		int from = q[out++];
		print[pIdx++] = from;
		for (int to = 1; to <= N; to++)
			if (map[from][to] == 1) {
				indegree[to]--;
				if (indegree[to] == 0)
					q[in++] = to;
			}
	}
}


int main() {
	scanf("%d %d", &N, &PD);

	for (int i = 0; i < PD; i++) {
		int C;
		scanf("%d", &C);
		int v[Max];
		for (int c = 0; c < C; c++)
			scanf("%d", &v[c]);
		for (int c = 1; c < C; c++) {
			int from = v[c - 1],
				to = v[c];
			if (map[from][to] == 0) {
				map[from][to] = 1; //중복제거
				indegree[to]++;
			}
		}
	}
	tplSort();
	int res = 0;
	for (int i = 1; i <= N; i++)
		if (indegree[i] > 0) {
			res = 1;
			break;
		}
	if (res)printf("0\n");
	else
		for (int i = 0; i < N; i++)
			printf("%d\n", print[i]);
	return 0;
}