#include<stdio.h>
#define Max 1001

int N, PD;

//list
typedef struct node {
	int v;
	struct node * next;
}Node;

//dummy를 생략함 - graph 탐색에는 의미가 없음, delete에는 필요하지만
Node list[Max], mem[Max*(Max - 1) / 2];
int memidx;

Node * myalloc() {
	return &mem[memidx++];
}

//topological sort
int indegree[Max];

int q[Max*(Max - 1) / 2];
int in, out;
int print[Max], pIdx;
void tplSort() {
	//1.넣기
	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0)
			q[in++] = i;

	while (in != out) {
		//2. 빼기
		int from = q[out++];
		print[pIdx++] = from;
		//3. 넣기
		Node * temp = list[from].next;
		while (temp) {
			int to = temp->v;
			indegree[to]--;
			if (indegree[to] == 0)
				q[in++] = to;
			temp = temp->next;
		}

	}
}

int main() {
	scanf("%d %d", &N, &PD);

	for (int i = 1; i <= N; i++) {
		list[i].v = i;
		list[i].next = NULL;
	}

	for (int i = 0; i < PD; i++) {
		int C;
		scanf("%d", &C);
		int v[Max];
		for (int c = 0; c < C; c++)
			scanf("%d", &v[c]);
		for (int c = 1; c < C; c++) {
			int from = v[c - 1],
				to = v[c];
			Node * newNode = myalloc();
			newNode->v = to;
			newNode->next = list[from].next;
			list[from].next = newNode;
			indegree[to]++;
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