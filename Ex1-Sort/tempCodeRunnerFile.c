#include <stdio.h>
#define MAX_VERTICE 100
#define MAX_ELEMENTS 100
// khai bao List
typedef struct
{
    int size;
    int data[MAX_ELEMENTS];
} List;

int element_at(List *L, int i)
{
    return L->data[i - 1];
}
void push_back(List *L, int x)
{
    L->data[L->size] = x;
    L->size++;
}
void make_null_list(List *L)
{
    L->size = 0;
}
// khai bao queue
typedef struct
{
    int front, rear;
    int data[MAX_ELEMENTS];
} Queue;

void make_null_queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = -1;
}
// them vao queue
void push(Queue *Q, int x)
{
    Q->rear++;
    Q->data[Q->rear] = x;
}
// lay phan tu trong queue
int top(Queue *Q)
{
    return Q->data[Q->front];
}
// loai bo phan tu dau queue
void pop(Queue *Q)
{
    Q->front++;
}
// kiem tra queue rổng
int empty(Queue *Q)
{
    return Q->front > Q->rear;
}

// khai bao do thi
typedef struct
{
    int n;
    int A[MAX_VERTICE][MAX_VERTICE];
} Graph;
// tao do thi
void init_graph(Graph *G, int n)
{
    G->n = n;
    int i, j;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            G->A[i][j] = 0;
        }
    }
}
// them cung
void add_edge(Graph *G, int u, int v)
{
    G->A[u][v] = 1;
}
List neighbors(Graph *G, int x)
{
    List L;
    make_null_list(&L);
    int i;
    for (i = 1; i <= G->n; i++)
        if (G->A[x][i] == 1)
            push_back(&L, i);
    return L;
}
int mark[MAX_VERTICE];
void breath_first_search(Graph *G, int x) {
    Queue frontier;
    make_null_queue(&frontier);
    int j;
    push(&frontier, x);
    List list1;
    make_null_list(&list1);
    while (!empty(&frontier))
    {
        int x = top(&frontier);
        pop(&frontier);
        if (mark[x] == 1)
            continue;
        push_back(&list1, x);
        mark[x] = 1;
		printf("%d\n", x);
        List list;
        make_null_list(&list);
        list = neighbors(G, x);
        for (j = 1; j <= list.size; j++)
        {
            int y = element_at(&list, j);
            if (mark[y] == 0)
                push(&frontier, y);
        }
    }
}
int main()
{
    Graph G;
    int m, n;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    int x, y, e;

    for (e = 1; e <= m; e++)
    {
        scanf("%d%d", &x, &y);
        add_edge(&G, x, y);
    }
    int u;
    for (u = 1; u <= G.n; u++)
        mark[u] = 0;

    for (u = 1; u <= G.n; u++)
        if (mark[u] == 0)
            breath_first_search(&G, u);

    return 0;
}