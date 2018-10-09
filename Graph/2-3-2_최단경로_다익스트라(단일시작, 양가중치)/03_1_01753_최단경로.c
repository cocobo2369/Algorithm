#include<stdio.h>
#define MaxV 20001
#define MaxE 300001
#define INF 0x7fffffff
//1. 리스트만들기
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

//2. 힙
typedef struct t {
	int idx;
	int dist;
}T;
T heap[MaxE];
int heapIdx;
int dist[MaxV], check[MaxV];
void insert(T now) {
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

int cmpChild(int nowIdx) {
	int Lchild = nowIdx * 2,
		Rchild = nowIdx * 2 + 1;

	if (Lchild > heapIdx)
		return 0;
	else if (Lchild == heapIdx)
		return Lchild;
	else
		return heap[Lchild].dist < heap[Rchild].dist ? Lchild : Rchild;
}

T myDelete() {
	int nowIdx = 1,
		childIdx;
	T	res = heap[nowIdx],
		last = heap[heapIdx--];

	while (childIdx = cmpChild(nowIdx)) {
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

//3. 다익스트라
//dist의 초기값은 INF
void dijkstra(int start) {

	dist[start] = 0;
	T s = { start, 0 };
	insert(s);

	while (heapIdx) {
		T from = myDelete();

		if (check[from.idx] == 0) {
			check[from.idx] = 1;

			Node * temp = list[from.idx].next->next;
			while (temp) {
				int to = temp->to,
					cost = temp->cost;
				if (dist[to] > dist[from.idx] + cost) {
					dist[to] = dist[from.idx] + cost;
					T t = { to, dist[to] };
					insert(t);
				}
				temp = temp->next;
			}
		}
	}
}

int main() {
	int V, E, K;
	scanf("%d %d %d", &V, &E, &K);
	for (int i = 1; i <= V; i++) {
		dist[i] = INF;
		list[i].to = i;
		list[i].cost = 0;
		list[i].next = &dummy[i];
		dummy[i].to = dummy[i].cost = 0;
		dummy[i].next = NULL;
	}

	while (E--) {
		int from, to, cost;
		scanf("%d %d %d", &from, &to, &cost);

		Node * newNode = alloc();
		newNode->to = to;
		newNode->cost = cost;
		newNode->next = list[from].next->next;
		list[from].next->next = newNode;
	}

	dijkstra(K);

	for (int i = 1; i <= V; i++)
		if (dist[i] == INF)
			printf("INF\n");
		else
			printf("%d\n", dist[i]);
	return 0;
}
		