//Inserção antes do K

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct lista{
	int data;
	struct lista *prox;
}knot;

knot* busca_k(knot **start);
void insere_antes_do_k(knot **aux, knot **ant, int k);
void up_insert(knot **start, int valor);
void sorting_insert(knot **start);
void imprime(knot *start);

int main(){
	bool repete = true;
	int escolha;
	knot *start;
	
	while(repete){
		printf("Controle de lista:"
		"\n1 - Inserir ordenado"
		"\n2 - Inserir antes de um valor K"
		"\n3 - Imprimir lista"
		"\n4 - Finalizar o programa"
		"\nSua escolha: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 3){
			printf("Invalido! Insira novamente sua escolha: ");	
			scanf("%d", &escolha);
		}
		switch(escolha){
			case 1:
				sorting_insert(&start);
				imprime(start);
				break;
			case 2:
				busca_k(&start);
				imprime(start);
				break;
			case 3:
				system("cls");
				imprime(start);
				break;
			case 4:
				system("cls");
				printf("Finalizando o programa...\n");
				repete = false;
				break;
		}
	}
}

knot* busca_k(knot **start){
	int k;	
	bool encontrado = false, unico_item = false;
	knot *aux = *start, *ant;
	system("cls");
	if(aux->prox == NULL)
		unico_item = true;
	if(aux){
		printf("Digite o K que deseja buscar: ");
		scanf("%d", &k);
		while(aux != NULL){
			if(aux->data == k){
				if(unico_item)
					up_insert(&start, k);
				else
					insere_antes_do_k(&aux, &ant, k);
				encontrado = true;
			}
			ant->prox = aux;
			aux = aux->prox;
		}
		if(encontrado == false){
			printf("\nNao foi encontrado o valor solicitado.\n\n");
	}
	else{
		printf("\nA lista nao existe!\n\n");
}

void insere_antes_do_k(knot **aux, knot **anterior, int k){
	knot *novo = (knot*)malloc(sizeof(knot)), *ant = *anterior;
	ant->prox = novo;
	novo->data = k;
	novo->prox = aux;
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
	}
}

void sorting_insert(knot **start){
	knot *novo, *aux;
	novo = (knot*)malloc(sizeof(knot));
	int valor;
	
	printf("\nDigite o valor que quer inserir: ");
	scanf("%d", &valor);
	system("cls");
	printf("Valor cadastrado e ordenado com sucesso!\n\n");
	
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
