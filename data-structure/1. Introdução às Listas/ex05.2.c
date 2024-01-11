/*
5.	Uma pizzaria precisa cadastrar produtos, clientes e fazer o controle de vendas. 
É preciso ter o cadastro de produto-pizza (código, nome da pizza, preço), um cadastro de cliente 
(código, nome, endereço) e um cadastro de venda (código da pizza e código do cliente, qtd de pizza, valor pago).

	Faça um menu para:  Gravar dados das pizzas / 
		Gravar dados dos clientes /
	    Gravar venda
	    Ler dados das pizzas
	    Ler dados dos clientes
	    Ler vendas

	a.	Grave os dados em arquivos.
	b.	Faça a leitura dos arquivos
	c.	Ao final do dia, imprimir a quantidade de pizzas vendidas e o valor total recebido.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct produto{
	int codigo;
	char nome[255];
	float preco;
}pizzas;

typedef struct comprador{
	int codigo;
	char nome[255], endereco[255];
}clientes;

typedef struct mercadoria{
	int codigo_pizza, codigo_cliente, qtd_pizza;
	float valor_pago;
}vendas;

void grava_pizza(pizzas *pizza);
void grava_cliente(clientes *cliente);
void grava_venda(vendas *venda);
void ler_pizza();
void ler_cliente();
void ler_venda();
void limpa_buffer();

int main(){
	bool repete = true;
	int escolha, cont_venda = 0;
	pizzas pizza;
	clientes cliente;
	vendas venda;
	
	while(repete){
		printf("Sistema de pizzaria:"
		"\n1 - Gravar dados das pizzas"
		"\n2 - Gravar dados dos clientes"
		"\n3 - Gravar venda"
		"\n4 - Ler dados das pizzas"
		"\n5 - Ler dados dos clientes"
		"\n6 - Ler vendas"
		"\n7 - Finalizar programa"
		"\nSua opcao: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 7){
			printf("Invalido! Informe uma opcao valida: ");
			scanf("%d", &escolha);
		}
		switch(escolha){
			case 1:
				system("cls");
				printf("Insira o codigo da pizza: ");
				scanf("%d", &pizza.codigo);
				limpa_buffer();
				printf("Insira o nome da pizza: ");
				fgets(pizza.nome, sizeof(pizza.nome), stdin);
				printf("Insira o preco da pizza: ");
				scanf("%f", &pizza.preco);
				grava_pizza(&pizza);
				break;
			case 2:
				system("cls");
				printf("Insira o codigo do cliente: ");
				scanf("%d", &cliente.codigo);
				limpa_buffer();
				printf("Insira o nome do cliente: ");
				fgets(cliente.nome, sizeof(cliente.nome), stdin);
				printf("Insira o endereco do cliente: ");
				fgets(cliente.nome, sizeof(cliente.nome), stdin);
				grava_cliente(&cliente);
				break;
			case 3:
				cont_venda++;
				system("cls");
				printf("Insira o codigo da pizza vendida: ");
				scanf("%d", &venda.codigo_pizza);
				printf("Insira o codigo do cliente comprador: ");
				scanf("%d", &venda.codigo_cliente);
				printf("Insira o qtd de pizza vendida: ");
				scanf("%d", &venda.qtd_pizza);
				printf("Insira o valor pago na compra: ");
				scanf("%f", &venda.valor_pago);
				grava_venda(&venda);
				break;
			case 4:
				system("cls");
				ler_pizza();
				break;
			case 5:
				system("cls");
				ler_cliente();
				break;
			case 6:
				system("cls");
				ler_venda();
				break;
			case 7:
				system("cls");
				printf("Foram vendidas um total de %d pizzas hoje.\n\nFinalizando o programa...", cont_venda);
				repete = false;
				break;
		}
	}
}

void grava_pizza(pizzas *pizza){
	FILE *arq;
	arq = fopen("ex5_pizzas.txt", "a+");
	if(arq){
		fprintf(arq, "---------------------------------\ncodigo: %d\n", pizza->codigo);
		fprintf(arq, "nome: %s", pizza->nome);
		fprintf(arq, "preco: %.2f\n---------------------------------\n\n", pizza->preco);
		fclose(arq);
		printf("\nPizza gravada com sucesso!\n\n");
	}
	else{
		system("cls");
		printf("Ocorreu algum problema ao tentar criar ou editar o arquivo.\n\n");
	}
}

void grava_cliente(clientes *cliente){
	FILE *arq;
	arq = fopen("ex5_clientes.txt", "a+");
	if(arq){
		fprintf(arq, "---------------------------------\ncodigo do cliente: %d\n", cliente->codigo);
		fprintf(arq, "nome: %s", cliente->nome);
		fprintf(arq, "endereco: %s\n---------------------------------\n\n", cliente->endereco);
		fclose(arq);
		printf("\nCliente gravado com sucesso!\n\n");
	}
	else{
		system("cls");
		printf("Ocorreu algum problema ao tentar criar ou editar o arquivo.\n\n");
	}
}

void grava_venda(vendas *venda){
	vendas *aux = venda;
	FILE *arq;
	arq = fopen("ex5_vendas.txt", "a+");
	if(arq){
		fprintf(arq, "---------------------------------\ncodigo da pizza: %d\n", venda->codigo_pizza);
		fprintf(arq, "codigo do cliente: %d\n", venda->codigo_cliente);
		fprintf(arq, "qtd de pizza: %d\n", venda->qtd_pizza);
		fprintf(arq, "valor pago: %.2f\n---------------------------------\n\n", venda->valor_pago);
		fclose(arq);
		printf("\nVenda gravada com sucesso!\n\n");
	}
	else{
		system("cls");
		printf("Ocorreu algum problema ao tentar criar ou editar o arquivo.\n\n");
	}
}

void ler_pizza(){
	FILE *arq;
	arq = fopen("ex5_pizzas.txt", "r");
	char carac;
	if(arq){
		while((carac = fgetc(arq)) != EOF)
			putchar(carac);
		printf("\n");	
	}
	else{
		system("cls");
		printf("Ocorreu algum problema ao tentar criar ou editar o arquivo.\n\n");
	}
	printf("\n");
	fclose(arq);
}

void ler_cliente(){
	FILE *arq;
	arq = fopen("ex5_clientes.txt", "r");
	char carac;
	if(arq){
		while((carac = fgetc(arq)) != EOF)
			putchar(carac);
		printf("\n");	
	}
	else{
		system("cls");
		printf("Ocorreu algum problema ao tentar criar ou editar o arquivo.\n\n");
	}
	printf("\n");
	fclose(arq);
}

void ler_venda(){
	FILE *arq;
	arq = fopen("ex5_vendas.txt", "r");
	char carac;
	if(arq){
		while((carac = fgetc(arq)) != EOF)
			putchar(carac);
		printf("\n");	
	}
	else{
		system("cls");
		printf("Ocorreu algum problema ao tentar criar ou editar o arquivo.\n\n");
	}
	fclose(arq);
}

void limpa_buffer(){
	int aux;
	while(aux != '\n' && aux != EOF){
		aux = getchar();
	}
}

