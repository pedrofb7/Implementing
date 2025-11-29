#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} node;

typedef struct {
    node *start;
    node *end;
    int size;
} lista;

void create(lista *L) {
    L->start = NULL;
    L->end = NULL;
    L->size = 0;
}

void enlista(lista *L, int p, int x) {
    if (p < 0 || p > L->size) {
        printf("-1\n");
        return;
    }
    node *new = (node *)malloc(sizeof(node));
    new->val = x;
    if (p == 0) {
        new->next = L->start;
        L->start = new;
        L->size++;
        return;
    }
    new->next = L->start;
    int i = 0;
    while (i != p - 1) {
        i++;
        new->next = (new->next)->next;
    }
    node *temp = (new->next)->next;
    (new->next)->next = new;
    new->next = temp;
    L->size++;
}

void delista(lista *L, int p) {
    if (p < 0 || p > L->size - 1) {
        printf("-1\n");
        return;
    }
    node *temp =  L->start;
    if (p == 0) {
        L->start = (L->start)->next;
        free(temp);
        L->size--;
        return;
    }
    int i = 0;
    while (i != p - 1) {
        temp = temp->next;
        i++;
    }
    node *temp2 = temp->next;
    temp->next = temp2->next;
    free(temp2);
    L->size--;
}

void pelista(lista *L, int p) {
    if (p < 0 || p > L->size - 1) {
        printf("-1\n");
        return;
    }
    node *temp =  L->start;
    int i = 0;
    while (i != p) {
        temp = temp->next;
        i++;
    }
    printf("%d\n", temp->val);
}

void telista(lista *L) {
    printf("%d\n", L->size);
}

void allista(lista *L) {
    int i = 0;
    node *temp = L->start;
    while (temp != NULL) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

int main () {
    lista *L = (lista *)malloc(sizeof(lista));
    create(L);
    int q;
    scanf(" %d", &q);
    while (q--) {
        int x;
        int p;
        char a;
        scanf(" %c", &a);
            switch (a) {
            case 'I':
                scanf(" %d %d", &p, &x);
                enlista(L, p, x);
                break;
            
            case 'R':
            scanf(" %d", &p);
                delista(L, p);
                break;
            
            case 'G':
            scanf(" %d", &p);
                pelista(L, p);
                break;
            
            case 'T':
                telista(L);
                break;
            
            case 'P':
                allista(L);
                break;

            default:
                break;
            }
    }
    return 0;
}