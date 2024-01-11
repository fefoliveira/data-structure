//Insercao e impressao de arvore BST (arvore binaria de busa):

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arvore{
	int data;
	struct arvore *dir, *esq;
}tree;

int ask_for_value(char *string);
void bst_insert(tree **start, int valor);
void search_null_bst(tree *root, int valor, tree **aux);
void pre_order_print(tree *root);	
void post_order_print(tree *root);
void symmetric_order_print(tree *root);

int main(){
	tree *root = NULL;
	bool repete = true;
	int escolha, valor;

	while(repete){
		printf("Controle de arvore binaria:"
		"\n01 - Inserir"
		"\n02 - Imprimir (pre-ordem)"
		"\n03 - Imprimir (pos-ordem)"
		"\n04 - Imprimir (ordem simetrica)"
		"\n05 - Finalizar o programa"
		"\nSua escolha: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 5){
			printf("Invalido! Insira novamente sua escolha: ");	
			scanf("%d", &escolha);
		}
		switch(escolha){
			case 1:
				valor = ask_for_value("Digite o valor que deseja inserir na arvore: ");
				bst_insert(&root, valor);
				break;
			case 2:
				system("cls||clear");
				printf("Valor:\t\tEsquerda:\t\t\tDireita:\t\t\tAtual:\n");
				pre_order_print(root);
				break;
			case 3:
				system("cls||clear");
				printf("Valor:\t\tEsquerda:\t\t\tDireita:\t\t\tAtual:\n");
				post_order_print(root);
				break;
			case 4:
				system("cls||clear");
				printf("Valor:\t\tEsquerda:\t\t\tDireita:\t\t\tAtual:\n");
				symmetric_order_print(root);
				break;
			case 5:
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

void bst_insert(tree **root, int valor){
	tree *novo = (tree*)malloc(sizeof(tree)), *aux;
	if(novo == NULL)
		printf("\nMemoria insuficiente!");
	else{
		novo->data = valor;
		if(*root == NULL){	//Arvore vazia;
			novo->dir = NULL;
			novo->esq = NULL;
			*root = novo;
		}
		else{	//Arvore que ja tem elementos;
			search_null_bst(*root, valor, &aux);
			if(valor >= aux->data)
				aux->dir = novo;
			else
				aux->esq = novo;
		}
		printf("Valor inserido na arvore com sucesso!\n\n");
	}
}

void search_null_bst(tree *root, int valor, tree **aux){	//Altera o ponteiro aux para que quando a recursao acabar, reste o endereco de memoria apropriado para a insercao
	if(root){	//A varivavel 'root' esta sendo usado pois, com essa passagem de parametro, seu valor original na funcao 'bst_insert' nao e alterado
		*aux = root;
		if(valor > root->data)
			root = root->dir;
		else
			root = root->esq;
		search_null_bst(root, valor, aux);
	}
}

void pre_order_print(tree *root){
	if(root){
		printf("%d\t\t%p\t\t%p\t\t%p\n", root->data, (void *)root->esq, (void *)root->dir, (void *)root);
		pre_order_print(root->esq);
		pre_order_print(root->dir);
	}
}

void post_order_print(tree *root){
	if(root){
		post_order_print(root->esq);
		post_order_print(root->dir);
		printf("%d\t\t%p\t\t%p\t\t%p\n", root->data, (void *)root->esq, (void *)root->dir, (void *)root);
	}
}

void symmetric_order_print(tree *root){
    if(root){
		symmetric_order_print(root->esq);
		printf("%d\t\t%p\t\t%p\t\t%p\n", root->data, (void *)root->esq, (void *)root->dir, (void *)root);
		symmetric_order_print(root->dir);
	}
}