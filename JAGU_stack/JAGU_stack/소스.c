#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100	// �ִ� ũ��

typedef struct StackType{    
    char word[MAX_SIZE];
    int top;
} StackType;

void init_stack(StackType* s){ // ���� �ʱ�ȭ �Լ�
    s->top = -1;
}

int is_empty(StackType* s){ // ���� ���� ���� �Լ�
    return (s->top == -1);
}

int is_full(StackType* s){ // ��ȭ ���� ���� �Լ�
    return (s->top == (MAX_SIZE - 1));
}

void push(StackType* s, char word){ // ���� �Լ�
    if (is_full(s)) {
        fprintf(stderr, "���� ��ȭ ����\n");
    }
    else
        s -> word[++(s -> top)] = word;
}

char pop(StackType* s){ // ���� �Լ�
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        return 0;
    }
    else
        return s->word[(s->top)--];    
}

int palindrome(char String[]) {
    StackType s;
    init_stack(&s);

    int i;
    int len = 0;

    for (i = 0; String[i] != 0; i++) {
        len++;
    }

    if ((len % 2) == 0) { //���ڿ��� ���̰� ¦��
        for (i = 0; i < (len/2); i++) {
            push(&s, String[i]);
        }

        for (i = (len/2); i < len; i++) {
            if (String[i] != pop(&s))
                return 0;
            else
                return 1;
        }
    }
    else { //���ڿ��� ���̰� Ȧ��
        for (i = 0; i < (len / 2); i++) {
            push(&s, String[i]);
        }

        for (i = (len / 2)+1; i < len; i++) {
            if (String[i] != pop(&s))
                return 0;
            else
                return 1;
        }
    }
}

void main()
{
    char str[MAX_SIZE];
    printf("[������ �̿��� ȸ�� �Ǵ�] ���ڿ��� �Է��Ͻÿ�: ");
    gets(str);
    if (palindrome(str))
        printf("ȸ���Դϴ�\n");
    else
        printf("ȸ���� �ƴմϴ�\n");
}