#include<stdio.h>
#define MaxL 21
#define MaxF 100001
#define prime 5381

unsigned int hash(char * name) {
	int key = prime;
	for (int i = 0; name[i]; i++)
		key = (((key << 5) + key) + name[i]) % MaxF;
	return key;
}

typedef struct node {
	char name[MaxL];
	struct node * next;
}Node;

Node htable[MaxF];
Node mem[MaxF];
int memIdx;


int T, F;
int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &F);

		//ÃÊ±âÈ­
		memIdx = 0;
		for (int f = 0; f < F; f++) {
			char string[MaxL];
			int key[2];
			for (int i = 0; i < 2; i++) {
				scanf("%s", string);
				key[i] = hash(string);

				for (int j = 0; string[j]; j++)
					mem[memIdx].name[j] = string[j];
				mem[memIdx].next = htable[key[i]].next;
				htable[key[i]].next = &mem[memIdx];
				memIdx++;
			}
		}






	}
}