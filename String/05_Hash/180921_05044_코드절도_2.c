#include<stdio.h>
#define Max 1000001

int makekey(char *string) {
	unsigned int key = 5381;
	for (int i = 0; string[i]; i++)
		key = ((key << 5) + key + string[i]) % Max;
	return key;
}

typedef struct node {
	char * string;
	struct node * next;
	int check;
}Node;

Node htable[Max];
Node mem[Max];
int memIdx;
char source[Max];
int code[101][10002];
int sourcehash[101][10002];
int N;
int S;
int strcmp(char * src, char * cmp) { //컴페어 이렇게 하면 안됨
	for (int i = 0; src[i]; i++)
		if (src[i] != cmp[i])
			return 0;
	return 1;
}


void quick(int above, int below, int * arr, int *arr2) {
	if (above >= below)
		return;

	int left = above - 1,
		right = below + 1,
		pivot = arr[left + (right - left) / 2];
	int pivot2 = arr2[left + (right - left) / 2];

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


int search(int above, int below, int n, int i, int cnt, int order) {
	if (code[N][i] == -1) {
		return cnt;
	}
	int left = above,
		right = below;
	int key = sourcehash[N][i];
	while (left <= right) {

		int mid = left + (right - left) / 2;

		if (key < sourcehash[n][mid])
			right = mid - 1;
		else if (key > sourcehash[n][mid])
			left = mid + 1;
		else {

			Node * temp = htable[key].next;
			while (temp) {
				if (order < (temp->string - source) && temp->check == 0 && strcmp(temp->string, source + code[N][i])) {
					//temp->check = 1;
					//printf("%d %s\n", i, source+order);
					int ans = search(above, below, n, i + 1, cnt + 1, temp->string - source);
					//temp->check = 0;
					return ans;
				}
				temp = temp->next;
			}
			return cnt;
		}
	}
	return cnt;
}


int main() {


	freopen("code_01.in", "r", stdin);
	setbuf(stdout, NULL);

	scanf("%d", &N);
	//초기화

	for (int i = 0; i <= N; i++)
		for (int j = 0; j < 10002; j++)
			code[i][j] = -1;

	int ii = 0;
	int start = 0;
	for (int i = 0; i<=N; i++) {
		start = 0;
		while (1) {
			scanf(" %[^\n]", source + ii);
			if (strcmp(source + ii, "***END***"))
				break;
			code[i][start] = ii;


			int n = 0;
			for (n = 0; source[ii + n]; n++);

			int p = 0;
			for (p = ii; p < ii + n; p++) {
				if (source[p] == ' ') {
					int j;
					for (j = 0; source[p + 1 + j] == ' '; j++);
					if (j == 0)continue;
					for (int k = p + 1; k <ii + n; k++) {
						source[k] = source[k + j];
						source[k + j] = 0;
					}
					n -= j;
				}
			}
			if (source[ii + n - 1] == ' ') {
				source[ii + n - 1] = 0;
				n--;
			}
			//hash 작업
			int key = makekey(source + ii);
			if (i != N) {
				Node * newNode = &mem[memIdx++];
				newNode->string = source + ii;


				Node * temp = htable[key].next;
				Node * before = &htable[key];
				while (temp) {
					before = temp;
					temp = temp->next;
				}

				before->next = newNode;
				newNode->next = temp;
			}
			sourcehash[i][start++] = key;

			//
			ii += (n + 1);
		}
		if(i != N)
			quick(1, start - 1, sourcehash[i], code[i]);
	}

	int mmax = 0;
	int ans[101];
	for (int n = 0; n < N; n++) {
		int cnt = 0;
		int max = 0;
		int sum = 0;
		int l;
		for (l = 0; code[n][l] != -1; l++);
		for (int i = 0; code[N][i] != -1;) {
			//printf("=%d\n", i);
			cnt = search(1, l-1 , n, i, 0,0);
			//if(cnt)printf("%d ///%d\n",i, cnt);
			max = max > cnt ? max : cnt;
			if (cnt > 0) {
				i += cnt;
			}
			else
				i++;
		}
		ans[n] = max;
		mmax = mmax > max ? mmax : max;
	}

	printf("%d", mmax);
	if (mmax != 0) {
		for (int i = 0; i < N; i++)
			if (mmax == ans[i])
				printf(" %s", source + code[i][0]);
	}
	printf("\n");
	return 0;
}