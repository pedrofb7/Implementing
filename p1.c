#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	
	struct node *prev; //aponta para o node anterior
	int val;    //valor deste node

	}node;

typedef struct {

	node *top; //aponta para o topo da pilha
	int size;

	}stack;

//função para inicializar a pilha
void init_stack(stack *S) {

	S->top = NULL;
	S->size = 0;
}

//função para inserir na pilha
void push(stack *S, int x) {

	//criando o novo node
	node *new = (node *)malloc(sizeof(node));
	new->val = x;
	new->prev = S->top;

	S->top = new;
	S->size +=1;
	
}

int pop(stack *S) {

	if (S->top ==NULL) return -1;
		
		node *temp = (node *)malloc(sizeof(node));
		temp = S->top;
		int res = temp->val;

		S->top = S->top->prev;
		S->size -=1;

		free(temp);

	return res;
}

int print_top(stack *S) {

	if (S->top ==NULL) return -1;
	
	return S->top->val;

}

int main () {

	//criando e inicializando a pilha
	stack *pilha = (stack *)malloc(sizeof(stack));	
	init_stack(pilha);

	//requisitando o numero de operacoes do usuario
	int q;
	scanf("%d", &q);

	while (q--) {

		char a;
		scanf(" %c", &a);

		switch (a) {

			case 'I':
			     int x;
			     scanf("%d", &x);

			     push(pilha, x);
			     break;

			case 'R':
			     printf("%d\n", pop(pilha));
			     break;

			case 'T':
			     printf("%d\n", print_top(pilha));
			     break;

			case 'S':
			     printf("%d\n", pilha->size);
			     break;

			case 'C':
			     node *curr = pilha->top;

			     while(curr != NULL) {

				     curr = pilha->top->prev;
				     pop(pilha);

			     }

			     break;

			case 'P':

			     if(pilha->top != NULL) {

			     	node *curr = pilha->top;
			     	while(curr != NULL) {

				     printf("%d ", curr->val);
				     curr = curr->prev;

			     }
				printf("\n");
				break;
			}

		}
	}

	return 0;
}























