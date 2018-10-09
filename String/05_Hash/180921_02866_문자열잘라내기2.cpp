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


void maketable() {

	
	for (int x = 0; x < X; x++) {
		for (int y = 0; y < Y; y++) {
			int key = (int)makekey(&string[y][x]);

			if (hash[key].next != NULL) {
				Node * temp = hash[key].next;
				while (temp) {
					if (strcmp(&string[y][x], temp->string))
						return;
					temp = temp->next;
				}
			}

			Node * newNode = &mem[memIdx++];
			newNode->string = &string[y][x];
			newNode->next = hash[key].next;
			hash[key].next = newNode;
		}

	}

}


int main() {
	scanf("%d %d", &X, &Y);
	for (int x = 0; x < X; x++)
		for (int y = 0; y < Y; y++)
			scanf("\n%c", &string[y][x]);

	maketable();
	printf("%d\n", cnt);
	return 0;
}