#include<stdio.h>
int N, E;
typedef struct node {
	int node;
	struct node * next;
}Node;

int memidx;
Node mem[500001];
Node list[1001], dummy[1001];

int check[1001];
int cnt;
void dfs(Node * n) {
	if (n == NULL)return;
	if(check[n->node] == 1) return;
	/*
	이거 위험하다.
	n이 null이면 만약 내가 
	if(check[n->node] == 1 || n == NULL) 이라했으면 n->node 는 NULL이라서 오류발생
	종료조건이 2 개인데 분명 조건 순서가 중요한 상황이다.!!!
	if (n == NULL || check[n->node] == 1) {
		return;
	}
	*/
	check[n->node] = 1;
	Node * temp = list[n->node].next->next;
	while (temp != NULL) {
		dfs(temp);
		temp = temp->next;
	}
}
//말그래도 공간을 만드는 역할만 하는 함수
Node * alloc() {
	return &mem[memidx++];
}
int main() {
	scanf("%d %d", &N, &E);

	//1. 초기화 template
	for (int i = 1; i <= 1000; i++) {
		list[i].node = i;
		list[i].next = &dummy[i];
		dummy[i].node = 0;
		dummy[i].next = NULL;
	}

	for (int i = 0; i < E; i++) {
		int from, to;
		scanf("%d %d", &from, &to);

		Node * newNode = alloc();
		newNode->node = to;
		newNode->next = list[from].next->next;
		list[from].next->next = newNode;
		newNode = alloc();
		newNode->node = from;
		newNode->next = list[to].next->next;
		list[to].next->next = newNode;
	}

	for (int i = 1; i <= N; i++) {
		if (check[i] == 1)continue;
		check[i] = 1;
		cnt++;
		Node * temp = list[i].next->next;
		while (temp != NULL) {
			dfs(temp);
			temp = temp->next;
		}
	}

	printf("%d\n", cnt);
	return 0;
}