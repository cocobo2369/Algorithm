#include<stdio.h>
#define MaxNode 1001
#define MaxHeap 100001
typedef struct node {
	int v;
	int e;
	struct node * next;
}Node;

Node list[MaxNode],
dummy[MaxNode],
mem[MaxHeap*2];
int memIdx;

Node heap[MaxHeap*2];
int heapIdx;
Node * alloc() {
	return &mem[memIdx++];
}

void insert(Node node) {
	int nowIdx = ++heapIdx;
	while (nowIdx != 1) {
		int parentIdx = nowIdx / 2;
		if (heap[parentIdx].e > node.e) {
			heap[nowIdx] = heap[parentIdx];
			nowIdx = parentIdx;
		}
		else
			break;
	}
	heap[nowIdx] = node;
	return;
}

int priorityChild(int nowIdx) {
	int LChild = nowIdx * 2,
		RChild = nowIdx * 2 + 1;
	if (LChild > heapIdx)
		return 0;
	else if (LChild == heapIdx)
		return LChild;
	else
		return heap[LChild].e < heap[RChild].e ? LChild : RChild;
}

Node  myDelete() {
	int nowIdx = 1;
	Node res = heap[nowIdx],
		last = heap[heapIdx--];
	int childIdx;
	while (childIdx = priorityChild(nowIdx)) {
		if (heap[childIdx].e < last.e) {
			heap[nowIdx] = heap[childIdx];
			nowIdx = childIdx;
		}
		else
			break;
	}
	heap[nowIdx] = last;
	return res;
}

int check[MaxNode];
int prim(int start) {
	int res = 0;
	//1.넣기
	Node  s = { start, 0, NULL };
	insert(s);
	//2.빼기
	while (heapIdx != 0) {
		Node out = myDelete();
		//3. 넣기
		if (check[out.v] == 1)continue;
		check[out.v] = 1;
		res += out.e;
		Node * next = list[out.v].next->next;
		while (next) {
			insert(*next); //이렇게 하면 힙 메모리도 MAx 값의 2배정도 해야함. 양방향 그래프기때문에 그래서 check[v] == 0 일때만 넣으면 MAx로 써도됨
			next = next->next;
		}
	}
	return res;
}

int main() {
	int N, E;
	scanf("%d %d", &N, &E);

	for (int i = 1; i <= N; i++) {
		list[i].v = i;
		list[i].e = 0;
		list[i].next = &dummy[i];
		dummy[i].v = dummy[i].e = 0;
		dummy[i].next = NULL;
	}
	while (E--) {
		int f, t, e;
		scanf("%d %d %d", &f, &t, &e);
		Node * newNode = alloc();
		newNode->v = t;
		newNode->e = e;
		newNode->next = list[f].next->next;
		list[f].next->next = newNode;
		newNode = alloc();
		newNode->v = f;
		newNode->e = e;
		newNode->next = list[t].next->next;
		list[t].next->next = newNode;
	}
	printf("%d\n", prim(1));
	return 0;
}