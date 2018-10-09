#include<stdio.h>
#define MAX 32010
int N, E;

typedef struct node {
	int num;
	struct node * next;
}Node ;

Node list[MAX],
	dummy[MAX],
	mem[100010];
int memIdx;

Node * alloc() {
	return &mem[memIdx++];
}

int heap[100001], heapIdx;
int indegree[MAX];

void insert(int n) {
	int nowIdx = ++heapIdx;

	while (nowIdx != 1) {
		int parentIdx = nowIdx / 2;
		if (n < heap[parentIdx]) {
			heap[nowIdx] = heap[parentIdx];
			nowIdx = parentIdx;
		}
		else
			break;
	}
	heap[nowIdx] = n;
}

int priorityChild(int nowIdx) {
	int leftChild = nowIdx * 2,
		rightChild = nowIdx * 2 + 1;
	if (leftChild > heapIdx)
		return 0;
	else if (leftChild == heapIdx)
		return leftChild;
	else
		return heap[leftChild] < heap[rightChild] ? leftChild : rightChild;
}

int mydelete() {
	int out = heap[1],
		last = heap[heapIdx--];
	int nowIdx = 1,
		childIdx;

	while (childIdx = priorityChild(nowIdx)) {
		if (heap[childIdx] < last) {
			heap[nowIdx] = heap[childIdx];
			nowIdx = childIdx;
		}
		else
			break;
	}
	heap[nowIdx] = last;
	return out;
}

void topologicalSort() {
	for (int n = 1; n <= N; n++) {
		if (indegree[n] == 0)
			insert(n);
	}

	while (heapIdx != 0) {
		int out = mydelete();
		printf("%d ", out);
		Node * temp = list[out].next->next;
		while (temp) {
			int num = temp->num;
			indegree[num]--;
			if (indegree[num] == 0)
				insert(num);
			temp = temp->next; //자꾸 놓침
		}
	}
}

int main() {
	scanf("%d %d", &N, &E);

	for (int i = 1; i <= N; i++) {
		list[i].num = i;
		list[i].next = &dummy[i];
		dummy[i].num = 0;
		dummy[i].next = NULL;
	}

	while(E--){
		int from, to;
		scanf("%d %d", &from, &to);
		indegree[to]++;
		Node * newNode = (Node *)malloc(sizeof(Node*)*(N + 1));
		newNode->num = to;
		newNode->next = list[from].next->next;
		list[from].next->next = newNode;
	}
	topologicalSort();
	printf("\n");
	return 0;
}