#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100	// 최대 크기

typedef struct StackType{    
    char word[MAX_SIZE];
    int top;
} StackType;

void init_stack(StackType* s){ // 스택 초기화 함수
    s->top = -1;
}

int is_empty(StackType* s){ // 공백 상태 검출 함수
    return (s->top == -1);
}

int is_full(StackType* s){ // 포화 상태 검출 함수
    return (s->top == (MAX_SIZE - 1));
}

void push(StackType* s, char word){ // 삽입 함수
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
    }
    else
        s -> word[++(s -> top)] = word;
}

char pop(StackType* s){ // 삭제 함수
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
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

    if ((len % 2) == 0) { //문자열의 길이가 짝수
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
    else { //문자열의 길이가 홀수
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
    printf("[스택을 이용한 회문 판단] 문자열을 입력하시오: ");
    gets(str);
    if (palindrome(str))
        printf("회문입니다\n");
    else
        printf("회문이 아닙니다\n");
}