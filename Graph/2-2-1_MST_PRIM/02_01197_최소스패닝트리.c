#include<stdio.h>
#define MaxV 10001
#define MaxE 100001

/*
1. 그래프 그리기
 1) typedef node
 2) 메모리 할당 list,dummy, mem (양방향일 경우 MaxE*2)
*/

typedef struct node {
	int v;
	int e;
	struct node * next;
}Node;

Node list[MaxV],
	dummy[MaxV],
	mem[MaxE*2];
int memIdx;

Node * alloc() {
	return &mem[memIdx++];
}
/*
2. PriorityQueue
 0) 가중치 없음 : v, 가중치 있음 : v,e(typedef 한 node를 하는게좋음)
 1) insert
 2) PriorityChild
 3) myDelete
*/

Node heap[MaxE*2];
int heapIdx;

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
	int Lchild = nowIdx * 2,
		Rchild = nowIdx * 2 + 1;
	if (Lchild > heapIdx)
		return 0;
	else if (Lchild == heapIdx)
		return Lchild;
	else return heap[Lchild].e < heap[Rchild].e ? Lchild : Rchild;
}

Node myDelete() {
	int nowIdx = 1,
		childIdx;
	Node res = heap[nowIdx],
		last = heap[heapIdx--];

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

/*
3.prim
*/
int check[MaxV];
int prim(int start) {
	int res = 0;
	//1.넣기
	Node s = { start, 0, NULL };
	insert(s);

	while(heapIdx != 0){
		Node  out = myDelete();
		
		if (check[out.v] == 1)continue;

		check[out.v] = 1;
		res += out.e;
		Node * nextNode = list[out.v].next->next;
		while (nextNode) {
			insert(*nextNode);
			nextNode = nextNode->next;
		}

	}
	return res;
}

int V, E;
int main() {
	scanf("%d %d", &V, &E);
	//1. 그래프 초기화
	for (int i = 1; i <= MaxV; i++) {
		list[i].v = i;
		list[i].e = 0;
		list[i].next = &dummy[i];
		dummy[i].e = dummy[i].v = 0;
		dummy[i].next = NULL;
	}
	//2. 그래프 만들기
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