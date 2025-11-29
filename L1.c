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

void enlista(lista *L, int p, int x) { //insere em alguma posição especificada no parametro p
    if (p < 0 || p > L->size) { // verifica se ta fora dos índices
        printf("-1\n");
        return;
    }
    node *new = (node *)malloc(sizeof(node));
    new->val = x;
    if (p == 0) { // caso especial de início
        new->next = L->start;
        L->start = new;
        L->size++;
        return;
    }
    new->next = L->start;
    int i = 0;
    while (i != p - 1) { //empurra o nodulo alvo até ser um antes do indice que voce quer inserir
        i++;
        new->next = (new->next)->next;
    }
    node *temp = (new->next)->next; // aponta temp pra um depois do indice que voce quer inserir
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
    while (i != p - 1) { //empurra o nodulo alvo até ser um antes do indice que voce quer apagar
        temp = temp->next;
        i++;
    }
    node *temp2 = temp->next; //auxiliar em cima do elemento que vai ser removido
    temp->next = temp2->next; //elemento anterior ao que vai ser retirado passa a apontar para o elemento depois do q vai ser removido
    free(temp2); //libera o que vai ser removido
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