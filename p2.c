#include <stdio.h>
#include <stdlib.h>


//-------------------------------
// Definicoes
//-------------------------------

typedef struct node{
	
	struct node *prev; //aponta para o node anterior
	int val;    //valor deste node

	}node;

typedef struct {

	node *top; //aponta para o topo da pilha
	int size;

	}stack;

typedef struct queue {

	stack *tops;
	int size;

	}queue;


//-------------------------------
// Funcoes
//-------------------------------

//funcao para inicializar a pilha
void init_stack(stack *S) {

	S->top = NULL;
	S->size = 0;
}

//funcao para inicializar a fila
void init_queue(queue *Q, stack *S) {

	Q->tops = S;
	Q->size = 0;
}

//funcao para inserir na pilha
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
		
		node *temp = S->top;
		int res = temp->val;

		S->top = S->top->prev;
		S->size -=1;

		free(temp);

	return res;
}

//inserir na fila
void enqueue(queue *Q, stack **current_stack, stack **not_current_stack, stack **top_stack, int x) {

	//Se a current_stack estiver vazia
	if (Q->size == 0) {

		//colocando na current_stack
		push(*current_stack, x);

		//obs, no começo a current_stack e a top_stack apontam para a mesma pilha
	
	}

	//caso ja exista algum elemento na current_stack
	else {

		int size = (*current_stack)->size;

		//desempilhando da current_stack e empilhando na not_current_stack
		while((*current_stack)->top != NULL) {

			int res = pop(*current_stack);
			push(*not_current_stack, res);
		}

		//inserindo o novo elemento na current_stack
		push(*current_stack, x);

		//reempilhando os elementos da not_current_stack que haviam sido desempilhados da current_stack
		for(int i = size; i > 0; i--) {

			int res = pop(*not_current_stack);
			push(*current_stack, res);

		}

	}

		stack *temp = *current_stack;
		*current_stack = *not_current_stack;
		*not_current_stack = temp;

		temp = NULL;
		free(temp);

		Q->tops = *top_stack;

		Q->size +=1;
}


//remover da fila
int  dequeue(queue *Q, stack **top_stack, stack **not_top_stack) {

	if(Q->size != 0) {

		int res = pop(Q->tops);

		stack *temp = *top_stack;
		*top_stack = *not_top_stack;
		*not_top_stack = temp;


		Q->tops = *top_stack;
		Q->size -=1;
		
		return res;

	}
	
	return -1;
}


//imprimir o primeiro da fila
int print_top(queue *Q) {

	if(Q->tops->top != NULL) {

		return Q->tops->top->val;
	}

	return -1;

}




int main() {

	//-----------------------------
	// Alocacoes
	//-----------------------------

	//criando e inicializando as duas pilhas
	stack *S1 = (stack *)malloc(sizeof(stack));
	stack *S2 = (stack *)malloc(sizeof(stack));

	init_stack(S1);
	init_stack(S2);

	//criando e inicializando a fila
	queue *Q = (queue *)malloc(sizeof(queue));
	init_queue(Q, S1);

	//criando ponteiros auxiliares;
	stack *top_s = S1;

	stack *ntop_s = S2;

	stack *curr_s = S1;

	stack *ncurr_s = S2;

	//-----------------------------
	// Inicio
	//-----------------------------
	
	long long int q;
	scanf("%lld", &q);

	while(q--) {

		char a;
		scanf(" %c", &a);

		int x;

		switch(a) {

			case 'I':
			      scanf("%d", &x);

			      enqueue(Q, &curr_s, &ncurr_s, &top_s, x);
			      break;

			case 'R':
			      printf("%d\n", dequeue(Q, &top_s, &ntop_s));
			      break;

			case 'F':
			      printf("%d\n", print_top(Q));
			      break;

			case 'S':
			      printf("%d\n", Q->size);
			      break;

			case 'C':
			      while(Q->tops->top != NULL) {

					dequeue(Q, &top_s, &ntop_s);

			      }
			      break;


		}

	}


	free(S1);
	free(S2);
	free(Q);

}





