#include<stdio.h>
#define Max 100001
int N;

//Èü
int heap[Max], heapIdx;

//1. insert

void insert(int num) {

	int nowIdx = ++heapIdx,
		parentIdx = nowIdx / 2;

	while (nowIdx != 1) {
		if (num < heap[parentIdx]) {
			heap[nowIdx] = heap[parentIdx];
			nowIdx = parentIdx;
			parentIdx = nowIdx / 2;
		}
		else
			break;
	}
	heap[nowIdx] = num;
}


int priorityChild(int idx) {
	int leftChild = idx * 2,
		rightChild = idx * 2 + 1;

	if (leftChild > heapIdx)
		return 0;
	else if (leftChild == heapIdx)
		return leftChild;
	else
		return heap[leftChild] < heap[rightChild] ? leftChild : rightChild;
}

int myremove() {
	int res = heap[1],
		num = heap[heapIdx--];
	int nowIdx = 1,
		childIdx;
	while (childIdx = priorityChild(nowIdx)) {
		if (num > heap[childIdx]) {
			heap[nowIdx] = heap[childIdx];
			nowIdx = childIdx;
		}
		else 
			break;
	}
	heap[nowIdx] = num;
	return res;
}

int main() {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int num;
		scanf("%d", &num);
		insert(num);
	}
	int res = 0;

	for (int i = 1; i < N; i++) {
		int cmp = myremove() + myremove();
		res += cmp;
		insert(cmp);
	}
	printf("%d\n", res);
	return 0;
}