#ifndef GRAPH_H
    #define GRAPH_H
    #include<stdio.h>
    #include<stdlib.h>
    #include<boolean.h>

    typedef struct graph_ GRAPH;
    typedef struct knot_ KNOT;
    typedef struct edge_ EDGE;

    GRAPH* myGraph(int); //feita não revisada
    void addEdge(GRAPH*, int, int, int); //feita não revisada
    bool existEdge(GRAPH*, int, int); //feita não revisada
    int* neighbors(GRAPH*, int); //feita não revisada
    void removeEdge(GRAPH*, int, int);//feita não revisada
    void printInfo(GRAPH*); //feita não revisada
    void deleteGraph(GRAPH**); //feita não revisada
    int* maxNeighbors(GRAPH*, int);
    void adjacencyMatrix(GRAPH*); //feita não revisadas
#endif