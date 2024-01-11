#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list{
	int data;
	struct list *prox ;
}knot;

void up_insert(knot **start, int valor);
void down_insert(knot **start, int valor);
void imprime();

int main(){
	bool repete = true;
	int escolha, valor;
	knot *start = NULL;
	
	while(repete){
		printf("1 - Inserir acima (a esquerda)"
		"\n2 - Inserir abaixo (a direita)"
		"\n3 - Imprimir"
		"\n4 - Sair"
		"\nSua escolha: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 4){
			printf("\nInvalido! Digite novamente sua escolha: ");
			scanf("%d", &escolha);
		}
		
		switch(escolha){
			case 1:
				printf("\nDigite o valor que quer inserir: ");
				scanf("%d", &valor);
				printf("\n");
				up_insert(&start, valor);
				break;
			case 2:
				printf("\nDigite o valor que quer inserir: ");
				scanf("%d", &valor);
				printf("\n");
				down_insert(&start, valor);
				break;
			case 3:
				imprime(start);
				break;
			case 4:
				repete = false;
				printf("\nFinalizando...");
				break;
		}
	}
}

void up_insert(knot **start, int valor){
	knot *novo;
	novo = (knot*)malloc(sizeof(knot));
	if(novo == NULL)
		printf("\nMemoria insuficiente!");
	else{
		novo->data = valor;
		if(start == NULL)
			novo->prox = NULL;
		else
			novo->prox = *start;
		*start = novo;
	}
}


void down_insert(knot **start, int valor){
	knot *novo, *aux;
	novo = (knot*)malloc(sizeof(knot));
	if(novo == NULL)
		printf("\nMemoria insuficiente!");
	else{
		novo->data = valor;
		novo->prox = NULL;
		aux = *start;
		if(aux == NULL)
			*start = novo;
		else{
			while(aux->prox != NULL){
				aux = aux->prox;
			}
		aux->prox = novo;
		}
	}
}

void imprime(knot *start){
	knot *aux;
	aux = start;
	printf("\nEndereco\tValor\tProximo\n");
	while(aux != NULL){
		printf("%d\t\t%d\t%d\n", aux, aux->data, aux->prox);
		aux = aux->prox;
	}
	printf("\n");
}
