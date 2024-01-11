#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct lista{
	int data;
	struct lista *prox;
}knot;

int ask_for_value();
void imprime(knot *start);
void up_insert(knot **start, int valor);					//insere no inicio
void down_insert(knot **start, int valor);					//insere no fim
void sorting_insert(knot **start, int valor);				//insere ordenado
void delete_end(knot **start);								//remove no final
void delete_beg(knot **start);								//remove no inicio
void search_k(knot **start, int escolha);					//funcao que percorre a lista e busca o K desejado, apos achalo, direciona a funcao para a busca, a insercao no meio ou a remocao no meio
void insert_before_k(knot **aux, knot **ant, int k);		//insere no meio (antes do K) -> e chamada dentro da 'search_k'
void delete_search(knot **auxiliar, knot **anterior);		//remove no meio (antes do K) -> tambem e chamada dentro da 'search_k'
void turn_to_circle(knot *start);							//torna a lista circular

int main(){
	bool repete = true;
	int escolha, valor;
	knot *start = NULL;
	
	while(repete){
		printf("Controle de lista:"
		"\n01 - Inserir no inicio"
		"\n02 - Inserir no final"
		"\n03 - Inserir ordenado"
		"\n04 - Inserir no meio (antes de um valor K)"
		"\n05 - Remover no final"
		"\n06 - Remover no inicio"
		"\n07 - Remover no meio (antes de um valor K)"
		"\n08 - Buscar um valor"
		"\n09 - Tornar a lista circular"
		"\n10 - Imprimir lista"
		"\n11 - Finalizar o programa"
		"\nSua escolha: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 11){
			printf("Invalido! Insira novamente sua escolha: ");	
			scanf("%d", &escolha);
		}
		switch(escolha){
			case 1:
				valor = ask_for_value();
				up_insert(&start, valor);
				break;
			case 2:
				valor = ask_for_value();
				down_insert(&start, valor);
				break;
			case 3:
				valor = ask_for_value();
				sorting_insert(&start, valor);
				break;
			case 4:
				search_k(&start, escolha);
				break;
			case 5:
				delete_end(&start);
				break;
			case 6:
				delete_beg(&start);
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
				imprime(start);
				break;
			case 11:
				system("cls||clear");
				printf("Finalizando o programa...\n");
				repete = false;
				break;
		}
	}
}

int ask_for_value(){
	int valor;
	system("cls||clear");
	printf("Digite o valor que quer inserir: ");
	scanf("%d", &valor);
	return valor;
}

void imprime(knot *start){
	knot *aux = start;
	bool valid = true;
	system("cls||clear");
	if(aux == NULL)
		printf("A lista esta vazia!\n");
	else{
		printf("Endereco:\t\tValor:\t\tProximo:\n");
		while(aux != NULL && valid){
			if(aux->prox == start)
				valid = false;
			printf("%p\t%d\t\t%p\n", (void *)aux, aux->data, (void *)aux->prox);
			aux = aux->prox;
		}
	}
	printf("\n");
}

void up_insert(knot **start, int valor){
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
		printf("Valor inserido no topo com sucesso!\n\n");
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
			while(aux->prox != NULL)
				aux = aux->prox;
		aux->prox = novo;
		}
		printf("Valor inserido no fim com sucesso!\n\n");
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
		printf("Valor inserido e ordenado com sucesso!\n\n");
	}
}

void delete_end(knot **start){
	knot *aux, *ant, *pos;
	aux = *start;
	pos = NULL;
	system("cls||clear");
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

void delete_beg(knot **start){
	knot *aux = *start;
	system("cls||clear");
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

void search_k(knot **start, int escolha){
	int k, valor_antes;	
	bool encontrado = false, valid = true;
	knot *aux = *start, *ant;
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
                	printf("\nEndereco:\t\tValor:\t\tProximo:\n%p\t%d\t\t%p\n\n", (void *)aux, aux->data, (void *)aux->prox);
                else if(escolha == 4){
                	printf("Digite o valor que deseja inserir antes do k: ");
                	scanf("%d", &valor_antes);
                	insert_before_k(&aux, &ant, valor_antes);
                	valid = false;
				}
                else if(escolha == 7){
                	delete_search(&aux, &ant);
                	valid = false;
				}
			}
			ant = aux;
			aux = aux->prox;
		}
		if(encontrado == false)
			printf("\nNao foi encontrado o valor solicitado.\n\n");
	}
	else
		printf("A lista nao existe!\n\n");
}

void insert_before_k(knot **aux, knot **anterior, int k){
	knot *novo = (knot*)malloc(sizeof(knot)), *ant = *anterior;
	system("cls||clear");
	if(novo == NULL){
		printf("Memoria Insuficiente!");
	}
	else{
		ant->prox = novo;
		novo->data = k;
		novo->prox = *aux;
		printf("O valor foi inserido antes do buscado com sucesso!\n\n");
	}
}

void delete_search(knot **auxiliar, knot **anterior){
	knot *aux = *auxiliar, *ant = *anterior;
	system("cls||clear");
	ant->prox = aux->prox;
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
			aux->prox = start;
			printf("Sua lista foi circularmente encadeada com sucesso.\n\n");
		}
	}
	else
		printf("A lista nao existe!\n\n");
}
