#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef struct LNode {
    int data;
    struct LNode *next;
}LNode, *LinkList;

void CreatList_L(LinkList L, int n) {
    //��λ������n��Ԫ�ص�ֵ����������ͷ���ĵ������Ա�L
    LinkList p;
    L -> next = NULL;
    printf("��������Ԫ��ֵ��\n");
    for (int i = n; i > 0; --i) {
        p = (LinkList) malloc(sizeof(LNode));
        scanf("%d", &(p -> data));
        p->next = L->next;
        L->next = p;
    }
}

void PrintList_L(LinkList L, int n) {
    //˳���ӡ����
    LinkList q = L;
    for (int i = n; i > 0; --i) {
        q = q->next;
        printf("%d ", q->data);
    }
    printf("\n");
}

int ListInsert_L(LinkList L, int i, int e) {
    //�ڵ�i��λ��֮ǰ����Ԫ��e
    LinkList p = L;
    int j = 0;
    while (p && j < i -1) {//Ѱ�ҵ�i-1�����
        p = p->next;
        ++ j;
    }
    if (!p || j > i -1) {
        return ERROR;
    }
    LinkList s = (LinkList) malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

int ListDelete_L(LinkList L, int i, int *e) {
//ɾ����i��Ԫ�أ�����e������ֵ
    LinkList p = L;
    int j = 0;
    while (p->next && j < i - 1) {//Ѱ�ҵ�i����㣬����pָ����ǰ��
        p = p->next;
        j ++;
    }
    if (!p->next && j >= i - 1) {
        return ERROR;
    }
    LinkList q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return OK;
}

int main() {
    int n;
    LinkList L = (LinkList) malloc (sizeof(LNode));
    printf("������Ԫ�صĸ���n:\n");
    scanf("%d", &n);
    CreatList_L(L, n);
    PrintList_L(L, n);
    printf("�ڵ�3��λ��֮ǰ����23\n");
    ListInsert_L(L, 3, 23);
    PrintList_L(L, n + 1);
    printf("ɾ���ڶ���Ԫ�أ��������ֵ\n");
    int *e;
    ListDelete_L(L, 2, e);
    printf("%d\n", *e);
}
