/*
1. Faca um codigo em c que permita ao usuario buscar um valor em uma lista. O usuario digita um valor, voce
deve percorrer a lista e verificar se encontra o valor solicitado.
	a. Caso encontre, imprima o endereco do valor, o valor e o endereco do proximo.
	b. Caso nao encontre, informe ao usuario.
	c. Caso a lista esteja vazia, informe ao usuario
	
2. Após fazer uma busca por valor, insira ordenado uma lista. Ao digitar um valor, o seu código deve fazer a
inserção ordenada.
	a. Sempre apresente, o endereço do dado, o dado e o endereço do próximo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list{
	int data;
	struct list *prox ;
}knot;

//void up_insert(knot **start, int valor);
//void down_insert(knot **start, int valor);
void sorting_insert(knot **start, int valor);
void imprime(knot *start);
void find_data(knot *start, int valor);
bool empty(knot *start);

int main(){
	bool repete = true, repete2 = true, vazio;
	int escolha, valor;
	knot *start = NULL;
	
	while(repete){
		printf("Sistema de uso de listas:"
		"\n1 - Cadastrar novos valores na lista"
		"\n2 - Buscar valores na lista"
		"\n3 - Finalizar o programa"
		"\nSua opcao: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 3){
			printf("Invalido! Digite novamente sua escolha: ");
			scanf("%d", &escolha);
		}
		system("cls");
		switch(escolha){
			case 1:
				repete2 = true;
				while(repete2){
					printf("Cadastro de valores:"
					/*"\n1 - Inserir acima (a esquerda)"
					"\n2 - Inserir abaixo (a direita)"
					"\n3 - Imprimir (checar os numeros cadastrados)"
					"\n4 - Finalizar etapa de cadastro"
					"\nSua escolha: ");*/
					"\n1 - Inserir valor (ordenado automaticamente)"
					"\n2 - Imprimir (checar os numeros cadastrados)"
					"\n3 - Finalizar etapa de cadastro"
					"\nSua escolha: ");
					scanf("%d", &escolha);
					while(escolha < 1 || escolha > 3){
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
							imprime(start);
							break;
						case 3:
							repete2 = false;
							system("cls");
							break;
					}
				}
				break;
			case 2:
				repete2 = true;
				while(repete2){
					printf("Busca de valores:"
					"\n1: Digite um valor que deseja buscar na lista"
					"\n2: Finalizar etapa de busca"
					"\nSua escolha: ");
					scanf("%d", &escolha);
					while(escolha != 1 && escolha != 2){
						printf("Invalido! Digite novamente sua escolha: ");
						scanf("%d", &escolha);
					}
					switch (escolha){
						case 1:
							if(empty(start)){
								printf("A lista esta vazia.\n\n");
								repete2 = false;
								break;
							}
							else{
								printf("\nDigite o valor que quer consultar: ");
								scanf("%d", &valor);
								find_data(start, valor);
							}
							break;
						case 2:
							system("cls");
							repete2 = false;
							break;
					}
				}
				break;
			case 3:
				repete = false;
				printf("Finalizando...");
				break;
		}
	}
}

/*
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
*/

/*
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
*/

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

void find_data(knot *start, int valor){
	knot *aux = start; bool cont = false;
	while(aux->prox != NULL){
		if(aux->data == valor){
			printf("O valor consultado foi encontrado em:\n"
			"Endereco:\t\tValor:\t\tProximo:\n");
			printf("%p\t%d\t\t%p\n", (void *)aux, aux->data, (void *)aux->prox);
			cont = true;
		}
		aux = aux->prox;
		printf("\n");
	}
	if(aux->prox == NULL && aux->data == valor){
		printf("O valor consultado foi encontrado em:\n"
		"Endereco:\t\tValor:\t\tProximo:\n");
		printf("%p\t%d\t\t%p\n", (void *)aux, aux->data, (void *)aux->prox);
		printf("\n");
		cont = true;
	}
	if(cont == false)
		printf("O valor consultado nao foi encontrado!\n\n");
}

bool empty(knot *start){
	knot *aux = start;
	if(aux == NULL)
		return true;
	else
		return false;
}








