#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 00
#define INFEASIBLE -1
#define OVERFLOW -2

typedef struct {
    int *base;
    int *top;
    int stacksize;
}SqStack;

int InitStack(SqStack *S) {
    //����һ����ջ
    S->base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
    if (!S->base) exit(OVERFLOW);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

int Push(SqStack *S, int e) {
    //����Ԫ��eΪ�µ�ջ��Ԫ��
    if(S->top - S->base >= S->stacksize) {//ջ����׷�Ӵ洢�ռ�
        S->base = (int *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(int));
        if (!S->base) exit(OVERFLOW);
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *(S->top ++) = e;
    return OK;
}

int Pop(SqStack *S, int *e) {
    //��ջ���գ�ɾ��ջ��Ԫ�أ���e������ֵ��������ok�����򷵻�error��
    if(S->top == S->base) {//�ж�ջ��
        return ERROR;
    }
    *e = * (-- S->top);
    return OK;
}

int main() {
    SqStack S;
    InitStack(&S);
    int a = 0, b = 0;
    printf("������һ��ʮ��������\n");
    scanf("%d", &a);
    while (a) {
        b = a % 8;
        Push(&S, b);
        a /= 8;
    }
    printf("ת��Ϊ8������Ϊ��\n");
    while (S.top != S.base){
        int *e;
        Pop(&S, e);
        printf("%d", *e);
    }
    return 0;
}