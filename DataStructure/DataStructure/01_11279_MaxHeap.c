#include<stdio.h>
#define MAX 100001

int heap[MAX], heapIdx = 0;

void insert(int n) {
	int nowIdx = ++heapIdx;

	while (nowIdx != 1) {
		int parentIdx = nowIdx / 2;
		if (heap[parentIdx] < n) {
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
	int leftChild = parentIdx * 2; // 왼자식이 먼저 차기에 기준으로쓴다
	int rightChild = parentIdx * 2 + 1;
	if (leftChild > heapIdx)
		return 0;
	else if (leftChild == heapIdx)
		return leftChild;
	else
		return heap[leftChild] >= heap[rightChild] ? leftChild : rightChild;
}
int mydelete() {
	//기본적으로 delete는 heap 안에 무엇이 있을 때 적용해줘야한다.
	//그래서 heapIdx ==0 인것을 밖에서 처리해주거나
	// 한번에 하고싶으면 if(heapIdx == 0) return 0; 을 따로 처리해야함

	int out = heap[1],
		last = heap[heapIdx];
	heapIdx--;
	int nowIdx = 1;
	int childIdx;

	while (childIdx = priorityChild(nowIdx)) {
		if (last < heap[childIdx]) {
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
