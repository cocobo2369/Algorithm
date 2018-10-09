#include<stdio.h>

#define MaxN 32001
#define MaxE 100001

int N, E;

//�׷��� �𵨸� - ��������Ʈ
//1)����ü ����
typedef struct node {
	int n;
	struct node * next;
}Node;

//2) �׷��� �����
Node list[MaxN], 
	 mem[MaxE];
int memIdx;

Node * myalloc() { //���� �޸� �Ҵ��� ���� myalloc()
	return &mem[memIdx++];
}

//�������� 
//- �ֱ� : indegree = 0 �� ��, indegree �� check ����
//- ���� : ����� node�� indegree�� ���ҽ�Ű�� indegree = 0 �̵Ǹ� �ֱ�
int q[MaxE], in, out,
	indegree[MaxN];

void tplSort() {
	//1) ���� �ֱ� 
	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0)
			q[in++] = i;

	//2) ����
	while (in != out) {
		int from = q[out++];
		
		//4)���� �� ����ֱ�
		printf("%d ", from);
		Node * temp = list[from].next;
		while (temp) { // while���� �׻� next�� �̸� ����
			
			int to = temp->n;
			indegree[to]--;

			//3) �ֱ�
			if (indegree[to] == 0)
				q[in++] = to;

			temp = temp->next;
		}
	}
	return;
}

int main() {
	scanf("%d %d", &N, &E);

	//1) list �ʱ�ȭ
	for (int v = 1; v <= N; v++) {
		list[v].n = v;
		list[v].next = NULL;
	}


	//2) E �Է�
	for (int e = 0; e < E; e++) {
		int from, to;
		scanf("%d %d", &from, &to);
		
		Node * newNode = myalloc();
		newNode->n = to;
		newNode->next = list[from].next;
		
		list[from].next = newNode;
		//3) �������Ŀ��� �߿�!! indegree ����
		indegree[to]++;
	}

	tplSort();
	printf("\n");
	return 0;
}