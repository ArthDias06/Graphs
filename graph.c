//Perguntas: dois vértices podem ter mais de uma aresta entre si?
//retornar a matriz é retornar a matrix na main ou prinatr ela para o usuário?
//A matriz começa como -1, quando colocar um uma aresta ela cresce em um? Então fica com 0 quando dois vértices estiverem ligados?

#include graph.h
struct graph_{
    int** matrix; //Matriz de adjacência
    int numVert;
};

GRAPH* myGraph(int N){
    GRAPH* graph = malloc(sizeof(GRAPH));
    if(graph == NULL){
        printf("Erro ao criar grafo!");
        return NULL;
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
        for(int j = 0; j < N; j++){
            graph->matrix[i][j] = -1;
        }
    }
    return graph;
}

int** adjacencyMatrix(GRAPH* graph){
    if(graph == NULL){
        return NULL;
    }
    return graph->matrix;
}

void printInfo(GRAPH* graph){
    if(graph == NULL){
        return 0;
    }
    for(int i =0; i< graph->verticeQuant; i++){
        printf(" \t%d", i);
    }
    for(int i = 0; i < graph->verticeQuant; i++){
        printf("%d", i);
        for(int j = 0; j < graph->verticeQuant; j++){
            printf("\t%d", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

//Precisa atualizar para caso haja mais de um vértice como max!
int maxNeighbors(GRAPH* graph){
    if(graph == NULL){
        return 0;
    }
    int max = 0;
    for(int i = 0; i < graph->verticeQuant; i++){
        for(int j = 0; j < graph->verticeQuant; j++){
            if(graph->matrix[i][j] > max)
                max = graph->matrix[i][j];
        }
    }
    return max;
}

bool existEdge(GRAPH* graph, int vert1, int vert2){
    if(graph == NULL){
        return false;
    }
    if(graph->matrix[vert1][vert2] != -1){
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
    //Verifica se já tem a aresta
    if(existEdge(graph, vert1, vert2)){
        printf("resta já existente!");
        return;
    }
    graph->matrix[vert1][vert2] = edge;
    graph->matrix[vert2][vert1] = edge;
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
    graph->matrix[vert1][vert2] = -1;
    graph->matrix[vert2][vert1] = -1;
}

int* neighbors(GRAPH* graph, int vert){
    if(graph == NULL){
        return NULL;
    }
    int cont=0;
    int* neigh = malloc(sizeof(int)*graph->numVert);
    if(neigh == NULL){
        return NULL;
    }
    for(int i = 0; i < graph->numVert; i++){
        if(vert == i)
            continue;
        if(existEdge(graph, vert, i)){
            neigh[cont] = i;
            cont++;
        }
    }
    realloc(neigh, sizeof(int)*(cont-1));
    return neigh;
}

void deleteGraph(GRAPH** graph){
    if(graph==NULL){
        return;
    }
    for(int i = 0; i < graph->numVert; i++)[
        free((*graph)->matrix[i]);
        (*graph)->matrix[i] = NULL;
    ]
    free((*graph)->matrix);
    (*graph)->matrix = NULL;
    free(*graph);
    *graph = NULL;
}