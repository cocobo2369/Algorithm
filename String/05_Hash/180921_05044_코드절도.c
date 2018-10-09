#include<stdio.h>
#define Max 1000001
#define Line 10002
#define MaxN 101
typedef struct node {
	char * string;
	struct node * next;
}Node;

Node hashtable[Max];
Node mem[Max];
int memIdx;

char string[Max];

int stringIdx[MaxN][Line];
int stringHash[MaxN][Line];

int N;

int makekey(char * string) {
	unsigned int key = 5381;
	for (int i = 0; string[i]; i++)
		key = ((key << 5) + key + string[i]) % Max;
	return key;
}

int strcmp(char * ahead, char * behind) {

	for (int i = 0; ahead[i] || behind[i]; i++) {
		if (ahead[i] != behind[i])
			return ahead[i] - behind[i];
	}
	return 0;
}


void quick(int above, int below, int * arr, int *arr2) {
	if (above >= below)
		return;

	int left = above - 1,
		right = below + 1,
		pivot = arr[left + (right - left) / 2],
		pivot2 = arr2[left + (right - left) / 2];

	while (left < right) {

		while (arr[++left] < pivot || (arr[left] == pivot && arr2[left] < pivot2));
		while (pivot < arr[--right] || (pivot == arr[right] && pivot2 < arr2[right]));


		if (left >= right)break;

		int temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
		temp = arr2[left];
		arr2[left] = arr2[right];
		arr2[right] = temp;
	}
	quick(above, left - 1, arr, arr2);
	quick(right + 1, below, arr, arr2);
}

void myscanf() {


	scanf("%d", &N);

	for (int i = 0; i <= N; i++)
		for (int j = 0; j < Line; j++)
			stringIdx[i][j] = -1;

	int idx = 0,
		line;

	for (int n = 0; n <= N; n++) {
		line = 0;

		while (1) {

			scanf(" %[^\n]", string + idx);
			//1. END 처리하기
			if (strcmp(string + idx, "***END***") == 0)
				break;


			//2. 공백줄이기
			int len = 0;
			for (len = 0; string[idx + len]; len++);

			int b = 0;
			for (b = idx; b < idx + len; b++) {
				if (string[b] == ' ') {

					int bb = 0;
					for (bb = 0; string[b + 1 + bb] == ' '; bb++);
					if (bb == 0)continue;

					for (int t = b + 1; t < idx + len; t++) {
						string[t] = string[t + bb];
						string[t + bb] = 0;
					}
					len -= bb;
				}
			}

			if (string[idx + len - 1] == ' ') {
				string[idx + len - 1] = 0;
				len -= 1;
			}

			//3. hash - ver. 순서고려
			int key = makekey(string + idx);
			if (n != N) {

				Node * newNode = &mem[memIdx++];
				newNode->string = string + idx;
				newNode->next = NULL;

				Node * before = &hashtable[key];
				for (Node * temp = hashtable[key].next; temp; temp = temp->next)
					before = temp;
				before->next = newNode;
			}

			//4. idx랑 key랑 챙기기
			stringIdx[n][line] = idx;
			stringHash[n][line++] = key;

			//5. idx
			idx += (len + 1);
		}

		if (n != N)
			quick(1, line - 1, stringHash[n], stringIdx[n]);
	}
}


int search(int above, int below, int n, int l, int cnt, int order) {

	if (stringIdx[N][l] == -1)
		return cnt;

	int left = above,
		right = below;
	int key = stringHash[N][l];

	while (left <= right) {

		int mid = left + (right - left) / 2;

		if (key < stringHash[n][mid])
			right = mid - 1;
		else if (stringHash[n][mid] < key)
			left = mid + 1;
		else {
			for (Node * temp = hashtable[key].next; temp; temp = temp->next) {
				if (order < (temp->string - string) && (strcmp(string + stringIdx[N][l], temp->string) == 0))
					return search(above, below, n, l + 1, cnt + 1, temp->string - string);
			}
			return cnt;
		}
	}
	return cnt;
}




int main() {

	myscanf();

	int res = 0;
	int ans[MaxN];

	for (int n = 0; n < N; n++) {

		int cnt = 0,
			max = 0;

		int len;
		for (len = 0; stringIdx[n][len] != -1; len++);

		for (int i = 0; stringIdx[N][i] != -1;) {

			cnt = search(1, len - 1, n, i, 0, 0);
			max = max > cnt ? max : cnt;
			if (cnt) i += cnt;
			else i++;

		}
		ans[n] = max;
		res = res > max ? res : max;
	}

	printf("%d", res);
	if (res != 0)
		for (int n = 0; n < N; n++)
			if (res == ans[n])
				printf(" %s", string + stringIdx[n][0]);
	printf("\n");
	return 0;
}
