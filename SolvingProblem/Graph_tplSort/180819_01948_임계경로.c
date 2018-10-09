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


V list[MaxV], mem[MaxE];
int memIdx;

V * myalloc() {
	return &mem[memIdx++];
}
//tplsort
int indegree[MaxV],q[MaxE];
int in, out;

//solve
int time[MaxV],totalCourse[MaxV];
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
			if (time[to] < (time[from] + e)) {
				time[to] = time[from] + e;
				totalCourse[to] = totalCourse[from]+1;
			}
			else if (time[to] == (time[from] + e))
				totalCourse[to] += (totalCourse[from]+1);
			if (indegree[to] == 0) {
				q[in++] = to;
			}
			temp = temp->next;
		}
	}

	return;
}


int main() {
	scanf("%d %d", &N, &E);
	for (int i = 1; i <= N; i++) {
		list[i].n = i;
		list[i].e = 0;
		list[i].next = NULL;
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
	}
	scanf("%d %d", &S, &G);
	tplSort();
	printf("%d\n%d\n", time[G], totalCourse[G]);
	return 0;
}