#include<stdio.h>
#define Max 10003
#define odd 5381
typedef struct node {
	char num[11];
	struct node * next;
}Node;

Node hashtable[Max+1];
Node mem[Max+1];
int memIdx;

char save[10001][11];
int saveIdx;

Node * myalloc() {
	return &mem[memIdx++];
}
unsigned int hash(char * num) {

	unsigned int key = odd;
	for (int i = 0; num[i]; i++) {
		key = (((key<<5) + key)+num[i]) % Max;
	}
	return key%Max;
}

int T;
int cmp(char *ori, char *check) {
	int i;
	for (i = 0; ori[i]; i++)
		if (ori[i] != check[i])return 0;
	return 1;
}
int main() {
	scanf("%d", &T);
	int N;
	while (T--) {
		scanf("%d", &N);
		int ans = saveIdx = memIdx = 0;
		for (int n = 0; n < N; n++) {
			char num[11];
			scanf("%s", num);

			int  i;
			for (i = 0; num[i]; i++)
				save[saveIdx][i] = num[i];
			save[saveIdx][i] = 0;
			saveIdx++;

			int key = (int)hash(num);

			Node * newNode = myalloc();
			
			for (i = 0; num[i]; i++)
				newNode->num[i] = num[i];
			newNode->num[i] = 0;
			newNode->next = hashtable[key].next;
			hashtable[key].next = newNode;
		}

		for (int l = 0; l < saveIdx; l++) {
			char temp[10];
			for (int i = 0; save[l][i]; i++) {
				temp[i] = save[l][i];
				temp[i + 1] = 0;
				int key = (int)hash(temp);

				Node * node = hashtable[key].next;
				while (node) {
					if (cmp(node->num, temp)) {
						if(cmp(save[l],temp) == 0)
							ans = 1;
						break;
					}
					node = node->next;
				}
				if (ans)break;
			}
			if (ans)break;
		}

		printf("%s\n", ans ? "NO" : "YES");

		for (int i = 0; i < Max; i++)
			hashtable[i].next = NULL;
	}
	return 0;
}