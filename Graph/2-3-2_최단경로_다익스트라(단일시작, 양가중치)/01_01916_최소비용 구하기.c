#include<stdio.h>
#define MaxV 1001
#define MaxE 100001
#define INF 0x7fffffff
int V, E,S,F;
int dist[MaxV];
int heap[MaxE], heapIdx;

typedef struct node {
	int t;
	int e;
	struct node * next;
}Node;

Node list[MaxV], dummy[MaxV], mem[MaxE];
int memIdx;

Node * alloc() {
	return &mem[memIdx++];
}

void insert(int n) {
	int nowIdx = ++heapIdx;

	while (nowIdx != 1) {
		int parentIdx = nowIdx/2;
		if (dist[heap[parentIdx]] > dist[n]) {
			heap[nowIdx] = heap[parentIdx];
			nowIdx = parentIdx;
		}
		else
			break;
	}
	heap[nowIdx] = n;
	return;
}

int priorityChild(int idx) {
	int LChild = idx * 2,
		RChild = idx * 2 + 1;
	if (LChild > heapIdx)
		return 0;
	else if (LChild == heapIdx)
		return LChild;
	else
		return dist[heap[LChild]] < dist[heap[RChild]] ? LChild : RChild;
}

int myDelete() {
	int nowIdx = 1;
	int res = heap[nowIdx],
		last = heap[heapIdx--];
	int childIdx;
	while (childIdx = priorityChild(nowIdx)) {
		if (dist[heap[childIdx]] < dist[last]) {
			heap[nowIdx] = heap[childIdx];
			nowIdx = childIdx;
		}
		else
			break;
	}
	heap[nowIdx] = last;
	return res;
}

int check[MaxV];

int dijkstra(int s) {
	
	dist[s] = 0;
	check[s] = 1;
	insert(s);

	while (heapIdx) {
		int from = myDelete();
		Node * next = list[from].next->next;
		while (next) {
			int to = next->t,
				cost = next->e;
			if (check[to] == 0) {
				if (dist[to] > dist[from] + cost) {
					dist[to] = dist[from] + cost;
					insert(to);
				}
			}
			next = next->next;
		}

	}
}


int main() {
	scanf("%d\n%d", &V, &E);
	for (int i = 1; i <= V; i++) {
		dist[i] = INF;
		list[i].t = i;
		list[i].e = 0;
		list[i].next = &dummy[i];
		dummy[i].e = dummy[i].t = 0;
		dummy[i].next = NULL;
	}
	
	for (int i = 1; i <= E; i++) {
		int f, t, c;
		scanf("%d %d %d", &f, &t, &c);
		Node * newNode = alloc();
		newNode->t = t;
		newNode->e = c;
		newNode->next = list[f].next->next;
		list[f].next->next = newNode;
	}
	scanf("%d %d", &S, &F);
	dijkstra(S);
	printf("%d\n", dist[F]);
	return 0;
}