//Hash_02866_문자열 잘라내기
#include<stdio.h> 

#define Max 1002
#define C 26


int makekey(char * string) {
	int key = 5381;
	for (int i = 0; string[i]; i++)
		key = ((key << 5) + key + string[i])%Max;
	return key;
}

typedef struct node {
	int num;
	char * string;
	struct node * next;
}Node;

Node htable[Max];
Node mem[Max];
int memIdx;

Node * myalloc() {
	return &mem[memIdx++];
}

int cmp(char * ahead, char * behind) {
	for (int i = 0; ahead[i] || behind[i]; i++)
		if (ahead[i] != behind[i])
			return ahead[i] - behind[i];
	return 0;
}

int check(int key, char * string,int y, int mid) {

	Node * temp = htable[key].next;
	while (temp) {
		if (cmp(string, temp->string) == 0)
			return 1;
		temp = temp->next;
	}

	Node * newNode = myalloc();
	newNode->num = key;
	newNode->string = string;

	temp = htable[key].next;
	Node * before = &htable[key];
	while (temp) {
		before = temp;
		temp = temp->next;
	}
	before->next = newNode;
	newNode->next = temp; //NULL

	return 0; 
}


int Y, X;
char string[Max][Max];

int binarysearch() {

	int left = 0,
		right = X - 1;
	int ans = 0;
	while (left <= right) {
		int mid = left + (right - left) / 2;

		int res = 0;
		memIdx = 0;
		for (int i = 0; i < Max; i++)
			htable[i].next = NULL, htable[i].num = 0, htable[i].string = NULL;
		for (int y = Y - 1; y >= 0; y--) {
			int key = makekey(&string[y][mid]);
			
			if (res = check(key, &string[y][mid],y,mid)) break;
		}
		if (res) {
			right = mid - 1;
		}
		else {
			ans = mid;
			left = mid + 1;
		}
	}
	return ans;
}


int main() {
	scanf("%d %d", &X, &Y);

	for (int x = 0; x < X; x++)
		for (int y = 0; y < Y; y++) {
			scanf(" %c", &string[y][x]);//

		}
	printf("%d\n", binarysearch());
	return 0;
}