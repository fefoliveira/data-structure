// Os grafos possuem seus vertices numerados de 1 a n, sendo n o numero de vertices do grafo.
// Os grafos sao constituidos por arestas nao direcionadas.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct vertice{
    int destino;
    struct vertice *prox;
} vertex;

typedef struct grafo{
    int vertices;
	bool *visitado;
    vertex **lista_adj;
} graph;

int ask_for_value(char *string);
graph *create_graph(int num_vertices);
void insert_edge(graph *grafo, int origem, int destino);
vertex *create_vertex(int destino);
void imprimir_grafo_LA(graph *grafo);
void DFS(graph* grafo, int vertice);
void free_visitados(graph *grafo);

int main(){
    bool repete = true;
    int escolha, num_vertice, origem, destino, vertice_inicio;
                                   
	num_vertice = ask_for_value("Controle de grafos:\nInsira o numero de vertices que voce deseja no grafo: ");
	graph *grafo = create_graph(num_vertice);
	printf("Grafo criado com sucesso!\n\n");
	while(repete){
        printf("Controle de grafos:" 
		"\n01 - Inserir aresta"
		"\n02 - Imprimir grafo (Lista de adjacencia)"
		"\n03 - Busca em profundidade (DFS)"			
		"\n04 - Finalizar o programa"
		"\nSua escolha: ");
		scanf("%d", &escolha); 
		while(escolha < 1 || escolha > 4)
			escolha = ask_for_value("Invalido! Insira novamente sua escolha: ");
		switch(escolha){
			case 1:
				origem = ask_for_value("Insira o vertice de origem: ");
				while(origem < 1 || origem > num_vertice)
					origem = ask_for_value("Invalido! Insira novamente o vertice de origem: ");
				destino = ask_for_value("Insira o vertice de destino: ");
				while(destino < 1 || destino > num_vertice)
					destino = ask_for_value("Invalido! Insira novamente o vertice de destino: ");
				insert_edge(grafo, origem, destino);
				break;
			case 2:
				system("cls||clear");
				imprimir_grafo_LA(grafo);
				printf("-----------------------------------\n\n");
				break;
			case 3:
				system("cls||clear");
				free_visitados(grafo);
				vertice_inicio = ask_for_value("Insira o vertice de inicio para a busca por profundidade (DFS): ");
				while(vertice_inicio < 1 || vertice_inicio > num_vertice)
					vertice_inicio = ask_for_value("Invalido! Insira novamente o vertice de inicio: ");
				printf("-----------------------------------\n");
				DFS(grafo, vertice_inicio);
				printf("\n\n");
				break;
            case 4:
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

graph *create_graph(int num_vertices){						
	graph *grafo = (graph*)malloc(sizeof(graph)); int i;
	grafo->vertices = num_vertices+1;
	grafo->lista_adj = (vertex**)malloc(num_vertices*sizeof(vertex));
	for(i = 1; i < num_vertices; i++){
		grafo->lista_adj[i] = NULL;
	}
	grafo->visitado = (bool*)malloc(num_vertices * sizeof(bool));
	for (i = 1; i < num_vertices; i++) {
		grafo->visitado[i] = false;
	}
	return grafo;
}

void insert_edge(graph *grafo, int origem, int destino){	
	vertex *novo_1 = create_vertex(destino), *novo_2 = create_vertex(origem);
	novo_1->prox = grafo->lista_adj[origem];
	grafo->lista_adj[origem] = novo_1;
	novo_2->prox = grafo->lista_adj[destino];
	grafo->lista_adj[destino] = novo_2;
}

vertex *create_vertex(int destino){  
    vertex *novo = (vertex*)malloc(sizeof(vertex));
    novo->destino = destino;
    novo->prox = NULL;
	return novo;
}

void imprimir_grafo_LA(graph *grafo){
	int i;
    for(i = 1; i < grafo->vertices; ++i){
        vertex *atual = grafo->lista_adj[i];
        printf("Lista de adjacencias do vertice %d\n", i);
        while(atual){
            printf(" -> %d", atual->destino);
            atual = atual->prox;
        }
        printf("\n");
    }
}

void DFS(graph *grafo, int vertice){
    printf("DFS a partir do vertice %d: ", vertice);
    grafo->visitado[vertice] = true;
    printf("%d\n", vertice);
    vertex *atual = grafo->lista_adj[vertice];
    while(atual){
        int destino = atual->destino;
        if(!grafo->visitado[destino])
            DFS(grafo, destino);
        atual = atual->prox;
    }
}

void free_visitados(graph *grafo){
	int i;
	for(i = 1; i < grafo->vertices; ++i){
		grafo->visitado[i] = 0;
	}
}