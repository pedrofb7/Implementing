#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//-------------------
// Definicoes
//-------------------

typedef struct node {

	struct node *prev;	//node anterior na pilha
	char term;		//character desse node
	int prec;		//precedencia do caracter, vai de 0 a 3

}node;

typedef struct stack {

	node *top;

}stack;

//-------------------
// Funcoes
//-------------------

//inicializar
void init_stack(stack *S) {

	S->top = NULL;
}

//inserir
void push(stack *S, char c, int x) {

	node *new = (node *)malloc(sizeof(node));
	new->prev = S->top;

	new->term = c;
	new->prec = x;
	S->top = new;

}

//remover
char pop(stack *S) {

	node *temp = S->top;
	S->top = S->top->prev;

	char res = temp->term;

	free(temp);

	return res;
}

//funcao para tratar os caracteres
void translate(stack *S, char c) {

	if(isdigit(c) || isalpha(c)) printf("%c ", c);	//printa se for uma variavel ou numero
	
	else if(c == '(') push(S, c, 0);		//insere na pilha se for '('	

	else if(c == '+'|| c == '-'|| c == '*' || c == '/' || c == '^') {

		int prec; //precedencia do operador utilizado
		
		switch(c) {

			case '+':
				prec = 1;
				break;
			case '-':
				prec = 1;
				break;
			case '*':
				prec = 2;
				break;
			case '/':
				prec = 2;
				break;
			case '^':
				prec = 3;
				break;

		}
		
		if(S->top == NULL || S->top->prec < prec) push(S, c, prec);

		else if(prec == 3) push(S, c, prec);

		else {

			while(S->top != NULL && S->top->prec >= prec && S->top->term != '(') {

				printf("%c ", pop(S));

			}

			push(S, c, prec);
		}
	}

	else {

		while(S->top != NULL && S->top->term != '(') {

			printf("%c ", pop(S));
		}

		pop(S);

	}
}



int main() {

	stack *R = (stack *)malloc(sizeof(stack)); //stack de leitura
	init_stack(R);

	stack *S = (stack *)malloc(sizeof(stack)); //stack de trabalho
	init_stack(S);

	char c;
	
	//variavel de checagem
	int eval = 1;
	char prev = '@';
	int closes = 0;

	while(1) {

		scanf("%c", &c);
		if(c == '\n') break;



		else if((c == '+'|| c == '-'|| c == '*' || c == '/' || c == '^') && 
		  (prev == '+'|| prev == '-'|| prev == '*' || prev == '/' || prev == '^' || prev == '@')) {

			eval = 0;
			break;
		}

		
		else if(c == '(') closes -= 1;
		else if(c == ')' && closes >= 0) {

			eval = 0;
			break;
		}
		else if (c == ')') closes += 1; 

		prev = c;
		
		//inserindo em ordem na pilha de leitura
		if (R->top == NULL) push(R, c, 0);
		else {

			while (R->top != NULL) {

				char ch = pop(R);
				push(S, ch, 0);		//usando a pilha de trabalho como auxiliar 
			}

			push(R, c, 0);

			while(S->top != NULL) {

				char ch = pop(S);
				push(R, ch, 0);		//reinserindo na pilha de leitura

			}
		}

	}

	if(eval == 0 || closes != 0) printf("Expressao invalida\n");

	else {

		while(R->top != NULL) {

			char ch = pop(R);
			translate(S, ch);


		}

		while(S->top != NULL) {

			printf("%c ", pop(S));

		}

		printf("\n");

	}



	return 0;
}
















