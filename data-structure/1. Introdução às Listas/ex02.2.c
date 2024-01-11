/*
2.	Faca um codigo em C que permite ao usuario criar uma lista com os seguintes dados: 
CPF usuario, Nome do curso, ano de in�cio. Realize as seguintes operacoes utilizando funcoes:
	a.	Inserir no na lista - final 
	b.	Imprimir a lista 
OBS: Apresente os dados com a seguinte construcao (endereco do no, valores do no, valor do proximo). 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct list{
	char cpf[12], nome[255];
	int ano[3];
	struct list *prox ;
}knot;

void down_insert(knot **start, char *cpf, char *nome, int *ano);
void imprime(knot *start);
bool validacao_cpf(char *cpf);
void limpa_buffer();
bool validacao_dia(int *data);

int main(){
	knot *start = NULL;
	bool repete = true;
	int escolha, ANO[3];
	char CPF[12], NOME[255];
	
	while(repete){
		printf("Controle de usuarios:"
		"\n1 - Inserir usuario"
		"\n2 - Imprimir lista de usuarios"
		"\n3 - Finalizar programa"
		"\nSua escolha: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 3){
			printf("Invalido! Digite uma opcao valida: ");
			scanf("%d", &escolha);
		}
		switch(escolha){
			case 1:
				//---------------------------------------------------------------
				
				printf("\nDigite o CPF do usuario: ");
				scanf("%12s", &CPF);
				limpa_buffer();
				while(!validacao_cpf(CPF)){
					printf("Invalido! Digite novamente o CPF do usuario: ");
					scanf("%12s", &CPF);
					limpa_buffer();
				}
				
				//---------------------------------------------------------------
				
				printf("Digite o Nome do usuario: ");
				gets(NOME);
				
				//---------------------------------------------------------------
				
				printf("Digite a data de nascimento do cliente:");
				printf("\n\tAno: ");
				scanf("%d", &ANO[2]);
				while(ANO[2] < 1900 || ANO[2] > 9999){
					printf("\tInvalido! Digite o ano novamente: ");
					scanf("%d", &ANO[2]);
				}
				printf("\tMes: ");
				scanf("%d", &ANO[1]);
				while(ANO[1] < 1 || ANO[1] > 12){
					printf("\tInvalido! Digite o mes novamente: ");
					scanf("%d", &ANO[1]);
				}
				printf("\tDia: ");
				scanf("%d", &ANO[0]);
				while(validacao_dia(ANO) == false){
					printf("\tInvalido! Digite o dia novamente: ");
					scanf("%d", &ANO[0]);
				}
				printf("\n");
				
				//---------------------------------------------------------------
				
				down_insert(&start, CPF, NOME, ANO);
				system("cls");
				break;
			case 2:
				system("cls");
				imprime(start);
				break;
			case 3:
				repete = false;
				system("cls");
				printf("Finalizando...");
				break;
		}
	}
}

void down_insert(knot **start, char *cpf, char *nome, int *ano){
	knot *novo, *aux;
	novo = (knot*)malloc(sizeof(knot));
	if(novo == NULL)
		printf("\nMemoria insuficiente!");
	else{
		novo->prox = NULL;
		strcpy(novo->cpf, cpf);
		strcpy(novo->nome, nome);
		novo->ano[0] = ano[0];
		novo->ano[1] = ano[1];
		novo->ano[2] = ano[2];
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
	knot *aux = start;
	if(aux == NULL)
		printf("\nA lista esta vazia.\n");
	else{
		while(aux != NULL){
			printf("\n----------------------------\nEndereco: %p \nCPF: %d \nNome: %s \nAno de inicio: %d/%d/%d \nProximo: %p\n----------------------------\n", (void *)aux, aux->cpf, aux->nome, aux->ano[0], aux->ano[1], aux->ano[2], (void *)aux->prox);
			aux = aux->prox;
		}
	}
	printf("\n");
}

bool validacao_cpf(char *cpf){
	int i, j, cont, d1 = 0, d1_resto, d2 = 0, d2_resto;
	//Verifica se o CPF tem 11 digitos:
	if(strlen(cpf) != 11)
		return false;
	//Verifica se o CPF tem todos os digitos iguais:
	for(i = 0, j = 1; j < 11; i++, j++){
		if(cpf[i] == cpf[j]){
			cont++;
		}
	}
	if(cont >= 10)
		return false;
	//Calculo do primeiro digito verificador:
	for(i = 8, j = 2; i >= 0; i--, j++){
		d1 += (cpf[i]-'0') * j;
	}
	d1_resto = d1%11;
	if(d1_resto < 2)
		d1 = 0;
	else
		d1 = 11-d1_resto;
	if((cpf[9]-'0') != d1)
		return false; 
	//Calculo do segundo digito verificador:
	for(i = 9, j = 2; i > 0; i--, j++){
		d2 += (cpf[i]-'0') * j;
	}
	d2_resto = d2%11;
	if(d2_resto < 2)
		d2 = 0;
	else
		d2 = 11-d2_resto;
	if((cpf[10]-'0') != d2)
		return false;
	return true;
}

void limpa_buffer(){
	int aux;
	while(aux != '\n' && aux != EOF){
		aux = getchar();
	}
}

bool validacao_dia(int *data){
	//Verifica o intervalo de dias padrão:
	if(data[0] < 1 || data[0] > 31)
		return false;
	//Verifica se o ano eh bissexto e se 29/02 é possível:
	if(data[1] == 2 && data[0] == 29){
		if((data[2] % 4 == 0 && data[2] % 100 != 0) || data[2] % 400 == 0){
			return true;
		}
		else
			return false;
	}
	//Impede 30/02 ou 31/02:
	if(data[1] == 2 && (data[0] == 30 || data[0] == 31))
		return false;
	//Impede o dia 31 em meses que nao o possuem:
	if((data[1] == 4 || data[1] == 6 || data[1] == 9 || data[1] == 11) && data[0] == 31)
		return false;
	return true;
}
