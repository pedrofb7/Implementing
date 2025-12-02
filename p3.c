#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//------------------
//Definicoes
//------------------

//estrutura node
typedef struct node {

	struct node *prev;	//ponteiro para o node anterior da pilha
	char term;		//caractere do node
	int prec;		//a precedencia do termo caso seja um operador
}node;

//estrutura stack
typedef struct stack {

	node *top;
	int size;
}stack;


//------------------
//Funcoes
//------------------

//inicializar pilha
void init_stack(stack *S) {

	S->top = NULL;
	S->size = 0;
}

//inserir
int push(stack *S, char c) {

	node *new = (node *)malloc(sizeof(node));
	int preced;	//precedencia do novo node

	new->term = c;

	//avaliando o caracter que foi empilhado
	switch(c) {

		case '(':
		case ')':
			preced = 0;
			break;

		case '+':
		case '-':
			preced = 1;
			break;

		case '*':
		case '/':
			preced = 2;
			break;
		case '^':
			preced = 3;
			break;

	}

	new->prec = preced;

	new->prev = S->top;
	S->top = new;
}

//remover
char pop(stack *S) {

	node *temp = S->top;
	char res = temp->term;

	S->top = S->top->prev;	//tornando o node anterior o novo topo da pilha

	free(temp);
	return res;
}

//funcao para traduzir
void translate(stack *S, char entrada) {
	

		if (isdigit(entrada) || isalpha(entrada)) printf("%c ", entrada);	//print imadiato se for um digito ou letra

		//devemos empilhar operadores + e -, mas apenas se o operador empilhado anteriormente for menor
		else if(entrada == '+' || entrada == '-') {

			int temp_prec = 1; //assumindo como precedencia 1

			//desempilhado e imprimindo enquanto houver operadores de precedencia maior ou igual na pilha
			while(S->top != NULL && S->top->prec >= temp_prec ) {

				printf("%c ", pop(S));
			}

			push(S, entrada);
		}


		//devemos empilhar operadores * e /, mas apenas se o operador empilhado anteriormente for menor
		else if(entrada == '*' || entrada == '/') {

			int temp_prec = 2; //assumindo como precedencia 2

			//desempilhado e imprimindo enquanto houver operadores de precedencia maior ou igual na pilha
			while(S->top != NULL && S->top->prec >= temp_prec ) {

				printf("%c ", pop(S));
			}

			push(S, entrada);
		}


		else if(entrada == '^') {

			push(S, entrada); //^ deve ser empilhado em todas as ocasioes para o funcionamento do algoritmo
		}

		else if (entrada == '(') push(S, entrada); //aberturas de escopo sao empilhadas

		//ao fechar um escopo deve-se imprimir a pilha inteira até que se ache uma abertura de escopo
		else if (entrada == ')') {

			while(S->top->term != '(') {

				printf("%c ", pop(S)); //printa todos os elementos da pilha (menos '(' )
			}

			pop(S); //desempilhando o '('
		}

}

int main () {

	stack *S = (stack *)malloc(sizeof(stack));
	init_stack(S);

	char entrada[1000];

	while(fgets(entrada, sizeof(entrada), stdin) != NULL) {

		long long int len = strlen(entrada);

		if(entrada[len-1] == '\n') {

			entrada[len-1] = '\0';
			len--;
		}

		if (len == 0) continue;

		//variavei de validacao
		int invalid = 0;
		int closes = 0;

        // Removendo os espaços
        char temp[1000];
        int j = 0;
        for(int i = 0; i < len; i++){

            if(entrada[i] != ' ' && entrada[i] != '\t'){

                temp[j++] = entrada[i];
            }
        }
        
        temp[j] = '\0'; //final da string temporaria
        
        printf("%s\n", temp);

		for(int i = 0; i < len; i++) {

			if(isalpha(temp[i])) {

				//a entrada será invalida se o caracter for uma letra minúscula ou se o caracter anterior for uma letra
				if (!isupper(temp[i]) || (i > 0 && isalpha(temp[i-1]))) {
					invalid = 1;
					break;
				}
			}

			else if(isdigit(temp[i])) {

				if(i > 0 && isdigit(temp[i-1])) {

					invalid = 1;
					break;
				}
			}


			else if(temp[i] == '+' || temp[i] == '-' ||temp[i] == '*' ||temp[i] == '/' || temp[i] == '^') {


			  if(i > 0 && (temp[i-1] == '+' || temp[i-1] == '-' ||temp[i-1] == '*' ||temp[i-1] == '/' || temp[i-1] == '^' )) {

					invalid = 1;
					break;

				}
			}

			else if(temp[i] == '(') closes--;

			//se for um fechamento de escopo e nao houver nenhum escopos abertos correspondentes sera invalido
			else if(temp[i] == ')') {
				if(closes >=0) {
					invalid = 1;
					break;
				}

				closes++;
			}
			



		}


			if(closes != 0) invalid =1;

			if (invalid) printf("Expressao invalida\n");

			else {
				for (int i = 0; i < len; i++)  {

					translate(S, temp[i]);

				}

				while(S->top !=NULL) printf("%c ", pop(S));
				printf("\n");

			}

			printf("\n");
	
	}



}









