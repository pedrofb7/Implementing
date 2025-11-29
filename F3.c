#include <stdio.h>
#include <stdlib.h>

// node
typedef struct node {
    int val;
    struct node *next;
} node;

// pilha
typedef struct {
    node *start;
    node *end;
    int size;
} pilha;

// criando a P
void create(pilha *Q) {
    Q->start = NULL;
    Q->end = NULL;
    Q->size = 0;
}

// adicionar à P
void enpilha(pilha *Q, int x) {
    node *new = (node *)malloc(sizeof(node));
    new->val = x;
    new->next = Q->start;
    Q->start = new;

    if (new->next == NULL) {
        Q->end = new;
    }
    Q->size++;
}

int depilha(pilha *Q) {
    if (Q->start == NULL) return -1;

    node *temp = Q->start;
    int res = temp->val;

    Q->start = Q->start->next;

    // se fosse o ultimo elemento da P torna end nulo
    if (Q->start == NULL) {
        Q->end = NULL;
    }
    Q->size--;

    free(temp);

    return res;
}

int main () {
    pilha *P = (pilha *)malloc(sizeof(pilha));
    create(P);
    int q;
    scanf(" %d", &q);
    while (q--) {
        int x;
        char a;
        scanf(" %c", &a);
            switch (a) {
            case 'P':
                scanf(" %d", &x);
                enpilha(P, x);
                break;
            
            case 'O':
                printf("%d\n", depilha(P));
                break;
            
            case 'T':
                if (P->start == NULL) {
                    printf("%d\n", -1);
                }
                else {
                    printf("%d\n", (P->start)->val);
                }
                break;

            case 'S':
                printf("%d\n", P->size);
                break;
            
            case 'C':
                while (P->start != NULL) {
                    depilha(P);
                }
                break;
            
            default:
                break;
            }
    }
    return 0;
}