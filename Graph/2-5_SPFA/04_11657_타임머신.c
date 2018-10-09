#include<stdio.h>
#define MaxV 501
#define MaxE 600001 //런타임 에러의 원인 사이클이 돌기때문에 q가 maxE보다 더 많이 필요하다 
#define INF 6000*10000
int V, E;
typedef struct node {
	int v;
	int cost;
	struct node * next;
}Node;

Node list[MaxV], dummy[MaxV], mem[MaxE];
int memidx;

Node * myalloc() {
	return &mem[memidx++];
}

int q[MaxE], in, out;

int dist[MaxV], check[MaxV];
int SPFA(int start) {
	for (int i = 1; i <= V; i++)
		dist[i] = INF;

	q[in++] = start;
	check[start] = 1;
	dist[start] = 0;

	while (in != out) {
		int from = q[out++];
		check[from] = 0;

		Node * temp = list[from].next->next;
		while (temp) {
			int to = temp->v,
				cost = temp->cost;
			if (dist[to] > dist[from] + cost) {
				dist[to] = dist[from] + cost;
				if (check[to] == 0) {
					check[to] = 1;
					q[in++] = to;
					if (dist[start] < 0) return -1;
				}
			}
			temp = temp->next;
		}
	}
	return dist[start];
}

int main() {
	scanf("%d %d", &V, &E);

	for (int i = 1; i <= V; i++) {
		dist[i] = INF;
		list[i].v = i;
		list[i].cost = 0;
		list[i].next = &dummy[i];
		dummy[i].cost = dummy[i].v = 0;
		dummy[i].next = NULL;
	}
	for (int e = 1; e <= E; e++) {
		int f, t, c;
		scanf("%d %d %d", &f, &t, &c);
		Node * newNode = myalloc();
		newNode->v = t;
		newNode->cost = c;
		newNode->next = list[f].next->next;
		list[f].next->next = newNode;
	}
	if (SPFA(1) == -1)
		printf("-1\n");
	else
		for (int i = 2; i <= V; i++)
			printf("%d\n", dist[i] == INF ? -1 : dist[i]);
	return 0;
}