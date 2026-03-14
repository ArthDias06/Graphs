//Perguntas: dois vértices podem ter mais de uma aresta entre si?
//retornar a matriz é retornar a matrix na main ou prinatr ela para o usuário?
//A matriz começa como -1, quando colocar um uma aresta ela cresce em um? Então fica com 0 quando dois vértices estiverem ligados?

#include graph.h

struct knot_{
    int vertice;
    EDGE* edges;
    int numEdge;
};

struct edge_{
    int value;
    KNOT* knot;
};

struct graph_{
    int** matrix; //Matriz de adjacência
    //Possso ter nós não conectados a nenhum outro vértice
    KNOT* knots;
    int verticeQuant;
};

GRAPH* myGraph(int N){
    GRAPH* graph = malloc(sizeof(GRAPH));
    if(graph == NULL){
        printf("Erro ao criar grafo!");
        return NULL;
    }
    graph->matrix = malloc(sizeof(int*) * N);
    if(graph->matrix == NULL){
        free(graph);
        graph = NULL;
        return NULL;
    }
    graph->knots = malloc(sizeof(KNOT)*N);
    if(graph->knots == NULL){
        free(graph->matrix);
        graph->matrix = NULL;
        free(graph);
        graph = NULL;
        return NULL;
    }
    int i;
    for(i = 0; i < N; i++){
        graph->matrix[i] = malloc(sizeof(int) * N);
        if(graph->matrix[i] == NULL){
            for(int j = 0; j<i; j++){
                free(graph->matrix[j]);
                graph->matrix = NULL;
            }
            free(graph->matrix);
            graph->matrix = NULL;
            free(graph->knots);
            graph->knots = NULL;
            free(graph);
            graph = NULL;
            return NULL;
        }
        for(int j = 0; j < N; j++){
            graph->matrix[i][j] = -1;
        }
        graph->knots[i].vertice = i+1;
        graph->knots[i].edges = NULL;
        graph->knots[i].numEdge = 0;
    }
    graph->verticeQuant = i;
    return graph;
}

/*int** adjacencyMatrix(GRAPH* graph){
    if(graph == NULL){
        return NULL;
    }
    return graph->matrix;
}*/

void adjacencyMatrix(GRAPH* graph){
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
    if(graph->matrix[vert1][vert2] > -1){
        return true;
    }
    return false;
}

void addEdge(GRAPH* graph, int edge, int vert1, int vert2){
    if(graph == NULL){
        return;
    }
    //Verifica se já tem a aresta
    /*if(graph->matrix[vert1][vert2] > -1){
        return;
    }*/
    graph->matrix[vert1][vert2]++;
    graph->matrix[vert2][vert1]++;
    if(graph->knots[vert1].edges == NULL){
        graph->knots[vert1].edges = malloc(sizeof(EDGE));
        graph->knots[vert1].numEdge++;
    }
    else{
        realloc(graph->knots[vert1].edges, sizeof(EDGE)*(++(graph->knots[vert1].numEdge)));
    }
    if(graph->knots[vert1].edges == NULL){
        return;
    }
    graph->knots[vert1].edges[numEdge-1].value = edge;
    graph->knots[vert1].edges[numEdge-1].knot = &(graph->knots[vert2]);

    if(graph->knots[vert2].edges == NULL){
        graph->knots[vert2].edges = malloc(sizeof(EDGE));
        graph->knots[vert1].numEdge++;
    }
    else{
        realloc(graph->knots[vert2].edges, sizeof(EDGE)*(++(graph->knots[vert2].numEdge)));
    }
    if(graph->knots[vert2].edges == NULL){
        return;
    }
    graph->knots[vert2].edges[numEdge-1].value = edge;
    grapg->knots[vert2].edges[numEdge-1].knot = &(graph->knots[vert1]);
}


//Muda tudo se puder ter mais uma aresta a cada 2 vértices
int* neighbors(GRAPH* graph, int vert){
    if(graph == NULL){
        return NULL;
    }
    int* neigh = malloc(sizeof(int) * graph->knots[vert].numEdge);
    for(int i = 0; i < graph->knots[vert].numEdge; i++){
        neigh[i] = graph->knots[vert].edges[i].knot->vertice;
    }
    return neigh;
}