#include "graph.h"

struct graph_{
    int** matrix; //Matriz de adjacência
    int numVert; //Quantidade de vértices do grafo
};

GRAPH* myGraph(int N){
    GRAPH* graph = malloc(sizeof(GRAPH));
    if(graph == NULL){
        printf("Erro ao criar grafo!");
        return NULL;
    }
    if(N < 1){
        printf("Grafo com número inválido de vértices!");
    }
    graph->numVert = N;
    graph->matrix = malloc(sizeof(int*) * N);
    if(graph->matrix == NULL){
        free(graph);
        graph = NULL;
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
    return graph->matrix;
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
    printf("E = [");
    for(int i = 1; i < graph->numVert; i++){
        for(int j = i; j <= graph->numVert; j++){
            if(existEdge(graph, i, j) && i != graph->numVert-1){
                printf("(%d, %d), ", i, j);
            }
            else if(existEdge(graph, i, j)){
                printf("(%d, %d)]", i, j);
            }
        }
    }
}

//Precisa atualizar para caso haja mais de um vértice como max!
int maxNeighbors(GRAPH* graph){
    if(graph == NULL){
        return 0;
    }
    int max = 0;
    int n;
    for(int i = 0; i < graph->numVert; i++){
        n = sizeof(neighbors(graph, i+1))/sizeof(int); 
        if(n > max){
            max = i+1;
        }
    }
    return max;
}

bool existEdge(GRAPH* graph, int vert1, int vert2){
    if(graph == NULL){
        return false;
    }
    if(graph->matrix[vert1-1][vert2-1] != -1){
        return true;
    }
    return false;
}

void addEdge(GRAPH* graph, int vert1, int vert2, int edge){
    if(graph == NULL){
        return;
    }
    if(edge <= 0){
        printf("Aresta com valor inválido!");
        return;
    }
    graph->matrix[vert1-1][vert2-1] = edge;
    graph->matrix[vert2-1][vert1-1] = edge;
}

void removeEdge(GRAPH* graph, int vert1, int vert2){
    if(graph == NULL){
        return;
    }
    //Verifica se já tem a aresta
    if(!existEdge(graph, vert1, vert2)){
        printf("Aresta não existente!");
        return;
    }
    //Tira 1 de vert1 e vert2 pois como o grafo começa com vértice numerado a partir de 1 e a matriz começa a partir de 0
    //Para acessar o índice vert1 vert2 correto, precisamos decrementar em 1.
    graph->matrix[vert1-1][vert2-1] = -1;
    graph->matrix[vert2-1][vert1-1] = -1;
}

int* neighbors(GRAPH* graph, int vert){
    if(graph == NULL){
        return NULL;
    }
    int cont=0;
    int neigh[graph->numVert];
    neigh[0] = 0;
    for(int i = 0; i < graph->numVert; i++){
        if(vert == i)
            continue;
        if(existEdge(graph, vert, i+1)){
            neigh[cont] = i;
            cont++;
        }
    }
    if(cont == 0){
        cont++;
    }
    int *neigh2 = malloc(sizeof(int) * cont);
    //Realloc para estáticos
    for(int i = 0; i < cont; i++){
        neigh2[i] = neigh[i];
    }
    //neigh deixa de existir ao final
    return neigh2;
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