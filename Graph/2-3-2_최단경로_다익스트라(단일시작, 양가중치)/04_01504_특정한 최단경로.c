#include<stdio.h>

#define MaxN 801
#define MaxE 200001
#define INF 100000000
int N, E;
//1. list
typedef struct node {
	int to;
	int cost;
	struct node * next;
}Node;

Node list[MaxN], dummy[MaxN], mem[MaxE*2];
int memIdx;

Node * alloc() {
	return &mem[memIdx++];
}

//2. heap
typedef struct pair {
	int v;
	int dist;
}Pair;

Pair heap[MaxE*2];
int heapIdx;

void insert(Pair now) {
	int nowIdx = ++heapIdx;

	while (nowIdx != 1) {
		int pIdx = nowIdx / 2;
		if (now.dist < heap[pIdx].dist) {
			heap[nowIdx] = heap[pIdx];
			nowIdx = pIdx;
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

Pair myDelete() {
	int nowIdx = 1,
		childIdx;
	Pair res = heap[nowIdx],
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

//3. dijkstra
int dist[MaxN], check[MaxN];
int dijkstra(int s, int e) {

	for (int i = 1; i <= N; i++) {
		dist[i] = INF;
		check[i] = 0;
	}
	Pair start = { s, dist[s] = 0 };
	insert(start);

	while (heapIdx) {
		Pair out = myDelete();
		int from = out.v;
		if (from == e) return dist[e];
		if (check[from] == 1)continue;
		check[from] = 1;

		Node * temp = list[from].next->next;
		while (temp) {
			int to = temp->to,
				cost = temp->cost;
			if (dist[to] > dist[from] + cost) {
				dist[to] = dist[from] + cost;

				Pair in = { to, dist[to] };
				insert(in);
			}
			temp = temp->next;
		}
	}
	return dist[e];
}

int main() {
	
	scanf("%d %d", &N, &E);

	for (int i = 1; i <= N; i++) {
		list[i].cost = 0;
		list[i].to = i;
		list[i].next = &dummy[i];
		dummy[i].to = dummy[i].next = 0;
		dummy[i].next = NULL;
	}

	while (E--) {
		int a, b, c;
		scanf("%d %d %d", &a, &b, &c);

		Node * newNode = alloc();
		newNode->to = b;
		newNode->cost = c;
		newNode->next = list[a].next->next;
		list[a].next->next = newNode;
		newNode = alloc();
		newNode->to = a;
		newNode->cost = c;
		newNode->next = list[b].next->next;
		list[b].next->next = newNode;
	}
	int v1, v2, res1 , res2, res;
	scanf("%d %d", &v1, &v2);

	int t = dijkstra(v1, v2);
	res1 = dijkstra(1, v1) + t + dijkstra(v2, N); // 3개 합쳐서 int 범위 안넘게!!!!!!!!!!
	res2 = dijkstra(1, v2) + t + dijkstra(v1, N);
	res = res1 < res2 ? res1 : res2;
	printf("%d\n", res >= INF ? -1 : res);
	return 0;
}