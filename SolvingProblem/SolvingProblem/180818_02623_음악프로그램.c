//ver1. 인접행렬, 사이클 함수
// 주의할 점
/* 간선의 중복을 허락하는지 허락하지 않는지를 구분하자
간선의 중복을 허락한다면 list에 추가할 때 검색이 필요하다
list에는 동일한 간선이 들어가게 되면 사이클을 찾을 때 곤란해짐
이 문제는 인접행렬로 간선을 만들경우 동일한 간선은 몇번이고
중복되어도 특별한 처리 없이 하나의 간선으로 취급할 수 있다.
그래프 모델링이 이렇게 중요하다.
*/

#include<stdio.h>
#define Max 1001

int N, PD;

//list
typedef struct node{
	int v;
	struct node * next;
}Node;

//dummy를 생략함 - graph 탐색에는 의미가 없음, delete에는 필요하지만
Node list[Max], mem[Max*(Max - 1) / 2];
int memidx;

Node * myalloc() {
	return &mem[memidx++];
}

//topological sort
int indegree[Max], check[Max];

int q[Max*(Max - 1) / 2];
int in, out;
int print[Max], pidx;
void tplSort() {

	//1.넣기
	for(int i = 1; i<=N;i++)
		if (check[i] == 0 && indegree[i] == 0) {
			q[in++] = i;
			check[i] = 1;
		}

	while (in != out) {
		//2. 빼기
		int from = q[out++];
		print[pidx++] = from;
		//3. 넣기
		Node * temp = list[from].next;
		while (temp) {
			int to = temp->v;
			indegree[to]--;
			if (check[to] == 0 && indegree[to] == 0) {
				q[in++] = to;
				check[to] = 1;
			}
			temp = temp->next;
		}

	}
}

int cycle(int n) {
	
	if (check[n] == 1)
		return 1;
	check[n] = 1;
	Node * temp = list[n].next;
	int res = 0;
	while (temp) {
		int to = temp->v;
		res = cycle(to);
		temp = temp->next;
	}
	return res;
}
int main() {
	scanf("%d %d", &N, &PD);

	for (int i = 1; i <= N; i++) {
		list[i].v = i;
		list[i].next = NULL;
	}

	for (int i = 0; i < PD; i++) {
		int C;
		scanf("%d", &C);
		int v[Max];
		for (int c = 0; c < C; c++)
			scanf("%d", &v[c]);
		for (int c = 1; c < C; c++) {
			int from = v[c - 1],
				to = v[c];
			Node * newNode = myalloc();
			newNode->v = to;
			newNode->next = list[from].next;
			list[from].next = newNode;
			indegree[to]++;
		}
	}
	if (cycle(1))
		printf("0\n");
	else {
		for (int i = 0; i < N; i++)
			check[i] = 0;
		tplSort();
		for (int i = 0; i < pidx; i++)
			printf("%d\n", print[i]);
	}
	return 0;
}


