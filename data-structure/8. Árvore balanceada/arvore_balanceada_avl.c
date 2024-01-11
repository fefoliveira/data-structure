/*Exercicios do PDF para entrega em 25/10/2023:
	-> Questoes abordadas: 2, 3, 4 e 5 (da pagina 11 do PDF).*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arvore{
	int data;
	struct arvore *right, *left;
}tree;

int ask_for_value(char *string);
void pre_order_print(tree *root);	
void post_order_print(tree *root);
void symmetric_order_print(tree *root);
void avl_insert(tree **start, int valor);
int balance_factor(tree *knot);
tree *rotate_right(tree *knot_y);
tree *rotate_left(tree *knot_x);
tree *rotate_right_left(tree *knot);
tree *rotate_left_right(tree *knot);
int height_counter(tree *root);
int knot_counter(tree *root);
int leaf_counter(tree *root);
void remove_leaves(tree **root);

int main(){
	tree *root = NULL;
	bool repete = true;
	int escolha, valor, altura, nos, folhas;

	while(repete){
		printf("Controle de arvore binaria balanceada (AVL):"
		"\n01 - Inserir balanceadamente"
		"\n02 - Imprimir (pre-ordem)"
		"\n03 - Imprimir (pos-ordem)"
		"\n04 - Imprimir (ordem simetrica)"
		"\n05 - Conferir a altura"
		"\n06 - Conferir o numero de nos"
		"\n07 - Conferir o numero de folhas"
		"\n08 - Remover todas as folhas da arvore"
		"\n09 - Finalizar o programa"
		"\nSua escolha: ");
		scanf("%d", &escolha);
		while(escolha < 1 || escolha > 9){
			printf("Invalido! Insira novamente sua escolha: ");	
			scanf("%d", &escolha);
		}
		switch(escolha){
			case 1:
				valor = ask_for_value("Digite o valor que deseja inserir na arvore: ");
				avl_insert(&root, valor);
				break;
			case 2:
				system("cls||clear");
				printf("Valor:\t\tEsquerda:\t\t\tDireita:\t\t\tAtual:\n");
				pre_order_print(root);
				printf("\n");
				break;
			case 3:
				system("cls||clear");
				printf("Valor:\t\tEsquerda:\t\t\tDireita:\t\t\tAtual:\n");
				post_order_print(root);
				printf("\n");
				break;
			case 4:
				system("cls||clear");
				printf("Valor:\t\tEsquerda:\t\t\tDireita:\t\t\tAtual:\n");
				symmetric_order_print(root);
				printf("\n");
				break;
			case 5:
				system("cls||clear");
				altura = height_counter(root);
				printf("A altura da arvore e: %d\n\n", altura);
				break;
			case 6:
				system("cls||clear");
				nos = knot_counter(root);
				printf("A arvore tem %d nos.\n\n", nos);
				break;
			case 7:
				system("cls||clear");
				folhas = leaf_counter(root);
				printf("A arvore tem %d folhas.\n\n", folhas);
				break;
			case 8:
				system("cls||clear");
				remove_leaves(&root);
				printf("As folhas foram removidas com sucesso!\n\n");
				break;
			case 9:
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

void pre_order_print(tree *root){
	if(root){
		printf("%d\t\t%p\t\t%p\t\t%p\n", root->data, (void *)root->left, (void *)root->right, (void *)root);
		pre_order_print(root->left);
		pre_order_print(root->right);
	}
}

void post_order_print(tree *root){
	if(root){
		post_order_print(root->left);
		post_order_print(root->right);
		printf("%d\t\t%p\t\t%p\t\t%p\n", root->data, (void *)root->left, (void *)root->right, (void *)root);
	}
}

void symmetric_order_print(tree *root){
    if(root){
		symmetric_order_print(root->left);
		printf("%d\t\t%p\t\t%p\t\t%p\n", root->data, (void *)root->left, (void *)root->right, (void *)root);
		symmetric_order_print(root->right);
	}
}

void avl_insert(tree **root, int valor){
	tree *novo = (tree*)malloc(sizeof(tree)), *aux; int bf;
	if(novo == NULL)
		printf("\nMemoria insuficiente!");
	else{
		novo->data = valor;
		if(*root == NULL){	//Arvore vazia;
		    novo->left = NULL;
		    novo->right = NULL;
			*root = novo;
		}
		//Para arvores que ja possuem elementos:
		else if((*root)->data < (*root)->data)				// Inserir na subárvore esquerda
        	avl_insert(&((*root)->left), (*root)->data);
		else if((*root)->data > (*root)->data)				// Inserir na subárvore direita
        	avl_insert(&((*root)->right), (*root)->data);
		//Balanceamento pos insercao usando rotacoes:
		bf = balance_factor(*root);
		if(bf > 1){									//No desbalanceado a esquerda
			if((*root)->data < (*root)->left->data)
				*root = rotate_right(*root);		//Rotacao LL
			else
				*root = rotate_left_right(*root);	//Rotacao LR
		}
		else if(bf < -1){
			if((*root)->data < (*root)->left->data)
				*root = rotate_left(*root);			//Rotacao RR
			else
				*root = rotate_right_left(*root);	//Rotacao RL
		}
	}
}

int balance_factor(tree *knot){
    if(knot)
    	return height_counter(knot->left) - height_counter(knot->right);
}

tree *rotate_right(tree *knot_y){
    tree *knot_x = knot_y->left;
    tree *T2 = knot_x->right;
    knot_x->right = knot_y;
    knot_y->left = T2;
    return knot_x;
}

tree *rotate_left(tree *knot_x){
    tree *knot_y = knot_x->right;
    tree *T2 = knot_y->left;
    knot_y->left = knot_x;
    knot_x->right = T2;
    return knot_y;
}

tree *rotate_right_left(tree *knot){
    knot->right = rotate_right(knot->right);
    return rotate_left(knot);
}

tree *rotate_left_right(tree *knot){
    knot->left = rotate_left(knot->left);
    return rotate_right(knot);
}

//EXERCICIO 2:
int height_counter(tree *root){
	int left_height, right_height;
	if(root){
        left_height = height_counter(root->left);
        right_height = height_counter(root->right);
        //A altura da arvore e o maximo entre a altura da subarvore esquerda e direita mais 1:
		if(left_height > right_height)
			return left_height + 1;
		else
			return right_height + 1;
    }
}

//EXERCICIO 3:
int knot_counter(tree *root){
	int left_knots, right_knots;
	if(root){
        left_knots = knot_counter(root->left);			// Contagem na esquerda
        right_knots = knot_counter(root->right);		// Contagem na direita
        return left_knots + right_knots + 1;			// 1 (o nó atual) + contagem das subarvores
    }
}

//EXERCICIO 4:
int leaf_counter(tree *root){
	int left_leaves, right_leaves;
	if(root){
		if(root->left == NULL && root->right == NULL)	//Nó atual é uma folha
			return 1;
		else{
			left_leaves = leaf_counter(root->left);		// Contagem nas folhas da esquerda
			right_leaves = leaf_counter(root->right);	// Contagem nas folhas da direita
			return left_leaves + right_leaves;			// Contagem total
		}
	}
}

//EXERCICIO 5:
void remove_leaves(tree **root){
	if(*root){
        if ((*root)->left == NULL && (*root)->right == NULL){	//Folha encontrada
            free(*root);
            *root = NULL;
        } 
		else{
            remove_leaves(&(*root)->left);
            remove_leaves(&(*root)->right);
        }
    }
}
