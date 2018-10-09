//ver1. �������, ����Ŭ �Լ�
// ������ ��
/* ������ �ߺ��� ����ϴ��� ������� �ʴ����� ��������
������ �ߺ��� ����Ѵٸ� list�� �߰��� �� �˻��� �ʿ��ϴ�
list���� ������ ������ ���� �Ǹ� ����Ŭ�� ã�� �� �������
�� ������ ������ķ� ������ ������ ������ ������ ����̰�
�ߺ��Ǿ Ư���� ó�� ���� �ϳ��� �������� ����� �� �ִ�.
�׷��� �𵨸��� �̷��� �߿��ϴ�.
*/

#include<stdio.h>
#define Max 1001

int N, PD;

//list
typedef struct node{
	int v;
	struct node * next;
}Node;

//dummy�� ������ - graph Ž������ �ǹ̰� ����, delete���� �ʿ�������
Node list[Max], mem[Max*(Max - 1) / 2];
int memidx;

Node * myalloc() {
	return &mem[memidx++];
}

//topological sort
int indegree[Max], check[Max];

int q[Max*(Max - 1) / 2];
int in, out;
int print[Max], pidx;
void tplSort() {

	//1.�ֱ�
	for(int i = 1; i<=N;i++)
		if (check[i] == 0 && indegree[i] == 0) {
			q[in++] = i;
			check[i] = 1;
		}

	while (in != out) {
		//2. ����
		int from = q[out++];
		print[pidx++] = from;
		//3. �ֱ�
		Node * temp = list[from].next;
		while (temp) {
			int to = temp->v;
			indegree[to]--;
			if (check[to] == 0 && indegree[to] == 0) {
				q[in++] = to;
				check[to] = 1;
			}
			temp = temp->next;
		}

	}
}

int cycle(int n) {
	
	if (check[n] == 1)
		return 1;
	check[n] = 1;
	Node * temp = list[n].next;
	int res = 0;
	while (temp) {
		int to = temp->v;
		res = cycle(to);
		temp = temp->next;
	}
	return res;
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
	if (cycle(1))
		printf("0\n");
	else {
		for (int i = 0; i < N; i++)
			check[i] = 0;
		tplSort();
		for (int i = 0; i < pidx; i++)
			printf("%d\n", print[i]);
	}
	return 0;
}


