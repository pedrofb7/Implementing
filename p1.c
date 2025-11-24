#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	
	struct node *prev; //aponta para o node anterior
	long long int val;    //valor deste node

	}node;

typedef struct {

	node *top; //aponta para o topo da pilha
	long long int size;

	}stack;

//função para inicializar a pilha
void init_stack(stack *S) {

	S->top = NULL;
	S->size = 0;
}

//funcao para inserir na pilha
void push(stack *S, long long int x) {

	//criando o novo node
	node *new = (node *)malloc(sizeof(node));
	new->val = x;
	new->prev = S->top;

	S->top = new;
	S->size +=1;
	
}

long long int pop(stack *S) {

	if (S->top ==NULL) return -1;
		
		node *temp = (node *)malloc(sizeof(node));
		temp = S->top;
		int res = temp->val;

		S->top = S->top->prev;
		S->size -=1;

		free(temp);

	return res;
}

long long int print_top(stack *S) {

	if (S->top ==NULL) return -1;
	
	return S->top->val;

}

int main () {

	//criando e inicializando a pilha
	stack *pilha = (stack *)malloc(sizeof(stack));	
	init_stack(pilha);

	//requisitando o numero de operacoes do usuario
	long long int q;
	scanf("%lld", &q);

	while (q--) {

		char a;
		scanf(" %c", &a);
		
		long long int x;
		node *curr = pilha->top;

		switch (a) {

			case 'I':
			     scanf("%lld", &x);

			     push(pilha, x);
			     break;

			case 'R':
			     printf("%lld\n", pop(pilha));
			     break;

			case 'T':
			     printf("%lld\n", print_top(pilha));
			     break;

			case 'S':
			     printf("%lld\n", pilha->size);
			     break;

			case 'C':

			     while(curr != NULL) {

				     curr = pilha->top->prev;
				     pop(pilha);

			     }

			     break;

			case 'P':

			     if(pilha->top != NULL) {

			     	node *curr = pilha->top;
			     	while(curr != NULL) {

				     printf("%lld ", curr->val);
				     curr = curr->prev;

			     }
				printf("\n");
				break;
			}

		}
	}

	return 0;
}























