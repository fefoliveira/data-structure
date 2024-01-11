/*
1.	Suponha que em um laboratório, cada paciente quando chega escolhe uma senha para atendimento. 
Essa senha pode ser para realizar exames de sangue ou exames de imagem. 
Quando um paciente é chamado pelo atendente ele deve informar o número da senha, seu nome, o plano de saúde(Unimed/Ipê)
e o tipo de exame a fazer(sangue/imagem). Ao término do dia, cada atendente gera a listagem dos pacientes que ele atendeu. 
Apresente:
	a)	A listagem dos pacientes atendidos
	b)	A quantidade de pacientes atendidos que possuem Unimed.
	c)	A quantidade de pacientes atendidos para realizar exames de Sangue.
OBS: Apresente os dados com a seguinte construção (endereço do nó, valores do nó, valor do próximo). 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct list{
	int senha;
	char nome[255], plano[6], exame[6];
	struct list *prox ;
}knot;

void add_paciente(knot **start, int *cont_uni, int *cont_sang);
void imprime(knot *start);
bool confere_senha(knot *start, int senha);

int main(){
	knot *start = NULL;
	int cont_unimed = 0, cont_sangue = 0, escolha;
	bool repete = true, repete2;
	
	while(repete){
		printf("Controle de pacientes:"
		"\n1 - Adicionar novo paciente"
		"\n2 - Listar pacientes atendidos"
		"\n3 - Listar quantidade de pacientes atendidos que possuem Unimed"
		"\n4 - Listar quantidade de pacientes atendidos para realizar exames de sangue"
		"\n5 - Finalizar o programa"
		"\nSua opcao: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 5){
			printf("Invalido! Informe uma opcao valida: ");
			scanf("%d", &escolha);
		}
		switch(escolha){
			case 1:
				system("cls");
				repete2 = true;
				while(repete2){
					add_paciente(&start, &cont_unimed, &cont_sangue);
					printf("\nDeseja cadastrar mais um paciente?"
					"\n1 - Sim"
					"\n0 - Nao"
					"\nSua opcao: ");
					scanf("%d", &escolha);
					while(escolha < 0 || escolha > 1){
						printf("Invalido! Informe uma opcao valida: ");
						scanf("%d", &escolha);
					}
					printf("\n\n");
					if(escolha == 0)
						repete2 = false;
				}
				system("cls");
				break;
			case 2:
				system("cls");
				imprime(start);
				break;
			case 3:
				if(cont_unimed == 0)
					printf("\nAinda nenhum paciente que possua plano de saude Unimed foi atendido hoje.\n\n");
				else
					printf("\nA quantidade de pacientes atendidos hoje que possuem Unimed foi de: %d\n\n", cont_unimed);
				break;	
			case 4:
				if(cont_sangue == 0)
					printf("\nAinda nenhum paciente realizou exame de sangue hoje.\n\n");
				else
					printf("\nA quantidade de pacientes atendidos hoje que realizaram exame de sangue foi de: %d\n\n", cont_sangue);				
				break;
			case 5:
				system("cls");
				printf("Finalizando...");
				repete = false;
				break;
		}
	}
}

void add_paciente(knot **start, int *cont_uni, int *cont_sang){
	knot *novo; 
	novo = (knot*)malloc(sizeof(knot));
	int plano, *cont_unimed = cont_uni, exame, *cont_sangue = cont_sang;
	char unimed[] = "Unimed", ipe[] = "Ipe", sangue[] = "Sangue", imagem[] = "Imagem";
	bool confere;
	
	if(novo == NULL)
		printf("\nMemoria insuficiente!");
	else{
		//---------------------------------------------------------------	
		
		printf("Informe a senha do paciente: ");
		scanf("%d", novo->senha);
		while(novo->senha < 0 || confere == false){
			printf("Invalido! Informe uma senha valida: ");
			scanf("%d", novo->senha);	
			confere = confere_senha;
		}
		
		//---------------------------------------------------------------	
		
		printf("Informe o nome do paciente: ");
		scanf("%s", novo->nome);
		while(strlen(novo->nome) <= 0){
			printf("Invalido! Informe um nome valido: ");
			scanf("%s", novo->nome);
		}
		
		//---------------------------------------------------------------	
		
		printf("Informe o plano de saude do paciente:"
		"\n1 - Unimed"
		"\n2 - Ipe"
		"\nSelecao: ");
		scanf("%d", &plano);
		while(plano < 1 || plano > 2){
			printf("Invalido! Digite novamente sua escolha: ");
			scanf("%d", &plano);
		}
		if(plano == 1){
			strcpy(novo->plano, unimed);
			*cont_unimed++;
		}
		else
			strcpy(novo->plano, ipe);
			
		//---------------------------------------------------------------	
		
		printf("Informe o tipo de exame do paciente:"
		"\n1 - Sangue"
		"\n2 - Imagem"
		"\nSelecao: ");
		scanf("%d", &exame);
		while(exame < 1 || exame > 2){
			printf("Invalido! Digite novamente sua escolha: ");
			scanf("%d", &exame);
		}
		if(exame == 1){
			strcpy(novo->exame, sangue);
			*cont_sangue++;
		}
		else
			strcpy(novo->exame, imagem);
			
		//---------------------------------------------------------------	
		
		if(*start == NULL)
			novo->prox = NULL;
		else
			novo->prox = *start;
		*start = novo;
		
		//---------------------------------------------------------------
	}
}

void imprime(knot *start){
	knot *aux = start;
	if(aux == NULL)
		printf("\nA lista de pacientes esta vazia.\n");
	else{
		while(aux != NULL){
			printf("\nEndereco: %p \nSenha: %d \nNome: %s \nPlano: %s \nExame: %s \nProximo: %p\n------------------------\n", (void *)aux, aux->senha, aux->nome, aux->plano, aux->exame, (void *)aux->prox);
			aux = aux->prox;
		}
	}
	printf("\n\n");
}

bool confere_senha(knot *start, int senha){
	knot *aux = start;
	int password = senha;
	while(aux->prox != NULL){
		if(aux->senha == password)
			return false;
	}
	if(aux->prox == NULL && aux->senha == password)
		return false;
	else
		return true;
}
