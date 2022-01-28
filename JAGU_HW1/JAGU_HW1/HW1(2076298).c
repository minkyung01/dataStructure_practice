#include <stdio.h>
#include <stdlib.h>

//������ ������ ���� ���
typedef struct ListNode 
{
	int coef; //���
	int expon; //����
	struct ListNode* link;
} ListNode;

//��� ���
typedef struct ListType 
{
	int size; 
	ListNode* head;
	ListNode* tail;
} ListType;

//���� �Լ�
void error(char* message) 
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//����Ʈ ���(plist) ���� �Լ�
ListType* create() 
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0; //size�� 0���� �ʱ�ȭ
	plist->head = plist->tail = NULL; //head�� tail�� null pointer�� �ʱ�ȭ
	return plist;
}

//��� �߰� �Լ�
void insert_last(ListType* plist, int coef, int expon) 
{
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	if (temp == NULL) error("�޸� �Ҵ� ����");
	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;
	if (plist->tail == NULL) plist->head = plist->tail = temp;
	else 
	{
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++; //��� �߰� �� size ����
}

//���׽��� ����
void poly_multiply(ListType* plist1, ListType* plist2, ListType* plist3, ListType* plist4) {
	//list3 = list1 * list2
	//list4 = list3���� ������ ������ �� ���� �����
	ListNode* a = plist1->head; //a�� plist1�� head�� ����Ű�� ������
	while (a != NULL) 
	{ //plist1�� ������ �ݺ��ϵ���
		ListNode* b = plist2->head; //b�� plist2�� head�� ����Ű�� ������
		while (b != NULL) 
		{ //plist2�� ������ �ݺ��ϵ���(plist2�� ���� �����ϸ� ���Ӱ� b ����)
			int co_tmp = a->coef * b->coef; 
			int ex_tmp = a->expon + b->expon;
			//plist1�� plist2�� ���� ����� plist3�� �ӽ� �����ϱ� ���� ���� co_tmp(���)�� ex_tmp(����)
			if (co_tmp != 0) insert_last(plist3, co_tmp, ex_tmp); //���� ����� ���� ����� 0�� �ƴ� ���, plist3�� �� �ӽ� ����
			b = b->link;
		}
		a = a->link;
	} //plist3�� plist1�� plist2�� ���� ������� �����

	//�������� ������ ����
	ListNode* c = plist3->head; //c�� plist3�� head�� ����Ű�� ������
	int col, exl;//���׽� p3�� lower�� �κп� �ִ� ����� ����
	while (c != NULL) 
	{ //plist3�� ������ �ݺ��ϵ���
		ListNode* d = c; //d�� c�� ����Ű�� ������
		ListNode* pre = plist3->head; //pre�� plist3�� head�� ����Ű�� ������
		int coh = c->coef; //���׽� p3�� higher�� �κп� �ִ� ���
		for (d = d->link; d != NULL; d->link) 
		{ //d�� c�� ����Ű�� �ִ� ��忡������ �ݺ� ����
			if ((c->expon == d->expon)) 
			{ //c�� ���� == d�� ����
				coh += d->coef; //������ ���� ���, ������� ����
				col = d->coef; //d�� ����Ű�� ���� ����� col�� ����
				exl = d->expon; //d�� ����Ű�� ���� ����� exl�� ����
				while (1) 
				{ //�̹� ����� ���� plist3���� �����ϱ� ���� �ڵ�
					if ((pre->link->coef == col) && (pre->link->expon == exl)) break;
					pre = pre->link;
					//pre�� d�� ����Ű�� �� �ٷ� ������ ����ų ������ �̵�
				}
				pre->link = pre->link->link; //�̹� ����� �� ����
			}
			d = d->link;
		}
		if (coh != 0) insert_last(plist4, coh, c->expon); 
		//������� ����� ����� 0�� �ƴ� ���, ���� ������� plist4�� �� ����
		c = c->link;
	}
}

//���׽� ���
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

//�ŵ�����
int power(int x, int n) 
{
	if (n == 0) return 1;
	else if ((n % 2) == 0) return power(x * x, n / 2);
	else return x * power(x * x, (n - 1) / 2);
}

//���׽Ŀ� ���� ������ ���
int poly_calc(int x, ListType* plist) 
{
	int val = 0; //��� ��� 0���� �ʱ�ȭ
	ListNode* p = plist->head;
	while (p) 
	{
		val += p->coef * power(x, p->expon); 
		//x�� expon��ŭ �ŵ������� ���� ����� ���Ͽ� val�� ����/�ݺ��� �ŵ��ϸ� ��� ���� ��갪�� val�� �����
		p = p->link;
	}
	return val;
}

int main(void) 
{
	ListType* list1, * list2, * list_tmp, *list_cmp;
	int x;

	list1 = create(); //���� ����Ʈ ��� ����
	list2 = create();
	list_tmp = create();
	list_cmp = create();

	insert_last(list1, 3, 4); //���׽� 1 ����
	insert_last(list1, 2, 2);
	insert_last(list1, 1, 0);

	insert_last(list2, 8, 5); //���׽� 2 ����
	insert_last(list2, -3, 3);
	insert_last(list2, 10, 1);

	poly_print(list1);
	poly_print(list2);
	printf("\n");

	poly_multiply(list1, list2, list_tmp, list_cmp);
	printf("�� ���׽��� �� ==> \n");
	poly_print(list_cmp);
	printf("\n");

	printf("X ���� �Է��ϼ���: ");
	scanf_s("%d", &x);
	printf("\n");

	int result = poly_calc(x, list_cmp);
	printf("���� X(= %d)�� ���� ���׽��� �� ==> %d \n", x, result);

	free(list1); free(list2); free(list_tmp); free(list_cmp);
}