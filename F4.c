#include <stdio.h>
#include <stdlib.h>

// node
typedef struct node {
    int val;
    struct node *next;
} node;

// queue
typedef struct {
    node *start;
    node *end;
    int size;
} queue;

// criando a fila
void create(queue *Q) {
    Q->start = NULL;
    Q->end = NULL;
    Q->size = 0;
}

// adicionar à fila
void enqueue(queue *Q, int x) {
    node *new = (node *)malloc(sizeof(node));
    new->val = x;
    new->next = NULL;

    // checando se a fila está vazia
    if (Q->start == NULL) {
        Q->start = new;
        Q->end = new;

    } else {
        Q->end->next = new; // definindo new como o poximo elemento da fila
        Q->end = new;       // definindo new como o novo end
    }

    Q->size++;
}

int dequeue(queue *Q) {
    if (Q->start == NULL) return -1;

    node *temp = Q->start;
    int res = temp->val;

    Q->start = Q->start->next;

    // se fosse o ultimo elemento da fila torna end nulo
    if (Q->start == NULL) {
        Q->end = NULL;
    }
    Q->size--;

    free(temp);

    return res;
}
int main () {
    queue *P = (queue *)malloc(sizeof(queue));
    create(P);
    int n, k;
    scanf(" %d %d", &n, &k);
    int N = n;
    while (N--) {
        long long int x;
        scanf(" %lld", &x);
        enqueue(P, x);
    }
    node *i = P->start;
    node *j = P->start;
    long long int S = 0;
    n -= k;
    while (k-- && i != NULL) {
        S += i->val;
        printf("%lld\n", S);
        i = i->next;
    }
    while (i != NULL) {
        S -= j->val;
        j = j->next;
        S += i->val;
        i = i->next;
        printf("%lld\n", S);
    }
    return 0;
}