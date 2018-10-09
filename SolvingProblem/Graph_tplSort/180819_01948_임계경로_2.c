#include<stdio.h>
#define MaxV 10001
#define MaxE 100001
int N, E, S, G;
//그래프 모델링
typedef struct v {
	int n;
	int e;
	struct v *next;
}V;


V list[MaxV], mem[MaxE*2], Rlist[MaxV];
int memIdx;

V * myalloc() {
	return &mem[memIdx++];
}
//tplsort
int indegree[MaxV], q[MaxE];
int in, out;

//solve
int time[MaxV];
void tplSort() {

	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0)
			q[in++] = i;

	while (in != out) {
		int from = q[out++];
		V * temp = list[from].next;
		while (temp) {
			int to = temp->n, e = temp->e;
			indegree[to]--;
			if (time[to] < (time[from] + e))
				time[to] = time[from] + e;

			if (indegree[to] == 0)
				q[in++] = to;
			temp = temp->next;
		}
	}
	return;
}

int course() {
	int res = 0;
	in = out = 0;

	q[in++] = G;
	indegree[G] = 1;
	while (in != out) {
		int from = q[out++];
		V * temp = Rlist[from].next;
		while (temp) {
			int to = temp->n, e = temp->e;
			if ((time[from] - e) == time[to]) {
				res++;
				if (indegree[to] == 0) {
					indegree[to] = 1;
					q[in++] = to;
				}
			}
			temp = temp->next;
		}
	}
	return res;
}

int main() {
	scanf("%d %d", &N, &E);
	for (int i = 1; i <= N; i++) {
		list[i].n = Rlist[i].n = i;
		list[i].e = Rlist[i].e = 0;
		list[i].next = Rlist[i].next = NULL;
	}
	for (int i = 0; i < E; i++) {
		int from, to, e;
		scanf("%d %d %d", &from, &to, &e);
		V * newNode = myalloc();
		newNode->n = to;
		newNode->e = e;
		newNode->next = list[from].next;
		list[from].next = newNode;
		indegree[to]++;

		//경로찾기그래프
		newNode = myalloc();
		newNode->n = from;
		newNode->e = e;
		newNode->next = Rlist[to].next;
		Rlist[to].next = newNode;

	}
	scanf("%d %d", &S, &G);
	tplSort();
	printf("%d\n%d\n", time[G], course());
	return 0;
}