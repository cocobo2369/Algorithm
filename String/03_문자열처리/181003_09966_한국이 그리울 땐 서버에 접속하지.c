#include<stdio.h>
#define Max 101

int F,N,NN;


int strcmp(char * ahead, char * behind, int L,int t) {
	
	if (t == 0) {
		for (int i = 0; i < L; i++)
			if (ahead[i] != behind[i])
				return ahead[i] - behind[i];
		return 0;
	}
	else {
		for (int i = 0; i < L; i++)
			if (ahead[N-1-i] != behind[NN-1-i])
				return ahead[N - 1 - i] - behind[NN - 1 - i];
		return 0;
	}
}


int main() {
	char file[Max], string[Max];
	scanf("%d %s", &F, string);
	int front, back;
	for (N = 0; string[N]; N++);


	for (front = 0; string[front] != '*'; front++);
	back = N - front - 1;

	for (int i = 0; i < F; i++) {
		
		scanf("%s", file);
		for (NN = 0; file[NN]; NN++);

		
		int cnt = 0;
		if (front <= NN - back) {
			if (strcmp(string, file, front, 0) == 0)
				cnt++;
			if (strcmp(string, file, back, 1) == 0)
				cnt++;
		}
		if (cnt == 2)
			printf("DA\n");
		else
			printf("NE\n");
	}
	return 0;
}