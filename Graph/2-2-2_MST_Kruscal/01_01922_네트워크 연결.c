#include<stdio.h>
#define MaxN 1001
#define MaxE 100001
typedef struct edge {
	int a;
	int b;
	int cost;
}Edge;

Edge mem[MaxE];
int memIdx;

Edge * alloc() {
	return &mem[memIdx++];
}
int N, M;

void quick(int left, int right)
{
	if (left < right) {// left == right 여도 안되는게 pivot = left가됨

		int l, r, pivot;
		l = left - 1;
		r = right + 1;
		pivot = mem[left + (right - left) / 2].cost;
		while (l < r)
		{
			Edge temp;
			while (pivot > mem[++l].cost);
			while (pivot < mem[--r].cost);
			if (l >= r)break;
			temp = mem[l];
			mem[l] = mem[r];
			mem[r] = temp;
		}
		quick(left, l - 1);
		quick(r + 1, right);
	}
}

int root[MaxN];

void make(int n) {
	for (int i = 1; i <= n; i++)
		root[i] = i;
}

int Find(int x) {
	if (root[x] == x) return x;
	else return root[x] = Find(root[x]);
}

void Union(int main, int sub) {
	return root[Find(sub)] = Find(main);
}

int main() {
	scanf("%d %d", &N, &M);

	make(N);
	for(int i =0;i<M;i++) {
		int a, b, cost;
		scanf("%d %d %d", &a, &b, &cost);
		Edge * newEdge = alloc();
		newEdge->a = a;
		newEdge->b = b;
		newEdge->cost = cost;
	}
	quick(0, memIdx - 1);
	int res = 0;
	for (int i = 0; i < M; i++) {
		int a = mem[i].a, b = mem[i].b;
		if (Find(a) != Find(b)) {
			Union(a, b);
			res += mem[i].cost;
		}
	}
	printf("%d\n", res);
	return 0;
}