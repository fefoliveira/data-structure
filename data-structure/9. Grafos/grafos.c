#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct vertice{
    int destino;
    struct vertice *prox;
} vertex;

typedef struct grafo{
    int vertices;
    vertex **lista_adj;
} graph;

int ask_for_value(char *string);
graph *create_graph(int num_vertices);
vertex *create_vertex(int destino);
void insert_edge(graph *grafo, int origem, int destino);
void imprimir_grafo_LA(graph *grafo);

int main(){
    vertex *start = NULL;
    bool repete = true;
    int escolha, num_vertice, origem, destino;
    
	//Criacao de grafo com 'n' vertices"	                                => Exercicio (a), pagina 29 do PDF
	num_vertice = ask_for_value("Controle de grafos:\nInsira o numero de vertices que voce deseja no grafo: ");
	graph *grafo = create_graph(num_vertice);
	printf("Grafo criado com sucesso!\n\n");
	while(repete){
        printf("Controle de grafos:" 
		"\n01 - Inserir aresta"//         			 					    => Exercicio (b), pagina 29 do PDF
		"\n02 - Imprimir grafo (Lista de adjacencia)"
		//"\n03 - Imprimir grafo (percursao em largura/amplitude (BFS))"	=> Ainda nao implementado
		//"\n04 - Imprimir grafo (percursao em profundidade (DFS))"			=> Ainda nao implementado
		"\n05 - Criar novo grafo e descartar atual"
		"\n06 - Finalizar o programa"
		"\nSua escolha: ");
		scanf("%d", &escolha); 
		while(escolha < 1 || escolha > 5){
			printf("Invalido! Insira novamente sua escolha: ");	
			scanf("%d", &escolha);
		}
		switch(escolha){
			case 1:
				origem = ask_for_value("Insira o vertice de origem: ");
				destino = ask_for_value("Insira o vertice de destino: ");
				insert_edge(grafo, origem, destino);
				break;
			case 2:
				system("cls||clear");
				imprimir_grafo_LA(grafo);
				break;
			case 3:
				system("cls||clear");
				printf("Ainda nao implementado!\n\n");
				break;
			case 4:
				system("cls||clear");
				printf("Ainda nao implementado!\n\n");
				break;
			case 5:
				free(grafo);
				num_vertice = ask_for_value("Insira o novo numero de vertices que voce deseja no grafo: ");
				graph *grafo = create_graph(num_vertice);
				printf("Grafo criado com sucesso!\n");
				break;
            case 6:
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

vertex *create_vertex(int destino){  
    vertex *novo = (vertex*)malloc(sizeof(vertex));
    novo->destino = destino;
    novo->prox = NULL;
	return novo;
}

graph *create_graph(int num_vertices){						//Exercicio (a), pagina 29 do PDF
	graph *grafo = (graph* )malloc(sizeof(graph)); int i;
	grafo->vertices = num_vertices;
	grafo->lista_adj = (vertex*)malloc(num_vertices*sizeof(vertex));
	for(i = 0; i < num_vertices; i++){
		grafo->lista_adj[i] = NULL;
	}
	return grafo;
}

void insert_edge(graph *grafo, int origem, int destino){	//Exercicio (b), pagina 29 do PDF
	vertex *novo = create_vertex(destino);
	novo->prox = grafo->lista_adj[origem];
	grafo->lista_adj[origem] = novo;
}

void imprimir_grafo_LA(graph *grafo){
	int i;
    for(i = 0; i < grafo->vertices; ++i){
        vertex *atual = grafo->lista_adj[i];
        printf("Lista de adjacencias do vertice %d\n", i);
        while(atual){
            printf(" -> %d", atual->destino);
            atual = atual->prox;
        }
        printf("\n");
    }
}
