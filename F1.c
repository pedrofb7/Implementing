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

    free(temp);

    return res;
}
