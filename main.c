//Arthur de Castro Dias - 1685302
//Pedro Tiago Biffi - 16
//Gabriel Carraro Salzedas - 16
//Guilherme Cavalcanti de Santana - 15456556

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct graph_{
    int** matrix; //Matriz de adjacência
    int numVert; //Quantidade de vértices do grafo
}GRAPH;

int* _neighbors_without_print (GRAPH*, int); // FUNÇÃO INTERNA



GRAPH* myGraph(int N){
    GRAPH* graph = malloc(sizeof(GRAPH));
    if(graph == NULL){
        printf("Erro ao alocar memória para o grafo!\n");
        return NULL;
    }
    if(N < 1){
        printf("Grafo com número inválido de vértices!\n");
        return NULL;
    }
    graph->numVert = N;
    graph->matrix = malloc(sizeof(int*) * N);
    if(graph->matrix == NULL){
        free(graph);
        graph = NULL;
        printf("Erro ao alocar matriz!\n");
        return NULL;
    }
    for(int i = 0; i < N; i++){
        graph->matrix[i] = malloc(sizeof(int) * N);
        if(graph->matrix[i] == NULL){
            for(int j = 0; j<i; j++){
                free(graph->matrix[j]);
                graph->matrix = NULL;
            }
            free(graph->matrix);
            graph->matrix = NULL;
            free(graph);
            graph = NULL;
            return NULL;
        }
        //Preenche a matriz com -1
        for(int j = 0; j < N; j++){
            graph->matrix[i][j] = -1;
        }
    }
    return graph;
}

//Função para retorno da matriz de adjacência para o  usuário
int** adjacencyMatrix(GRAPH* graph){
    if(graph == NULL){
        return NULL;
    }
   
   // DEBUG!!!
    
    for(int i = 0; i < graph->numVert; i++){
    	for(int j = 0; j < graph->numVert; j++){
    		printf("%2d ", graph->matrix[i][j]);
    	}
    	printf("\n");
    }
    
    return graph->matrix; // ISSO QUEBRA O INFORMATION HIDING
}

int existEdge(GRAPH* graph, int vert1, int vert2){
    if(graph == NULL){
        return 0;
    }
    if(graph->matrix[vert1-1][vert2-1] != -1){
        return 1;
    }
    return 0;
}

void printInfo(GRAPH* graph){
    if(graph == NULL){
        return;
    }
    printf("V = [");
    for(int i =0; i< graph->numVert; i++){
        if(i+1 != graph->numVert){
            printf("%d, ", i+1);
        }else{
            printf("%d]\n", i+1);
        }
    }
    
    int printaVirgula=0; // a vírgula é imprimida antes da aresta. Por isso, quando imprimir a primeira aresta antes não pode imprimir vírgula
    printf("E = [");
    for(int i = 1; i <= graph->numVert; i++){
        for(int j = 1; j <= i; j++){
            if(existEdge(graph, i, j)){
            
            	if(printaVirgula) printf(", ");
            	printaVirgula = 1;
            	
                printf("(%d, %d)", j, i);
            }
        }
    }
    printf("]\n");
}

int maxNeighbors(GRAPH* graph){
    if(graph == NULL){
        return 0;
    }
    
    int max_vert;
    int max_neigh = 0;
    int* neighbors_temp;
    for(int i = 1; i <= graph->numVert; i++){
        neighbors_temp = _neighbors_without_print(graph, i);
        if(neighbors_temp[0] > max_neigh){ // compara a quantidade de vizinhos desse nó
        	max_neigh = neighbors_temp[0];
        	max_vert = i;
        }
        free(neighbors_temp);
    }
    return max_vert;
}

void addEdge(GRAPH* graph, int vert1, int vert2, int edge){
    if(graph == NULL){
        return;
    }
    if(edge <= 0){
        printf("Aresta com valor inválido!\n");
        return;
    }
    if(vert1 < 1 || vert2 < 1 || vert1 > graph->numVert || vert2 > graph->numVert){
    	printf("Vértices inválidos!\n");
    }
    graph->matrix[vert1-1][vert2-1] = edge;
    graph->matrix[vert2-1][vert1-1] = edge;
}

 int removeEdge(GRAPH* graph, int vert1, int vert2){
    if(graph == NULL || vert1<1 || vert1>graph->numVert || vert1<2 || vert2>graph->numVert){
        return -1;
    }
    //Verifica se já tem a aresta
    if(!existEdge(graph, vert1, vert2)){
        return -1;
    }
    //Tira 1 de vert1 e vert2 pois como o grafo começa com vértice numerado a partir de 1 e a matriz começa a partir de 0
    //Para acessar o índice vert1 vert2 correto, precisamos decrementar em 1.
    graph->matrix[vert1-1][vert2-1] = -1;
    graph->matrix[vert2-1][vert1-1] = -1;
    return 0;
}

int* neighbors(GRAPH* graph, int vert){
    if(graph == NULL || graph->matrix == NULL) return NULL;
	if(vert < 1 || vert > graph->numVert) return NULL;
	
	int conta_vizinhos = 0;
	for(int i=1; i <= graph->numVert; i++){
		if( (graph->matrix)[vert-1][i-1] != -1) conta_vizinhos++;
	}
	
	int* vizinhos = (int*)malloc( (conta_vizinhos) * sizeof(int) );
	
	int index_array = 0;
	for(int i=1; i <= graph->numVert; i++){
		if( graph->matrix[vert-1][i-1] != -1){
			vizinhos[index_array] = i;
			index_array++;
		}
	}
	
	// agora printa os vizinhos
	
	for(int i=1; i<conta_vizinhos; i++){
		if(i != 1) printf(", ");
		printf("%d", vizinhos[i]);
	}
	
	return vizinhos;
}

int* _neighbors_without_print (GRAPH* graph, int vert){ // FUNÇÃO INTERNA
    if(graph == NULL || graph->matrix == NULL) return NULL;
	if(vert < 1 || vert > graph->numVert) return NULL;
	
	int conta_vizinhos = 0;
	for(int i=1; i <= graph->numVert; i++){
		if( (graph->matrix)[vert-1][i-1] != -1) conta_vizinhos++;
	}
	
	int* vizinhos = (int*)malloc( (conta_vizinhos+1) * sizeof(int) );
	vizinhos[0] = conta_vizinhos;
	
	int index_array = 1;
	for(int i=1; i <= graph->numVert; i++){
		if( (graph->matrix)[vert-1][i-1] != -1){
			vizinhos[index_array] = i;
			index_array++;
		}
	}
	
	return vizinhos;
}

void deleteGraph(GRAPH** graph){
    if(graph==NULL){
        return;
    }
    for(int i = 0; i < (*graph)->numVert; i++){
        free((*graph)->matrix[i]);
        (*graph)->matrix[i] = NULL;
    }
    free((*graph)->matrix);
    (*graph)->matrix = NULL;
    free(*graph);
    *graph = NULL;
}

int main(void)
{
    int option;
    int N, x, y, w;
    int res;
    bool print_status = 1;
    GRAPH *G;

	/*
    printf("[0] myGraph\n");
    printf("[1] addEdge\n");
    printf("[2] existEdge\n");
    printf("[3] neighbors\n");
    printf("[4] removeEdge\n");
    printf("[5] printInfo\n");
    printf("[6] deleteGraph\n");
    printf("[7] maxNeighbors\n");
    printf("[8] adjacencyMatrix\n");
    printf("[9] sair\n");
    */
    scanf("%d ", &option);
    do{
        switch (option)
        {
            case 0:
                scanf("%d ", &N);
                G = myGraph(N);
                break;
            case 1: // add_edge
                scanf("%d %d %d ", &x, &y, &w);
                addEdge(G, x, y, w);
                break;
            case 2: // existEdge
                scanf("%d %d ", &x, &y);
                res = existEdge(G, x, y);
                print_status = 0;
                break;
            case 3: // neighbors
                scanf("%d ", &x);
                free(neighbors(G, x));
                break;
            case 4: // removeEdge
                scanf("%d %d ", &x, &y);
                if(removeEdge(G, x, y) == -1){
                    res = -1;
                    print_status = 0;
                }
                break;
            default:
                printf("unrecognized option!\n");
        }
        scanf("%d ", &option);
    }while(option != -1);

    if(option == -1){
        if(print_status)
            printInfo(G);
        else
            printf("%d\n", res);
    }

    deleteGraph(&G);
    return 0;
}