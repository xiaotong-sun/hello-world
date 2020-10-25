#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define STACK_INIT_SIZE 100

//�������Ķ���������ṹ
typedef struct BiTNode{
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//ջ�Ĵ���ṹ
typedef struct {
    BiTree base;
    BiTree top;
    int stacksize;
} SqStack;

//���ô���ֹ�����������й���������
int CreateBiTree(BiTree *T) {  //���ö���ָ�봫�Σ���Ϊ�������������Ҫ�ı�һ��ָ���ָ��������ö���ָ����൱��һ��ָ���ֵ���ݣ����ܸı�ָ���ָ��
    char ch;
    scanf("%c", &ch);
    if (ch == ' ') *T = NULL;
    else {
        if (!*T) exit(OVERFLOW);
        (*T)->data = ch;
        (*T)->lchild = (BiTree)malloc(sizeof(BiTNode));
        if (!(*T)->lchild) exit(OVERFLOW);
        (*T)->rchild = (BiTree)malloc(sizeof(BiTNode));
        if (!(*T)->rchild) exit(OVERFLOW);
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
        }
    return OK;
}

int PrintElement(char e) {
    printf("%c ", e);
    return OK;
}

//��ʼ��һ����ջ
int InitStack(SqStack *S) {
    S->base = (BiTree)malloc(STACK_INIT_SIZE * sizeof(BiTNode));
    if (!S->base) exit(OVERFLOW);
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

//�ж�һ��ջ�Ƿ�Ϊ��ջ
int StackEmpty(SqStack S) {
    if (S.base == S.top) return 1;
    return 0;
}

//������ѹ��ջ��
int Push(SqStack *S, BiTree p) {
    if (S->top - S->base >= S->stacksize) {
        S->base = (BiTree)realloc(S->base, (S->stacksize + 50) * sizeof(BiTNode));
        if (!S->base) exit(OVERFLOW);
        S->top = S->base + S->stacksize;
        S->stacksize += 50;
    }
    * S->top ++ = *p;
    return OK;
}

//ջ�����ݳ�ջ
int Pop(SqStack *S, BiTree *p) {
    if (S->top== S->base) return ERROR;
    *p = --(S->top);
    return OK;
}

//���ǵݹ飩���������
int InOrderTraverse(BiTree T) {
    SqStack S;
    BiTree p = T;
    BiTree *p1 = &p;
    InitStack(&S);
    while (p || !StackEmpty(S)) {
        if (p) {
            Push(&S,p);
            p = p->lchild;
        } else {
            Pop(&S,p1);
            if (!PrintElement(p->data)) return ERROR;
            p = p->rchild;
        }
    }
    return OK;
}

//���ݹ飩���������
int PreOrder(BiTree T) {
    if (T) {
        PrintElement(T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
    return OK;
}

//���ݹ飩�ĺ������
int PostOrder(BiTree T) {
    if (T) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        PrintElement(T->data);
    }
    return OK;
}

int InOrder(BiTree T) {
    if (T) {
        InOrder(T->lchild);
        PrintElement(T->data);
        InOrder(T->rchild);
    }
    return OK;
}

int main() {
    BiTree T = (BiTree)malloc(sizeof(BiTNode));
    BiTree *T1 = &T;
    CreateBiTree(T1);
    printf("�ǵݹ������������Ϊ��\n");
    InOrderTraverse(T);
    printf("\n�ݹ������������Ϊ��\n");
    PreOrder(T);
    printf("\n�ݹ�ĺ���������Ϊ��\n");
    PostOrder(T);
    printf("\n�ݹ������������Ϊ��\n");
    InOrder(T);
    return 0;
}
