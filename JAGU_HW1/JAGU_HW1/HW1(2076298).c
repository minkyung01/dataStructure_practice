#include <stdio.h>
#include <stdlib.h>

//데이터 저장을 위한 노드
typedef struct ListNode 
{
	int coef; //계수
	int expon; //지수
	struct ListNode* link;
} ListNode;

//헤더 노드
typedef struct ListType 
{
	int size; 
	ListNode* head;
	ListNode* tail;
} ListType;

//오류 함수
void error(char* message) 
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//리스트 헤더(plist) 생성 함수
ListType* create() 
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0; //size를 0으로 초기화
	plist->head = plist->tail = NULL; //head와 tail을 null pointer로 초기화
	return plist;
}

//노드 추가 함수
void insert_last(ListType* plist, int coef, int expon) 
{
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL) error("메모리 할당 에러");
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL) plist->head = plist->tail = temp;
	else 
	{
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++; //노드 추가 후 size 증가
}

//다항식의 곱셈
void poly_multiply(ListType* plist1, ListType* plist2, ListType* plist3, ListType* plist4) {
	//list3 = list1 * list2
	//list4 = list3에서 동류항 정리를 한 최종 결과식
	ListNode* a = plist1->head; //a는 plist1의 head를 가리키는 포인터
	while (a != NULL) 
	{ //plist1의 끝까지 반복하도록
		ListNode* b = plist2->head; //b는 plist2의 head를 가리키는 포인터
		while (b != NULL) 
		{ //plist2의 끝까지 반복하도록(plist2의 끝에 도달하면 새롭게 b 생성)
			int co_tmp = a->coef * b->coef; 
			int ex_tmp = a->expon + b->expon;
			//plist1과 plist2의 곱셈 결과를 plist3에 임시 저장하기 위한 변수 co_tmp(계수)와 ex_tmp(지수)
			if (co_tmp != 0) insert_last(plist3, co_tmp, ex_tmp); //곱셈 결과로 나온 계수가 0이 아닐 경우, plist3에 항 임시 저장
			b = b->link;
		}
		a = a->link;
	} //plist3에 plist1과 plist2를 곱한 결과식이 저장됨

	//곱셈식의 동류항 정리
	ListNode* c = plist3->head; //c는 plist3의 head를 가리키는 포인터
	int col, exl;//다항식 p3의 lower한 부분에 있는 계수와 지수
	while (c != NULL) 
	{ //plist3의 끝까지 반복하도록
		ListNode* d = c; //d는 c를 가리키는 포인터
		ListNode* pre = plist3->head; //pre는 plist3의 head를 가리키는 포인터
		int coh = c->coef; //다항식 p3의 higher한 부분에 있는 계수
		for (d = d->link; d != NULL; d->link) 
		{ //d는 c가 가리키고 있는 노드에서부터 반복 시작
			if ((c->expon == d->expon)) 
			{ //c의 차수 == d의 차수
				coh += d->coef; //차수가 같을 경우, 계수끼리 덧셈
				col = d->coef; //d가 가리키는 곳의 계수를 col에 저장
				exl = d->expon; //d가 가리키는 곳의 계수를 exl에 저장
				while (1) 
				{ //이미 계산한 항을 plist3에서 삭제하기 위한 코드
					if ((pre->link->coef == col) && (pre->link->expon == exl)) break;
					pre = pre->link;
					//pre가 d가 가리키는 곳 바로 이전을 가리킬 때까지 이동
				}
				pre->link = pre->link->link; //이미 계산한 항 삭제
			}
			d = d->link;
		}
		if (coh != 0) insert_last(plist4, coh, c->expon); 
		//계수끼리 계산한 결과가 0이 아닐 경우, 최종 결과식인 plist4에 항 저장
		c = c->link;
	}
}

//다항식 출력
void poly_print(ListType* plist) 
{
	ListNode* p = plist->head;
	printf("polynomial = ");
	for (; p; p = p->link)
	{
		printf("%dx^%d + ", p->coef, p->expon);
	}
	printf("\n");
}

//거듭제곱
int power(int x, int n) 
{
	if (n == 0) return 1;
	else if ((n % 2) == 0) return power(x * x, n / 2);
	else return x * power(x * x, (n - 1) / 2);
}

//다항식에 값을 대입해 계산
int poly_calc(int x, ListType* plist) 
{
	int val = 0; //계산 결과 0으로 초기화
	ListNode* p = plist->head;
	while (p) 
	{
		val += p->coef * power(x, p->expon); 
		//x를 expon만큼 거듭제곱한 값을 계수에 곱하여 val에 대입/반복을 거듭하면 모든 항의 계산값이 val에 저장됨
		p = p->link;
	}
	return val;
}

int main(void) 
{
	ListType* list1, * list2, * list_tmp, *list_cmp;
	int x;

	list1 = create(); //연결 리스트 헤더 생성
	list2 = create();
	list_tmp = create();
	list_cmp = create();

	insert_last(list1, 3, 4); //다항식 1 생성
	insert_last(list1, 2, 2);
	insert_last(list1, 1, 0);

	insert_last(list2, 8, 5); //다항식 2 생성
	insert_last(list2, -3, 3);
	insert_last(list2, 10, 1);

	poly_print(list1);
	poly_print(list2);
	printf("\n");

	poly_multiply(list1, list2, list_tmp, list_cmp);
	printf("두 다항식의 곱 ==> \n");
	poly_print(list_cmp);
	printf("\n");

	printf("X 값을 입력하세요: ");
	scanf_s("%d", &x);
	printf("\n");

	int result = poly_calc(x, list_cmp);
	printf("정수 X(= %d)에 대한 다항식의 값 ==> %d \n", x, result);

	free(list1); free(list2); free(list_tmp); free(list_cmp);
}