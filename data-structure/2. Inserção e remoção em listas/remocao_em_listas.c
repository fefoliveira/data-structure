#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list{
	int data;
	struct list *prox ;
}knot;

void sorting_insert(knot **start, int valor);
void imprime(knot *start);
void remove_fim(knot **start);
void remove_inicio(knot **start);
void remove_busca(knot **start, int valor);

int main(){
	bool repete = true;
	int escolha, valor;
	knot *start = NULL;
	
	while(repete){
		printf("Cadastro de valores:"
		"\n1 - Inserir valor (ordenado automaticamente)"
		"\n2 - Imprimir (checar os numeros cadastrados)"
		"\n3 - Remover (no fim)"
		"\n4 - Remover (no inicio)"
		"\n5 - Remover (buscar)"
		"\n6 - Finalizar programa"
		"\nSua escolha: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 5){
			printf("Invalido! Digite novamente sua escolha: ");
			scanf("%d", &escolha);
		}
		switch(escolha){
			case 1:
				printf("\nDigite o valor que quer inserir: ");
				scanf("%d", &valor);
				sorting_insert(&start, valor);
				system("cls");
				imprime(start);
				break;
			case 2:
				printf("\n");
				system("cls");
				imprime(start);
				break;
			case 3:
				system("cls");
				remove_fim(&start);
				break;
			case 4:
				system("cls");
				remove_inicio(&start);
				break;
			case 5:
				printf("\nInforme o valor que quer buscar e remover da lista: ");
				scanf("%d", &valor);
				system("cls");
				remove_busca(&start, valor);
				break;
			case 6:
				repete = false;
				system("cls");
				printf("Finalizando...");
				break;
		}
	}
}

void sorting_insert(knot **start, int valor){
	knot *novo, *aux;
	novo = (knot*)malloc(sizeof(knot));
	if(novo == NULL)
		printf("\nMemoria insuficiente!");
	else{
		novo->data = valor;
		aux = *start;
		if(aux == NULL){
			novo->prox = NULL;
			*start = novo;
		}
		else if(novo->data < aux->data){
			novo->prox = *start;
			*start = novo;
		}
		else if(novo->data > aux->data){
			while(aux->prox && novo->data > aux->prox->data)
				aux = aux->prox;
			novo->prox = aux->prox;
			aux->prox = novo;
		}
	}
}

void imprime(knot *start){
	knot *aux = start;
	if(aux == NULL)
		printf("A lista esta vazia.\n");
	else{
		printf("Endereco:\t\tValor:\t\tProximo:\n");
		while(aux != NULL){
			printf("%p\t%d\t\t%p\n", (void *)aux, aux->data, (void *)aux->prox);
			aux = aux->prox;
		}
	}
	printf("\n");
}

void remove_fim(knot **start){
	knot *aux, *ant, *pos;
	aux = *start;
	pos = NULL;
	if(*start == NULL)
		printf("A lista esta vazia.\n");
	else if(aux->prox == NULL){
		free(aux);
		*start = NULL;
		printf("Removido com sucesso.\n");
	}
	else{
		while(aux->prox != NULL){
			ant = aux;
			aux = aux->prox;
		}
		pos = aux;
		if(pos != NULL){
			ant->prox = pos->prox;
			free(pos);
			printf("Removido com sucesso.\n");
		}
	}
	printf("\n");
}

void remove_inicio(knot **start){
	knot *aux = *start;
	if(*start == NULL)
		printf("A lista esta vazia.\n");
	else if(aux->prox == NULL){
		free(aux);
		*start = NULL;
		printf("Removido com sucesso.\n");
	}
	else{
		*start = aux->prox;
		free(aux);
		printf("Removido com sucesso.\n");
	}
	printf("\n");
}

void remove_busca(knot **start, int valor){
	knot *aux = *start;
	bool cont = false;
	if(*start == NULL)
		printf("A lista esta vazia.\n");
	else{
		if(aux->prox == NULL){
			free(*start);
			cont = true;
		}
		else{
			while(aux->prox != NULL){
				if(aux->data == valor){
					*start = aux->prox;
					free(aux);
					cont = true;
				}
				aux = aux->prox;
				printf("\n");
			}
			if(cont == false)
				printf("O valor consultado nao foi encontrado!\n\n");
			else
				printf("O valor consultado foi removido com sucesso!\n\n");
		}
	}
}
