#include<stdio.h>

#define Max 100010
int N;

//heap
int heapMax[Max], heapMaxIdx;
int heapMin[Max], heapMinIdx;
void insertMax(int num) {
	int nowIdx = ++heapMaxIdx,
		parentIdx = nowIdx / 2;

	while (nowIdx != 1) {
		if (num > heapMax[parentIdx]) {
			heapMax[nowIdx] = heapMax[parentIdx];
			nowIdx = parentIdx;
			parentIdx = nowIdx / 2;
		}
		else
			break;
	}
	heapMax[nowIdx] = num;
}

void insertMin(int num) {
	int nowIdx = ++heapMinIdx,
		parentIdx = nowIdx / 2;

	while (nowIdx != 1) {
		if (num < heapMin[parentIdx]) {
			heapMin[nowIdx] = heapMin[parentIdx];
			nowIdx = parentIdx;
			parentIdx = nowIdx / 2;
		}
		else
			break;
	}
	heapMin[nowIdx] = num;
}

int priorityChildMax(int nowIdx) {
	int leftChild = nowIdx * 2,
		rightChild = nowIdx * 2 + 1;
	if (leftChild > heapMaxIdx)
		return 0;
	else if (leftChild == heapMaxIdx)
		return leftChild;
	else
		return heapMax[leftChild] > heapMax[rightChild] ? leftChild : rightChild;
}

int priorityChildMin(int nowIdx) {
	int leftChild = nowIdx * 2,
		rightChild = nowIdx * 2 + 1;
	if (leftChild > heapMinIdx)
		return 0;
	else if (leftChild == heapMinIdx)
		return leftChild;
	else
		return heapMin[leftChild] < heapMin[rightChild] ? leftChild : rightChild;
}

int myremoveMax() {
	int res = heapMax[1],
		num = heapMax[heapMaxIdx--];

	int nowIdx = 1,
		childIdx;
	while (childIdx = priorityChildMax(nowIdx)) {
		if (num < heapMax[childIdx]) {
			heapMax[nowIdx] = heapMax[childIdx];
			nowIdx = childIdx;
		}
		else
			break;
	}
	heapMax[nowIdx] = num;
	return res;
}

int myremoveMin() {
	int res = heapMin[1],
		num = heapMin[heapMinIdx--];

	int nowIdx = 1,
		childIdx;
	while (childIdx = priorityChildMin(nowIdx)) {
		if (num > heapMin[childIdx]) {
			heapMin[nowIdx] = heapMin[childIdx];
			nowIdx = childIdx;
		}
		else
			break;
	}
	heapMin[nowIdx] = num;
	return res;
}
int main() {
	int num;
	scanf("%d", &N);
	heapMax[heapMaxIdx] = -10000;
	heapMin[heapMinIdx] = 10000;
	while (N--) {
		scanf("%d", &num);
		if (num < heapMax[1]) {
			insertMax(num);
		}
		else if (num == heapMax[1]) {
			insertMin(num);
		}
		else if (num < heapMin[1]) {
			insertMax(num); // 일단 넣어두는 거임
		}
		else if (num == heapMin[1]) {
			insertMax(num);
		}
		else if (heapMin[1] < num) {
			insertMin(num);
		}

		//이제 개수 정리를 하자

		if (heapMaxIdx > heapMinIdx) {
			int num = myremoveMax();
			insertMin(num);
		}
		else if (heapMaxIdx < heapMinIdx) {
			int num = myremoveMin();
			insertMax(num);
		}

		if (heapMaxIdx > heapMinIdx)
			printf("%d\n", heapMax[1]);
		else if (heapMaxIdx < heapMinIdx)
			printf("%d\n", heapMin[1]);
		else
			printf("%d\n", heapMax[1]);
	}
	return 0;
}