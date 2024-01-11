/*Considere que um estacionamento da Rua Direita, em Porto alegre, que e composto por uma unica alameda que varios carros. 
Existe apenas uma entrada/saida no estacionamento, e esta extremidade da alameda da acesso justamente a Rua Direita. 
Se chegar um cliente para retirar um carro que nao seja o mais proximo da saida, todos os carros bloqueando seu caminho sairao do estacionamento. 
O carro do cliente sera manobrado para fora do estacionamento, e os outros carros voltarao a ocupar a mesma sequencia inicial. 
-------------------------------------------------------------------------------------------------------------------------------------
Escreva um programa que processe um grupo de linhas de entrada. 
Cada linha de entrada contem um "E" ou "1", de entrada, ou um "S" ou 2 de saida, e o numero da placa do carro.  
Presume-se que os carros cheguem e partam na mesma ordem que entraram no estacionamento. 
O programa deve imprimir uma mensagem sempre que um carro chegar ou sair. 
Quando um carro chegar, a mensagem deve especificar se existe ou nao vaga para o carro no estacionamento. 
Se nao houver vaga, o carro partira sem entrar no estacionamento. 
Quando um carro sair do estacionamento, a mensagem devera incluir o numero de vezes em que o carro foi manobrado para fora do estacionamento para permitir que os outros carros saissem.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct pilha{
	int data;
	struct pilha *prox;
}knot;

int ask_for_value(char *string);
void imprime(knot *start, char *string);
void estaciona(knot **alameda, int valor);
void retira_alameda(knot **alameda, knot **rua, int valor);

int main(){
	knot *alameda = NULL, *rua = NULL;
	bool repete = true;
	int escolha, valor;

	while(repete){
		printf("Controle de lista:"
		"\n01 - Entrada de carro na alameda"
		"\n02 - Retirar carro selecionado"
		"\n03 - Imprimir carros estacionados na alameda"
		"\n04 - Imprimir carros estacionados na rua"
		"\n05 - Finalizar programa"
		"\nSua escolha: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 11){
			printf("Invalido! Insira novamente sua escolha: ");	
			scanf("%d", &escolha);
		}
		switch(escolha){
			case 1:
				valor = ask_for_value("Digite a placa (em inteiros) do carro estacionado: ");
				estaciona(&alameda, valor);
				imprime(alameda, "alameda");
				printf("O carro de placa '%d' estacionado na alameda com sucesso!\n\n", valor);
				break;
			case 2:
				valor = ask_for_value("Digite a placa (em inteiros) do carro que deseja retirar: ");
				retira_alameda(&alameda, &rua, valor);
				break;
			case 3:
				system("cls||clear");
				imprime(alameda, "alameda");
				printf("\n");
				break;
			case 4:
				system("cls||clear");
				imprime(rua, "rua");
				break;
			case 5:
				system("cls||clear");
				printf("Finalzando programa...");
				repete = false;
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

void imprime(knot *start, char *string){
	knot *aux = start;
	if(aux == NULL)
		printf("A %s esta vazia!"
		"\n--------------------------------------------------------\n\n", string);
	else{
		printf("Carros estacionados na %s:"
		"\n--------------------------------------------------------\n"
		"Endereco:\t\tValor:\t\tProximo:\n", string);
		while(aux != NULL){
			printf("%p\t%d\t\t%p\n", (void *)aux, aux->data, (void *)aux->prox);
			aux = aux->prox;
		}
		printf("--------------------------------------------------------\n");
	}
}

void estaciona(knot **alameda, int valor){
	knot *novo;
	novo = (knot*)malloc(sizeof(knot));
	if(novo == NULL)
		printf("\nMemoria insuficiente!");
	else{
		novo->data = valor;
		if(*alameda == NULL)
			novo->prox = NULL;
		else
			novo->prox = *alameda;
		*alameda = novo;
		system("cls||clear");
	}
}

void retira_alameda(knot **alameda, knot **rua, int valor){
	knot *aux_al = *alameda, *aux_rua = *rua;
	bool encontrado = false;
	int cont = 0, i;
	if(*alameda == NULL){
		system("cls||clear");
		printf("O estacionamento esta vazio!\n\n");
	}
	else{
		if(aux_al->prox == NULL){
			if(aux_al->data == valor){
				*alameda = NULL;
				system("cls||clear");
				printf("O unico carro estacionado na alameda foi retirado!"
				"\n--------------------------------------------------------\n\n");
				//imprime(*alameda, "alameda");
				//imprime(*rua, "rua");
			}
			else{
				system("cls||clear");
				printf("O unico carro estacionado nao condiz com a placa '%d'!"
				"\n--------------------------------------------------------\n\n", valor);					
			}
		}
		else if(aux_al->data == valor){
			aux_al = *alameda;
			*alameda = aux_al->prox;
			free(aux_al);
			system("cls||clear");
			printf("O carro de placa '%d' era o ultimo estacionado e foi removido imediatamente!"
			"\n--------------------------------------------------------\n\n", valor);	
		}
		else{
			while(aux_al != NULL && encontrado == false){	//Checa para ver se a placa buscada esta estacionada.
				if(aux_al->data == valor)
					encontrado = true;
				else
					aux_al = aux_al->prox;
				cont++;
			}
			if(encontrado == false){
				system("cls||clear");
				printf("O carro de placa '%d' nao foi encontrado no estacionamento!"
				"\n--------------------------------------------------------\n\n", valor);
			}
			else{
				aux_al = *alameda;
				//while(aux_al->data != valor){	
				for(i = 0; i < cont; i++){
				//Ao termino desse while, todos os carros na frente do carro que sera retirado, estarao na Rua direita.
					aux_al = *alameda;
					*alameda = aux_al->prox;
					aux_rua = *rua;
					*rua = aux_al;
					(*rua)->prox = aux_rua;
					aux_al = aux_al->prox;
				}
				//Aqui o carro escolhido esta como primeiro da Rua direita e logo eh depois liberado:
				aux_rua = *rua;
				*rua = aux_rua->prox;
				system("cls||clear");
				printf("O carro de placa '%d' e todos os que estavam em sua frente foram manobrados para a Rua Direita."
				"\n--------------------------------------------------------\n", valor);
				imprime(*alameda, "alameda");
				imprime(*rua, "rua");
				free(aux_rua);	//Aqui o carro enfim foi embora.
				printf(".\n.\n.\nO carro de placa '%d' foi embora."
				"\n--------------------------------------------------------\n", valor);
				imprime(*alameda, "alameda");
				imprime(*rua, "rua");
				for(i = cont; i > 1; i--){	
				//Ao termino desse for, todos os carros que estavam na frente do carro retirado voltam pra alameda, e a rua direita volta a ficar vazia.
					aux_al = *alameda;
					*alameda = *rua;
					aux_rua = *rua;
					*rua = aux_rua->prox;
					(*alameda)->prox = aux_al;
				}
				printf(".\n.\n.\nOs carros manobrados para a saida do carro de placa '%d' voltaram para a alameda."
				"\n--------------------------------------------------------\n", valor);
				imprime(*alameda, "alameda");
				imprime(*rua, "rua");
			}
		}
	}
}
