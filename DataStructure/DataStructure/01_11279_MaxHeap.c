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
	int leftChild = parentIdx * 2; // ���ڽ��� ���� ���⿡ �������ξ���
	int rightChild = parentIdx * 2 + 1;
	if (leftChild > heapIdx)
		return 0;
	else if (leftChild == heapIdx)
		return leftChild;
	else
		return heap[leftChild] >= heap[rightChild] ? leftChild : rightChild;
}
int mydelete() {
	//�⺻������ delete�� heap �ȿ� ������ ���� �� ����������Ѵ�.
	//�׷��� heapIdx ==0 �ΰ��� �ۿ��� ó�����ְų�
	// �ѹ��� �ϰ������ if(heapIdx == 0) return 0; �� ���� ó���ؾ���

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
