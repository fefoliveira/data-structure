#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct pilha{
	int data;
	struct pilha *prox;
}knot;

int ask_for_value(char *string);
void imprime(knot *start);
void up_insert(knot **start, knot **unstack,  int valor);
void delete_beg(knot **start);
void desempilhar(knot **unstack, knot **start);
void reempilhar(knot **unstack, knot **start);

int main(){
	bool repete = true;
	int escolha, valor;
	knot *start = NULL, *unstack = NULL;
	
	while(repete){
		printf("Controle de pilha:"
		"\n01 - Empilhar um valor: "
		"\n02 - Desempilhar o ultimo valor empilhado"
		"\n03 - Reempilhar o ultimo valor desempilhado"
		"\n04 - Imprimir pilha 1"
		"\n05 - Imprimir pilha 2"
		"\n06 - Finalizar o programa"
		"\nSua escolha: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 6){
			printf("Invalido! Insira novamente sua escolha: ");	
			scanf("%d", &escolha);
		}
		switch(escolha){
			case 1:
				valor = ask_for_value("Digite um valor que deseja empilhar: ");
				up_insert(&start, &unstack, valor);
				break;
			case 2:
				start = start->prox;
				system("cls||clear");
				printf("Ultimo valor desempilhado com sucesso!\n\n");
				break;
			case 3:
				reempilhar(&unstack, &start);
				break;
			case 4:
				system("cls||clear");
				printf("Pilha 1:\n--------------------------------------------------------\n");
				imprime(start);
				printf("--------------------------------------------------------\n\n");
				break;
			case 5:
				system("cls||clear");
				printf("Pilha 2:\n--------------------------------------------------------\n");
				imprime(unstack);
				printf("--------------------------------------------------------\n\n");
				break;
			case 6:
				system("cls||clear");
				printf("Finalizando o programa...\n\n");
				repete = false;
				break;
		}
	}
}

int ask_for_value(char *string){
	int valor;
	system("cls||clear");
	printf("%s", string);
	scanf("%d", &valor);
	return valor;
}

void imprime(knot *start){
	knot *aux = start;
	bool valid = true;
	//system("cls||clear");
	if(aux == NULL){
		system("cls||clear");
		printf("A pilha esta vazia!\n");
	}
	else{
		printf("Endereco:\t\tValor:\t\tProximo:\n");
		while(aux != NULL && valid){
			if(aux->prox == start)
				valid = false;
			printf("%p\t%d\t\t%p\n", (void *)aux, aux->data, (void *)aux->prox);
			aux = aux->prox;
		}
	}
}

void up_insert(knot **start, knot **unstack, int valor){
	knot *novo;
	novo = (knot*)malloc(sizeof(knot));
	if(novo == NULL)
		printf("\nMemoria insuficiente!");
	else{
		novo->data = valor;
		if(*start == NULL)
			novo->prox = NULL;
		else
			novo->prox = *start;
		*start = novo;
		*unstack = *start;	//Associacao da pilha 1 com a pilha 2
		system("cls||clear");
		printf("Valor inserido no topo com sucesso!\n\n");
	}
}

void reempilhar(knot **unstack, knot **start){
	knot *aux = *unstack;
	if(*start){
		system("cls||clear");
		printf("A pilha esta vazia!\n");
	}
	else{
		if(aux != NULL && aux != *start){
		    while(aux->prox != *start)
		      aux = aux->prox;
		    *start = aux;
		    system("cls||clear");
			printf("O ultimo valor desempilhado foi reempilhado com sucesso!\n");
	 	}
	 	else{
		    system("cls||clear");
			printf("A pilha esta vazia OU esta em seu estado completo!\n");
		}
	}
}
