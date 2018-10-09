#include<stdio.h>

#define Max 1001
int Y, X;

typedef struct node {
	char * string;
	struct node * next;
}Node;

Node hash[Max*Max];
Node mem[Max*Max];
int memIdx;

char string[Max][Max];

unsigned int makekey(char * data) {
	unsigned int key = 5381;

	for (int i = 0; data[i]; i++)
		key = (((key << 5) + key) + data[i]) % (Max*Max);
	return key;
}

//글자 길이가 다를 수 있다.
int strcmp(char *  main, char * sub) {
	int i;
	for (i = 0; main[i]; i++)
		if (main[i] != sub[i])
			return 0;
	if (sub[i] != 0) return 0;
	return 1;
}

int find(int x) {


	for (int y = 0; y < Y; y++) {
		int key = (int)makekey(&string[y][x]);

		if (hash[key].next != NULL) {
			Node * temp = hash[key].next;
			while (temp) {
				if (strcmp(&string[y][x], temp->string))
					return 1;
				temp = temp->next;
			}
		}

		Node * newNode = &mem[memIdx++];
		newNode->string = &string[y][x];
		newNode->next = hash[key].next;
		hash[key].next = newNode;
	}

	return 0;
}
int maketable() {
	int trace = 0;
	int start = 0, end = X - 1;
	int mid;
	int ans;
	while (start <= end) {
		ans = 0;
		mid = start + (end - start) / 2;

		if (ans = find(mid)) 
			end = mid - 1;
		else 
			start = mid + 1;
		trace = ans;
	}

	return trace == 1 ? mid-1 : mid;
}

int main() {
	scanf("%d %d", &X, &Y);
	for (int x = 0; x < X; x++)
		for (int y = 0; y < Y; y++)
			scanf("\n%c", &string[y][x]);

	printf("%d\n", maketable());
	return 0;
}