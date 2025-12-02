#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
    struct node *last;
} node;

typedef struct {
    node *start;
    node *end;
    int size;
} dl;

void create(dl *L) {
    L->start = NULL;
    L->end = NULL;
    L->size = 0;
}

void enlista(dl *L, int p, int x) { 
    if (p < 0 || p > L->size) { 
        printf("-1\n");
        return;
    }
    node *new = (node *)malloc(sizeof(node));
    new->val = x;
    new->next = L->start;
    new->last = NULL;
    L->size++;
    if (L->size == 1) {
        L->start = new;
        L->end = new;
        return;
    }
    int i = 0;
    while (i != p) { 
        i++;
        new->last = new->next;
        new->next = (new->next)->next;
    }
    if (new->next == NULL) {
        L->end = new;
        (new->last)->next = new;
        return;
    }
    if (new->last == NULL) {
        L->start = new;
        (new->next)->last = new; 
        return;
    }
    (new->last)->next = new;
    (new->next)->last = new; 
}

void delista(dl *L, int p) {
    if (p < 0 || p > L->size - 1) {
        printf("-1\n");
        return;
    }
    L->size--;
    node *temp =  L->start;
    if (L->size == 0) {
        L->start = NULL;
        L->end = NULL;
        free(temp);
        return;
    }
    if (p == 0) {
        L->start = temp->next;
        (L->start)->last = NULL;
        free(temp);
        return;
    }
    else if (p == L->size) {
        temp = L->end;
        L->end = temp->last;
        (L->end)->next = NULL;
        free(temp);
        return;
    }
    int i = 0;
    while (i != p) { 
        temp = temp->next;
        i++;
    }
    (temp->last)->next = temp->next;
    (temp->next)->last = temp->last;
    free(temp);
}

void pelista(dl *L, int p) {
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

void telista(dl *L) {
    printf("%d\n", L->size);
}

void allista(dl *L) {
    node *temp = L->start;
    while (temp != NULL) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

void reallista(dl *L) {
    node *temp = L->end;
    while (temp != NULL) {
        printf("%d ", temp->val);
        temp = temp->last;
    }
    printf("\n");
}

int main () {
    dl *L = (dl *)malloc(sizeof(dl));
    create(L);
    int N, x;
    scanf(" %d", &N);
    while (N--) {
        scanf(" %d", &x);
        node *temp = L->start;
        for (int i = 0; i <= L->size; i++) {
            if (temp == NULL || x <= temp->val) {
                enlista(L, i, x);
                break;
            }
            temp = temp->next;
        }
    }
    allista(L);
    return 0;
}