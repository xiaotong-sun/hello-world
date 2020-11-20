#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define OVERFLOW -2
#define ERROR -3
#define INFINITY 10000       //���ֵ
#define MAX_VERTEX_NUM 20      //��󶥵����

//--------- ͼ�����飨�ڽӾ��󣩴����ʾ----------
typedef enum {
    DG, DN, UDG, UDN    //{����ͼ��������������ͼ��������}
} GraphKind;

typedef struct ArcCell {
    int adj;            //Ȩֵ
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
    char vexs[MAX_VERTEX_NUM];       //��������
    AdjMatrix arcs;                   //�ڽӾ���
    int vexnum, arcnum;               //ͼ�ĵ�ǰ�������ͻ���
    GraphKind kind;                   //ͼ�������־
} MGraph;

//---------�����ڽӾ����ʾ����������ͼ----------
int LocateVex(char *vexs, char v) {     //ȷ��һ�������λ�ã������ظ�λ��
    for (int i = 0; i < MAX_VERTEX_NUM; ++i) {
        if (v == vexs[i]) {
            return i;
        }
    }
    return 0;
}

int CreatUDG(MGraph *G) {       //��������ͼ
    printf("������ڵ���������ĸ���:");
    scanf("%d %d", &G->vexnum, &G->arcnum);
    getchar();
    printf("�����붥����Ϣ��");
    for (int i = 0; i < G->vexnum; ++i) {       //���춥������
        scanf("%c", &G->vexs[i]);
        getchar();
    }
    for (int i = 0; i < G->vexnum; ++i) {       //��ʼ���ڽ�����
        for (int j = 0; j < G->vexnum; ++j) {
            G->arcs[i][j].adj = INFINITY;
        }
    }
    printf("�����뻡��Ӧ����������v1,v2��Ȩֵw:\n");
    getchar();
    for (int k = 0; k < G->arcnum; ++k) {       //�����ڽӾ���
        char v1, v2;
        int w;                                  // w����Ȩֵ
        //printf("�������%d������Ӧ����������v1,v2��Ȩֵw:\n", k + 1);
        //getchar();
        scanf("%c %c %d", &v1, &v2, &w);
        getchar();
        int i = LocateVex(G->vexs, v1);
        int j = LocateVex(G->vexs, v2);
        G->arcs[i][j].adj = w;
        G->arcs[j][i] = G->arcs[i][j];          //��<v1,v2>�ĶԳƻ�<v2,v1>
    }
    return OK;
}

//---------�����������--------
int visited[MAX_VERTEX_NUM];    //���ʱ�־���飬1Ϊ���ʣ�0Ϊδ����

void VisitFunc(int v, char *vexs) {     //���ʽڵ�
    printf("%c ", vexs[v]);
}

int FirstAdjVex(MGraph *G, int v) {        //ĳ�ڵ�ĵ�һ���ڽӽڵ�
    for (int i = 0; i < G->vexnum; ++i) {
        if (G->arcs[v][i].adj != INFINITY) {
            return i;
        }
    }
}

int NextAdjVex(MGraph *G, int v, int w) {   //ĳ�ڵ��ڽӽڵ����һ���ڵ�
    for (int i = w + 1; i < G->vexnum; ++i) {
        if (G->arcs[v][i].adj != INFINITY) {
            return i;
        }
    }
    return -1;
}

/*
��������������ǻ����ڽӾ�����ص�ʵ�ֵģ�
 ���й̶���ʹ�������1���Ӷ�ʵ�ְ�һ��˳��
 Ѱ��ĳ�ڵ������ڽӵ��Ŀ�ġ�
*/

void DFS(MGraph *G, int v) {                //������������κ���
    visited[v] = 1;
    VisitFunc(v, G->vexs);
    for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w)) {
        if (!visited[w]) {
            DFS(G, w);
        }
    }
}

void DFSTraverse(MGraph *G) {               // �����������������
    for (int v = 0; v < G->vexnum; ++v) {
        visited[v] = 0;
    }
    for (int v = 0; v < G->vexnum; ++v) {
        if (!visited[v]) DFS(G, v);
    }
}

//--------�����������--------------
//---��������Q-----
typedef struct QNode {
    char data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct {
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

int InitQueue(LinkQueue *Q) {
    Q->front = Q->rear = (QueuePtr) malloc(sizeof(QNode));
    if (!Q->front) exit(OVERFLOW);
    Q->front->next = NULL;
    return OK;
}

int EnQueue(LinkQueue *Q, char e) {         //����в���
    QueuePtr p = (QueuePtr) malloc(sizeof(QNode));
    if (!p) exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}

int DeQueue(LinkQueue *Q, char *e) {        //�����в���
    if (Q->front == Q->rear) return ERROR;
    QueuePtr p;
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;
    if (Q->rear == p) {
        Q->rear = Q->front;
    }
    free(p);
    return OK;
}

//-----������ȷǵݹ����-------
void BFSTraverse(MGraph *G) {
    for (int v = 0; v < G->vexnum; ++v) {
        visited[v] = 0;
    }
    LinkQueue Q;
    InitQueue(&Q);
    for (int v = 0; v < G->vexnum; ++v) {
        if (!visited[v]) {
            visited[v] = 1;
            VisitFunc(v, G->vexs);
            EnQueue(&Q, G->vexs[v]);
            while (Q.front != Q.rear) {
                char e;
                DeQueue(&Q, &e);
                int i = LocateVex(G->vexs, e);
                for (int w = FirstAdjVex(G, i); w >= 0; w = NextAdjVex(G, i, w)) {
                    if (!visited[w]) {
                        visited[w] = 1;
                        VisitFunc(w, G->vexs);
                        EnQueue(&Q, G->vexs[w]);
                    }
                }
            }
        }
    }
}

int main() {
    MGraph G;
    CreatUDG(&G);
    printf("�������������\n");
    DFSTraverse(&G);
    printf("\n�����������\n");
    BFSTraverse(&G);
    return 0;
}
