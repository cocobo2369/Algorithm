#include<stdio.h>
#define MaxV 10001
#define MaxE 100001

int V, E;
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
void quick(int left, int right) {
	if (left < right) {
		int l = left - 1,
			r = right + 1,
			pivot = mem[l + (r - l) / 2].cost;
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

int root[MaxV];
void make(int n) {
	for (int i = 1; i <= n; i++)
		root[i] = i;
}

int Find(int x) {
	if (root[x] == x) return root[x];
	else return root[x] = Find(root[x]);
}

void Union(int main, int sub) {
	return root[Find(sub)] = Find(main);
}

int main() {
	scanf("%d %d", &V, &E);
	make(V);
	for (int i = 0; i < E; i++) {
		int a, b, cost;
		scanf("%d %d %d", &a, &b, &cost);
		Edge * newEdge = alloc();
		newEdge->a = a;
		newEdge->b = b;
		newEdge->cost = cost;
	}
	quick(0, memIdx - 1);

	int res = 0;
	for (int i = 0; i < E; i++) {
		int a = Find(mem[i].a),
			b = Find(mem[i].b);
		if (a != b) {
			Union(a, b);
			res += mem[i].cost;
		}
	}
	printf("%d\n", res);
	return 0;
}