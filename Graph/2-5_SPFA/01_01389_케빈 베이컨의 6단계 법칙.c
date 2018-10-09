#include<stdio.h>
#define MaxV 100
#define MaxE 10001 //양방향이니까
#define INF 5000
typedef struct node {
	int v;
	struct node * next;
}Node;

Node list[MaxV],
dummy[MaxV], mem[MaxE];
int memidx;

Node * myalloc() {
	return &mem[memidx++];
}

int q[MaxE], in, out;

int dist[MaxV], check[MaxV];


int V, M;
int SPFA(int start) {

	in = out = 0;
	for (int i = 1; i <= V; i++)
		dist[i] = INF;

	q[in++] = start;
	check[start] = 1;
	dist[start] = 0;

	//다익스트라 처럼 모든 dist는 시작점을 기준으로 한다.
	while (in != out) {

		int from = q[out++];
		check[from] = 0;

		Node * temp = list[from].next->next;
		while (temp) {
			int to = temp->v;
			if(check[to] == 0)
				if (dist[to] > dist[from] + 1) {
					dist[to] = dist[from] + 1;
					check[to] = 1;
					q[in++] = to;
				}
			temp = temp->next;
		}
	}

	int res = 0;
	for (int i = 1; i <= V; i++) {
		if (dist[i] >= INF)continue;
		else res += dist[i];
	}
	return res;
}

int main() {
	scanf("%d %d", &V, &M);
	int a, b;

	for (int i = 1; i <= V; i++) {
		list[i].next = &dummy[i];
		dummy[i].next = NULL;
		dummy[i].v = 0;
		list[i].v = i;
	}

	while (M--) {
		scanf("%d %d", &a, &b);

		Node * newNode = myalloc();
		newNode->v = b;
		newNode->next = list[a].next->next;
		list[a].next->next = newNode;
		newNode = myalloc();
		newNode->v = a;
		newNode->next = list[b].next->next;
		list[b].next->next = newNode;
	}

	int min = INF, people=1; 
	for (int i = 1; i <= V; i++) {
		int res = SPFA(i);
		if (min > res) {
			min = res;
			people = i;
		}
	}
	printf("%d\n", people);
	return 0;
}