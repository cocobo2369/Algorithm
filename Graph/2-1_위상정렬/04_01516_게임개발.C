#include<stdio.h>
#define MAX 501

typedef struct node {
	int num;
	struct node * next;
}Node;

Node list[MAX],
	dummy[MAX],
	mem[MAX*100];
int memIdx;
int indegree[MAX],q[MAX], in, out;
int time[MAX], sum[MAX];
Node * myalloc() {
	return &mem[memIdx++];
}

int N;

void tplSort() {
	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0)
			q[in++] = i;
	
	while (in != out) {
		int now = q[out++];
		Node * next = list[now].next->next;
		while (next) {
			int num = next->num;
			indegree[num]--;
			sum[num] = sum[num] > sum[now] + time[num] ? sum[num] : sum[now] + time[num];
			if (indegree[num] == 0)
				q[in++] = num;
			next = next->next;
		}
	}
}
int main() {
	scanf("%d", &N);

	for (int i = 1; i <= N; i++) {
		list[i].num = i;
		list[i].next = &dummy[i];
		dummy[i].num = 0;
		dummy[i].next = NULL;
	}

	for(int i = 1; i<=N;i++) {
		scanf("%d", &time[i]);
		sum[i] = time[i];
		while (1) {
			int num;
			scanf("%d", &num);
			if (num == -1)break;

			Node * newNode = myalloc();
			newNode->num = i;
			newNode->next = list[num].next->next;
			list[num].next->next = newNode;
			indegree[i]++;
		}
	}
	tplSort();
	for (int i = 1; i <= N; i++)
		printf("%d\n", sum[i]);
	return 0;
}