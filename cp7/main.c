#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>


//На основе списка
typedef struct {
	int index;
	struct Item* next;
	double value;
} Item;

Item* init(int number) {
	Item* head = malloc(sizeof(Item));
	head->next = NULL;
	head->value = 0;
	head->index = 1;
	Item* cur = head;
	for (int i = 1; i < number; i++) {
		Item* tmp = malloc(sizeof(Item));
		tmp->next = NULL;
		tmp->value = 0;
		tmp->index = i + 1;

		cur->next = tmp;
		cur = cur->next;
	}
	return head;
}

Item* getLast(Item* head) {
	if (head == NULL) return NULL;
	Item* g = head;
	while (g->next != NULL) {
		g = g->next;
	}
	return g;
}

Item* Add(Item* head, double val) {
	if (head == NULL) {
		Item* tmp = malloc(sizeof(Item));
		tmp->next = NULL;
		tmp->value = val;
		tmp->index = 1;
		return tmp;
	}

	Item* last = getLast(head);
	Item* tmp = malloc(sizeof(Item));
	tmp->next = NULL;
	tmp->value = val;
	tmp->index = last->index + 1;
	last->next = tmp;
	return head;
}

Item* getByIndex(Item* head, int ind) {
	if (head == NULL) return NULL;
	Item* g = head;
	while (g->index != ind && g->next != NULL)
		g = g->next;
	return g;
}
int getSize(Item* head) {
	Item* last = getLast(head);
	if (last == NULL) return 0;
	return last->index;
}

void printItems(Item* head) {
	Item* g = head;
	while (g != NULL) {
		printf("%lf ", g->value);
		g = g->next;
	}
	printf("\n");
}


typedef struct {
	Item* M;
	Item* A;
	int m, n;
	double MX;
} Matrix;

Matrix* initi(int Mm, int Nn) {
	Matrix* ans = malloc(sizeof(Matrix));
	ans->m = Mm;
	ans->n = Nn;
	ans->M = init(Mm);
	ans->A = NULL;
	return ans;
}

//1-индексация хранения!!!
Matrix* readMatrix(FILE* in) {
	double curVal = 0;
	int m, n;
	int curRow = 0;
	fscanf(in, "%d %d\n", &m, &n);
	Matrix* ans = initi(m, n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (fscanf(in, "%lf", &curVal) == 1) {
				if (curVal == 0)
					continue;
				int realI = i + 1;
				int realJ = j + 1;
				if (curRow == 0) {
					curRow = realI;
					Item* Mind = getByIndex(ans->M, realI);
					Mind->value = 1;
				}
				//Переход на новую строку
				else if (curRow != realI) {
					//Записали - как символ окончания строки
					ans->A = Add(ans->A, 0);
					curRow = realI;

					Item* Mind = getByIndex(ans->M, realI);
					//+1? поскольку не хотим указывать на 0
					Mind->value = getSize(ans->A) + 1;
				}
				ans->A = Add(ans->A, realJ);
				ans->MX = (abs(curVal)) > (ans->MX) ? (abs(curVal)) : (ans->MX);
				ans->A = Add(ans->A, curVal);
			}
		}
		fscanf(in, "\n");
	}
	//Последний 0 нужно записать в Item
	ans->A = Add(ans->A, 0);
	return ans;
}
double EPS = 1e-6;
//1-индексация!!!
void printMatrix(Matrix* A) {
	printf("Human representation:\n");
	for (int i = 1; i <= A->m; i++) {
		Item* mmm = getByIndex(A->M, i);
		if (mmm->value == 0) {
			for (int j = 1; j <= A->n; j++) {
				printf("%d\t", 0);
			}
		}
		else {
			Item* ColumnsAndValues = getByIndex(A->A, mmm->value);
			for (int j = 1; j <= A->n; j++) {
				if (ColumnsAndValues->value != 0 && j == ColumnsAndValues->value) {
					ColumnsAndValues = ColumnsAndValues->next;
					printf("%.2lf\t", ColumnsAndValues->value);
					ColumnsAndValues = ColumnsAndValues->next;
				}
				else {
					printf("%d\t", 0);
				}
			}
		}
		printf("\n");
	}
	printf("Internal Represenation:\n");
	printf("M:\n");
	printItems(A->M);
	printf("A:\n");
	printItems(A->A);
}

Item* calcLine(Item* headLine, double val) {
	while (headLine->value != 0) {
		Item* nxt = headLine->next;
		nxt->value = nxt->value / val;
		headLine = nxt->next;
	}
	return headLine;
}
 Matrix* task(Matrix *A) {
	 double modMax = A->MX;
	 Item* headLine = A->A;
	 Item* curIndex = headLine;
	 while (curIndex != NULL) {
		 while (curIndex->value != 0) {
			 Item* nxt = curIndex->next;
			 double val = nxt->value;
			 if (abs(val) == modMax) {
				 headLine = calcLine(headLine, val);
				 //останавливается на 0
			 }
			 curIndex = nxt->next;
		 }
		 headLine = headLine->next;
		 curIndex = curIndex->next;
	 }
	 return A;
 }

int main() {
	Matrix* A;
	char path[256];
	printf("Enter file input: ");
	scanf("%s", path);
	FILE* input = fopen(path, "r");
	if (input == NULL) {
		printf("Error: file not found\n");
		return 0;
	}
	A = readMatrix(input);
	fclose(input);
	int g = 1;
	while (g) {
		printf("1) Print A\n");
		printf("2) Task\n");
		printf("3) Exit\n");
		int command;
		scanf("%d", &command);
		switch (command) {
		case 1: {
			printMatrix(A);
			break;
		}
		case 2: {
			A = task(A);
			break;
		}
		case 3: {
			g = 0;
			break;
		}
		default: {
			printf("Error: unknown command");
			break;
		}
		}
	}
	return 0;
}
