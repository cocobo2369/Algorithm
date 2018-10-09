#include<stdio.h>
#define MaxV 1001
#define MaxE 100001
#define INF 0x7fffffff
int V, E, S, G;
//1. linkedList : node 정의, list, dummy, mem
typedef struct node {
	int to;
	int cost;
	struct node * next;
}Node;

Node list[MaxV], dummy[MaxV], mem[MaxE];
int memIdx;

Node * alloc() {
	return &mem[memIdx++];
}

typedef struct pair {
	int node;
	int dist;
}Pair;
//1. heap : heap, heapIdx
Pair heap[MaxE];
int heapIdx;
int dist[MaxV], check[MaxV]; //dist 최초값은 INF!
void insert(Pair now) {
	int nowIdx = ++heapIdx;

	while (nowIdx != 1) {
		int parentIdx = nowIdx / 2;
		if (now.dist < heap[parentIdx].dist) {
			heap[nowIdx] = heap[parentIdx];
			nowIdx = parentIdx;
		}
		else
			break;
	}
	heap[nowIdx] = now;
	return;
}

int compareChild(int nowIdx) {
	int Lchild = nowIdx * 2,
		Rchild = nowIdx * 2 + 1;
	if (Lchild > heapIdx)
		return 0;
	else if (Lchild == heapIdx)
		return Lchild;
	else
		return heap[Lchild].dist < heap[Rchild].dist ? Lchild : Rchild;
}

Pair myDelete() {
	int nowIdx = 1, childIdx;
	Pair	res = heap[nowIdx],
			last = heap[heapIdx--];
	while (childIdx = compareChild(nowIdx)) {
		if (last.dist > heap[childIdx].dist) {
			heap[nowIdx] = heap[childIdx];
			nowIdx = childIdx;
		}
		else
			break;
	}
	heap[nowIdx] = last;
	return res;
}



//1.다익스트라 : BFS_heap, dist
//BFS_heap : check
//결국 check, dist 필요
//int dist[MaxV], check[MaxV];

int back[MaxV],stack[MaxV],cnt;
void dijkstra(int start) {
	//1. 최초 한개 넣기, 거리 0
	dist[start] = 0;
	Pair s = { start, dist[start] };
	insert(s);

	while (heapIdx) {
		Pair from = myDelete();
		if (check[from.node] == 0) {
			check[from.node] = 1;

			Node * temp = list[from.node].next->next;
			while (temp) {
				int to = temp->to,
					cost = temp->cost;
				if (dist[to] > dist[from.node] + cost) {
					dist[to] = dist[from.node] + cost;
					back[to] = from.node;
					Pair t = { to, dist[to] };
					insert(t);
				}
				temp = temp->next;
			}
		}
	}
}

int main() {
	scanf("%d %d", &V, &E);

	for (int i = 1; i <= V; i++) {
		dist[i] = INF;
		list[i].to = i;
		list[i].cost = 0;
		list[i].next = &dummy[i];
		dummy[i].cost = dummy[i].to = 0;
		dummy[i].next = NULL;
	}

	while (E--) {
		int from, to, cost;
		scanf("%d %d %d", &from, &to, &cost);
		Node * newNode = alloc();
		newNode->cost = cost;
		newNode->to = to;
		newNode->next = list[from].next->next;
		list[from].next->next = newNode;
	}
	scanf("%d %d", &S, &G);
	dijkstra(S);
	printf("%d\n", dist[G]);
	int temp = G;
	while (temp) {
		stack[++cnt] = temp;
		temp = back[temp];
	}
	printf("%d\n", cnt);
	while (cnt)
		printf("%d ", stack[cnt--]);
	printf("\n");
	return 0;
}