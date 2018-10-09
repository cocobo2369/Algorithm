#include<stdio.h>
#define MaxE 200001
int K, V, E;

typedef struct node {
	int num;
	struct node * next;
}Node;

Node dummy[20001];
Node mem[MaxE*2];
int memIdx; //
Node * alloc() {
	return &mem[memIdx++];
}

Node list[20001];

int check[20001]; //

int dfs(int from, int c) {
	check[from] = c;

	Node * next = list[from].next->next;
	while (next) {
		if (check[next->num] == 0) {
			if (dfs(next->num, c*-1))
				return 1;
		}
		else if (check[next->num] == check[from])
			return 1;
		next = next->next;
	}
	return 0;
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
		
		scanf("%d %d", &V, &E);

		memIdx = 0;
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
		int res = 0;
		for (int v = 1; v <= V; v++) {
			if (check[v] == 0)
				if (dfs(v, 1))
					res = 1;
					
		}
		printf("%s\n", res == 1 ? "NO" : "YES");
	}
	return 0;
}