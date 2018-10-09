#include<stdio.h>
#include<malloc.h>
int N, M, S, E;
typedef struct node {
	int num;
	int edge;
	struct node * next;
} Node;

Node from[10001];
int check[10001];

Node mem[200001];
int memIdx;
Node * insert(int t, int e, Node * nextNode) {
	//1. �޸� �Ҵ�
	//Node * newNode = (Node *)malloc(sizeof(Node));
	//2. ������ �Է�
	//newNode->num = t;
	//newNode->edge = e;
	//3. next ó��
	//newNode->next = nextNode;
	mem[memIdx].num = t;
	mem[memIdx].edge = e;
	mem[memIdx].next = nextNode;
	return &mem[memIdx++];
}


int q[10000001];
int in, out;
int bfs(int limit) {

	check[S] = 1;
	q[in++] = S;

	while (in != out) {
		int now = q[out++];
		if (now == E)
			return 1;

		Node * t = from[now].next; //������������ ��Ŵ� �� ���� ����Ʈ�� ������带 ������ �迭�ϻ�
		while (t) {
			if (check[t->num] == 0 && limit <= t->edge) {
				check[t->num] = 1;
				q[in++] = t->num;
			}
			t = t->next;
		}
	}
	return 0;
}
int main() {

	scanf("%d %d", &N, &M);

	//�׷��� �ʱ�ȭ
	//for (int i = 1; i <= N; i++)
		//from[i].next = insert(0, 0, NULL);
	memIdx = 0;
	for (int i = 0; i < M; i++) {
		int f, t, e;
		scanf("%d %d %d", &f, &t, &e);
		from[f].next = insert(t, e, from[f].next);
		from[t].next = insert(f, e, from[t].next);
	}
	scanf("%d %d", &S, &E);

	int i = 0, j = 1000000000;
	int res = 0;
	while (i <= j) {

		for (int k = 0; k <= 10000; k++)
			check[k] = 0; //limit = mid �� ���� �������� ���̽��⋚���� check�� �ݵ�� �ʱ�ȭ�������
		in = out = 0;

		int mid = i + (j - i) / 2;
		if (bfs(mid)) {
			i = mid + 1;
			res = res > mid ? res : mid;
		}
		else
			j = mid - 1;
	}
	printf("%d\n", res);
	return 0;
}