#include<stdio.h>
#define Max 3001
#define C 26
#define mod  1000000007
int N;
typedef struct child {
	int num;
	int idx;
	struct child * next;
}Child;

typedef struct node {
	char valid;
	int cnt;
	Child * child;
}Node;

Node trie[Max*Max];
int trieIdx;
Child child[Max*Max*2]; // trie�� 2���� ������ trie ������� �� ������ ������ �ϳ�������
//�׷��� �Ǹ� trie ������ �ܾ��� ö�ڰ�����ŭ ��������� ���������� ö�ڰ����� ������ �� �ι���
int childIdx;

Child * myalloc() {
	child[childIdx].idx = -1;
	child[childIdx].num = -1;
	return &child[childIdx++];
}

int init() {
	trie[trieIdx].valid = 0;
	trie[trieIdx].cnt = 0;
	trie[trieIdx].child = myalloc();
	//3.�Ǽ�
	return trieIdx++;
}

void add(int now, char * string, int sLen, int sIdx) {
	if (sLen == sIdx) {
		int last = init();
		trie[now].cnt++;
		Child * newChild = myalloc();
		newChild->num = C;
		newChild->idx = last;
		newChild->next = trie[now].child->next;
		trie[now].child->next = newChild;

		trie[last].cnt++;
		trie[last].valid = 1;
		return;
	}

	int c = string[sIdx] - 'A';

	Child * next = trie[now].child;
	int nextidx = 0;
	int is = 1;
	
	while (next) {
		if (next->num == c) {
			is = 0;
			nextidx = next->idx;
			break;
		}
		next = next->next;
	}

	if (is) {
		int next = init();
		trie[now].cnt++;
		Child *newChild = myalloc();
		newChild->num = c;
		newChild->idx = next;
		newChild->next = trie[now].child->next;
		trie[now].child->next = newChild;
		nextidx = next;
	}
	add(nextidx, string, sLen, sIdx + 1);
}

//ū�� �����ؾ��Ѵ�.

long long factorial(int n) {
	long long res = 1;
	for (int i = 1; i <= n; i++)
		res = (long long)((res%mod) * (i%mod))%mod;
	return res;
}

long long find(int now) {
	//2. �Ǽ� �׷��� ���ѷ���
	if (trie[now].valid == 1)
		return 1;
	long long res = factorial(trie[now].cnt);


	Child * next = trie[now].child;
	while (next) {
		res = (long long)((res%mod) * (find(next->idx) % mod))%mod;
		next = next->next;
	}
	return res;
}
int main() {
	scanf("%d\n", &N);

	int root = init();

	for (int i = 0; i < N; i++) {
		char string[Max];
		scanf("%s", string);
		int len;
		for (len = 0; string[len]; len++);
		add(root, string, len, 0);
	}
	printf("%lld\n", find(root));
	return 0;
}