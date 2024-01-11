#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct lista{
	int data;
	struct lista *prox, *ant;
}knot;

int ask_for_value(char *string);
void imprime(knot *start);
void start_insert(knot **start, int valor);
void end_insert(knot **start, int valor);
void delete_start(knot **start);
void delete_end(knot **start);
void search_k(knot **start, int escolha);					
void insert_before_k(knot **aux, int k);		
void delete_search(knot **auxiliar);
void turn_to_circle(knot *start);	
						
int main(){
	knot *start = NULL;
	bool repete = true;
	int escolha, valor;

	while(repete){
		printf("Controle de lista duplamente encadeada:"
		"\n01 - Inserir no inicio"
		"\n02 - Inserir no fim"
		"\n03 - Imprimir"
		"\n04 - Remover no inicio"
		"\n05 - Remover no fim"
		"\n06 - Inserir no meio (antes da primeira aparicao de um valor K)"
		"\n07 - Remover no meio (a primeira aparicao de um valor K)"
		"\n08 - Buscar por um valor"
		"\n09 - Tornar circular a lista duplamente encadeada"
		"\n09 - Finalizar programa"
		"\nSua escolha: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 9){
			printf("Invalido! Insira novamente sua escolha: ");	
			scanf("%d", &escolha);
		}
		switch(escolha){
			case 1:
				start_insert(&start, ask_for_value("Digite o valor que deseja inserir no inicio: "));
				break;
			case 2:
				end_insert(&start, ask_for_value("Digite o valor que deseja inserir no fim: "));
				break;
			case 3:
				imprime(start);
				break;
			case 4:
				delete_start(&start);
				break;
			case 5:
				delete_end(&start);
				break;
			case 6:
				search_k(&start, escolha);
				break;
			case 7:
				search_k(&start, escolha);
				break;
			case 8:
				search_k(&start, escolha);
				break;
			case 9:
				turn_to_circle(start);
				break;
			case 10:
				system("cls||clear");
				printf("Finalizando o programa...\n");
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
	system("cls||clear");
	printf("----------------------------------------------------------------------------------------\n");
	if(aux == NULL)
		printf("A lista esta vazia!\n");
	else{
		printf("Endereco:\t\tAnterior:\t\tValor:\t\tProximo:\n");
		while(aux != NULL && valid){
			if(aux->prox == start)
				valid = false;
			printf("%p\t%p\t%d\t\t%p\n", (void *)aux, (void *)aux->ant, aux->data, (void *)aux->prox);
			aux = aux->prox;
		}
	}
	printf("----------------------------------------------------------------------------------------\n\n");
}

void start_insert(knot **start, int valor){
	knot *novo = (knot*)malloc(sizeof(knot));
	if(novo == NULL)
		printf("\nMemoria insuficiente!");
	else{
		novo->data = valor;
		if(*start == NULL){		//Lista vazia;
			novo->prox = NULL;
			novo->ant = NULL;
			*start = novo;
		}
		else{					//Lista que ja tem elementos;
			novo->prox = *start;
			(*start)->ant = novo;
			novo->ant = NULL;
		}
		*start = novo;
		printf("Valor inserido no inicio com sucesso!\n\n");
	}
}

void end_insert(knot **start, int valor){
	knot *novo = (knot*)malloc(sizeof(knot)), *aux = *start;
	if(novo == NULL)
		printf("\nMemoria insuficiente!");
	else{
		while(aux->prox != NULL)
			aux = aux->prox;
		novo->data = valor;
		if(*start == NULL){		//Lista vazia;
			novo->prox = NULL;
			novo->ant = NULL;
			*start = novo;
		}
		else{					//Lista que ja tem elementos;
			aux->prox = novo;
			novo->ant = aux;
			novo->prox = NULL;
		}
		aux = novo;
		printf("Valor inserido no fim com sucesso!\n\n");
	}
}

void delete_start(knot **start){
	knot *aux = *start;
	system("cls||clear");
	if(*start == NULL)
		printf("A lista esta vazia.\n");
	else if(aux->prox == NULL){		//Lista com somente um elemento;
		free(aux);
		*start = NULL;
		printf("Removido com sucesso.\n");
	}
	else{
		*start = aux->prox;
		if(*start != NULL)
			(*start)->ant = NULL;
		free(aux);
		printf("Removido com sucesso.\n");
	}
	printf("\n");
}

void delete_end(knot **start){
	knot *aux = *start, *pos;
	system("cls||clear");
	if(*start == NULL)
		printf("A lista esta vazia.\n");
	else if(aux->prox == NULL){		//Lista com somente um elemento;
		free(aux);
		*start = NULL;
		printf("Removido com sucesso.\n");
	}
	else{
		while(aux->prox != NULL)
			aux = aux->prox;
		pos = aux;
		aux = aux->ant;
		aux->prox = NULL;
		free(pos);
		printf("Removido com sucesso.\n");
	}
	printf("\n");
}

void search_k(knot **start, int escolha){
	int k, valor_antes;	
	bool encontrado = false, valid = true;
	knot *aux = *start;
	system("cls||clear");
	if(aux){
		if(escolha == 7)
			printf("Digite o K que deseja buscar e deletar: ");
		else
			printf("Digite o K que deseja buscar: ");
		scanf("%d", &k);
		while(aux != NULL && valid){
			if(aux->data == k){
				encontrado = true;
				if(escolha == 8)
                	printf("\nValor encontrado:\n----------------------------------------------------------------------------------------\nEndereco:\t\tAnterior:\t\tValor:\t\tProximo:\n%p\t%p\t%d\t\t%p\n----------------------------------------------------------------------------------------\n\n", (void *)aux, (void *)aux->ant, aux->data, (void *)aux->prox);
                else if(escolha == 6){
                	printf("Digite o valor que deseja inserir antes do k: ");
                	scanf("%d", &valor_antes);
                	insert_before_k(&aux, valor_antes);
                	valid = false;
				}
                else if(escolha == 7){
                	delete_search(&aux);
                	valid = false;
				}
			}
			aux = aux->prox;
		}
		if(encontrado == false)
			printf("\nNao foi encontrado o valor solicitado.\n\n");
	}
	else
		printf("A lista nao existe!\n\n");
}

void insert_before_k(knot **aux, int k){
	knot *novo = (knot*)malloc(sizeof(knot));
	system("cls||clear");
	if(novo == NULL)
		printf("Memoria Insuficiente!");
	else{
		(*aux)->ant->prox = novo;
		novo->ant = (*aux)->ant;
		novo->data = k;
		novo->prox = *aux;
		printf("O valor foi inserido antes do buscado com sucesso!\n\n");
	}
}

void delete_search(knot **auxiliar){
	knot *aux = *auxiliar;
	aux->ant->prox = aux->prox;
	aux->prox->ant = aux->ant;
	free(aux);
	printf("O valor consultado foi removido com sucesso!\n\n");
}

void turn_to_circle(knot *start){
	knot *aux = start;
	system("cls||clear");
	if(aux){
		if(aux->prox == NULL)
			printf("A lista possui somente um elemento, nao foi possivel torna-la ela circular.\n\n");
		else{		
			while(aux->prox != NULL)
				aux = aux->prox;
			start->ant = aux;
			aux->prox = start;
			printf("Sua lista foi circularmente encadeada com sucesso.\n\n");
		}
	}
	else
		printf("A lista nao existe!\n\n");
}
