#include<stdio.h>
#define MAX 100001

int heap[MAX], heapIdx;

void insert(int n) {
	int nowIdx = ++heapIdx;

	while (nowIdx != 1) {
		int parentIdx = nowIdx / 2;
		if (heap[parentIdx] > n) {
			heap[nowIdx] = heap[parentIdx];
			nowIdx = parentIdx;
		}
		else
			break;
	}
	heap[nowIdx] = n;
	return;
}

int priorityChild(int parentIdx) {
	int leftChild = parentIdx * 2,
		rightChild = parentIdx * 2 + 1;
	if (leftChild > heapIdx)
		return 0;
	else if (leftChild == heapIdx)
		return leftChild;
	else
		return heap[leftChild] < heap[rightChild] ? leftChild : rightChild;
}

int mydelete() {
	int nowIdx = 1, childIdx;
	int out = heap[1],
		last = heap[heapIdx];
	heapIdx--;
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


int main() {
	int N, cmd;
	scanf("%d", &N);
	while (N--) {
		scanf("%d", &cmd);
		if (cmd) insert(cmd);
		else printf("%d\n", heapIdx == 0 ? 0 : mydelete());
	}
	return 0;
}
