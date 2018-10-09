#include<stdio.h>
#define MaxE 200001
int K, V, E;

typedef struct node {
	int num;
	struct node * next;
}Node;

Node dummy[20001];
Node mem[MaxE];
int memIdx; //
Node * alloc() {
	return &mem[memIdx++];
}

Node list[20001];

int q[MaxE];
int in, out; //
int check[20001]; //

int bfs(int s) {
	int res = 0;
	check[s] = 1;
	q[in++] = s;
	while (in != out) {
		int now = q[out++];
		Node * nextNode = list[now].next->next;
		while (nextNode) {
			int nextNum = nextNode->num;
			if (check[nextNum] == 0) {
				check[nextNum] = check[now] * -1;
				q[in++] = nextNum;
			}
			else if (check[nextNum] == check[now])
				res = 1;
			nextNode = nextNode->next;
		}
	}
	return res;
}
int main() {
	scanf("%d", &K);
	for (int i = 1; i <= 20001; i++) {
		list[i].num = i;
		dummy[i].num = 0;
		dummy[i].next = NULL;
		list[i].next = &dummy[i];
	}
	while (K--) {
		int res = 0;
		scanf("%d %d", &V, &E);

		memIdx = in = out = 0;
		for (int i = 1; i <= V; i++) {
			check[i] = 0;
			list[i].next->next = NULL;
		}
		for (int e = 1; e <= E; e++) {
			int from, to;
			scanf("%d %d", &from, &to);
			Node * newNode = alloc();
			newNode->num = to;
			newNode->next = list[from].next->next;
			list[from].next->next = newNode;
			newNode = alloc();
			newNode->num = from;
			newNode->next = list[to].next->next;
			list[to].next->next = newNode;
		}

		for (int v = 1; v <= V; v++) {
			if (check[v] == 0) {
				res = bfs(v);
				if (res)break;
			}
		}
		if (res)
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}