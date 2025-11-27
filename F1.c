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
    queue *fila = (queue *)malloc(sizeof(queue));
    create(fila);
    int q;
    scanf(" %d", &q);
    while (q--) {
        int x;
        char a;
        scanf(" %c", &a);
            switch (a) {
            case 'I':
                scanf(" %d", &x);
                enqueue(fila, x);
                break;
            
            case 'R':
                printf("%d\n", dequeue(fila));
                break;
            
            case 'F':
                if (fila->start == NULL) {
                    printf("%d\n", -1);
                }
                else {
                    printf("%d\n", (fila->start)->val);
                }
                break;
            
            case 'B':
                if (fila->end == NULL) {
                    printf("%d\n", -1);
                }
                else {
                    printf("%d\n", (fila->end)->val);
                }
                break;
            
            case 'S':
                printf("%d\n", fila->size);
                break;
            
            case 'C':
                while (fila->start != NULL) {
                    dequeue(fila);
                }
                break;
            
            case 'P':
                if (fila->start != NULL) {
                    node *temp = fila->start;
                    while (temp != NULL) {
                        printf("%d ", temp->val);
                        temp = temp->next;
                    }
                }
                printf("\n");
                break;
            
            default:
                break;
            }
    }
    return 0;
}
