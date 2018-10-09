#include<stdio.h>

#define MaxN 32001
#define MaxE 100001

int N, E;

//그래프 모델링 - 인접리스트
//1)구조체 선언
typedef struct node {
	int n;
	struct node * next;
}Node;

//2) 그래프 만들기
Node list[MaxN], 
	 mem[MaxE];
int memIdx;

Node * myalloc() { //빠른 메모리 할당을 위한 myalloc()
	return &mem[memIdx++];
}

//위상정렬 
//- 넣기 : indegree = 0 일 때, indegree 가 check 역할
//- 빼기 : 연결된 node의 indegree를 감소시키고 indegree = 0 이되면 넣기
int q[MaxE], in, out,
	indegree[MaxN];

void tplSort() {
	//1) 최초 넣기 
	for (int i = 1; i <= N; i++)
		if (indegree[i] == 0)
			q[in++] = i;

	//2) 빼기
	while (in != out) {
		int from = q[out++];
		
		//4)뺐을 때 수행넣기
		printf("%d ", from);
		Node * temp = list[from].next;
		while (temp) { // while문은 항상 next를 미리 적자
			
			int to = temp->n;
			indegree[to]--;

			//3) 넣기
			if (indegree[to] == 0)
				q[in++] = to;

			temp = temp->next;
		}
	}
	return;
}

int main() {
	scanf("%d %d", &N, &E);

	//1) list 초기화
	for (int v = 1; v <= N; v++) {
		list[v].n = v;
		list[v].next = NULL;
	}


	//2) E 입력
	for (int e = 0; e < E; e++) {
		int from, to;
		scanf("%d %d", &from, &to);
		
		Node * newNode = myalloc();
		newNode->n = to;
		newNode->next = list[from].next;
		
		list[from].next = newNode;
		//3) 위상정렬에서 중요!! indegree 증가
		indegree[to]++;
	}

	tplSort();
	printf("\n");
	return 0;
}