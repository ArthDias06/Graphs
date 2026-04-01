//Arthur de Castro Dias - 16855302
//Pedro Tiago Biffi - 1627777
//Gabriel Carraro Salzedas - 1627905
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
    if(graph == NULL || graph->matrix == NULL){
        return NULL;
    }
    
    // Primeiro, precisamos achar os nós desconexos e marcá-los como não printáveis
    bool* marca = (bool*)malloc(sizeof(bool)*graph->numVert);
    bool flag = true;
    for(int i = 0; i < graph->numVert; i++){ // percorre cada linha
    	for(int j = 0; j < graph->numVert; j++){ // cada item da linha
    		if(graph->matrix[i][j] != -1) flag = false;
    		}
    	marca[i] = flag; // marca o nó como true, se é desconexo
    	flag = true;
    }
   
   printf("Adjacency Matrix:");
    
    for(int i = 0; i < graph->numVert; i++){
    	printf("\n");
    	for(int j = 0; j < graph->numVert; j++){
    		if(marca[i] || marca[j] == true) continue; // se o vértice está marcado como não printável, pula
    		
    		if(graph->matrix[i][j] == -1){
    			printf("  0 ");
    		}else{
    			printf("%3d ", graph->matrix[i][j]);
    		}
    	}
    }
    
    free(marca);
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
    if(graph == NULL || vert1<1 || vert1>graph->numVert || vert2<1 || vert2>graph->numVert){
    	printf("-1\n");
        return -1;
    }
    //Verifica se não tem a aresta
    if(existEdge(graph, vert1, vert2) == 0){
        printf("-1\n");
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
	
	int* vizinhos = (int*)malloc( (conta_vizinhos+1) * sizeof(int) );
	vizinhos[0] = conta_vizinhos;
	
	int index_array = 1;
	for(int i=1; i <= graph->numVert; i++){
		if( graph->matrix[vert-1][i-1] != -1){
			vizinhos[index_array] = i;
			index_array++;
		}
	}
	
	// agora printa os vizinhos
	
	for(int i=1; i<=conta_vizinhos; i++){
		printf("%d ", vizinhos[i]);
	}
	printf("\n");
	
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





// MAIN COPIADA DO RUNCODES:






int main(void)
{
    int option;
    int N, x, y, w;
    int res;
    int print_status = 1;

    GRAPH *G;

    scanf(" %d", &option);

    while (option != -1)
    {
        switch (option){
        case 0:
            scanf(" %d", &N);
            G = myGraph(N);
            break;
        case 1:
            // adicionamos
            scanf(" %d %d %d", &x, &y, &w);
            addEdge(G, x, y, w);
            break;
        case 2:
            // get
            scanf(" %d %d", &x, &y);
            res = existEdge(G, x, y);
            print_status = 0;
            break;
        case 3:
        	// neighbors
        	scanf(" %d", &x);
        	free(neighbors(G, x)); // dá free no retorno para não vazar memória
        	print_status = -1;
        	break;
        case 4:
        	 // remove
            scanf(" %d %d", &x, &y);
            if(removeEdge(G, x, y) == -1){
            	print_status = -1;
            }
            break;
        case 5:
        	// matriz
        	adjacencyMatrix(G);
        	print_status = -1;
        	break;
        case 6:
            //Max neighbors
            res = maxNeighbors(G);
            print_status = 0;
            printf("max vertex: ");
            break;
        default:
            printf("unrecognized option %d!\n", option);
        }
        scanf(" %d", &option);
    }

    if (option == -1){
        switch(print_status){
        	case -1:
        		break;
        	case 0:
            	printf("%d\n", res);
            	break;
            case 1:
        		printInfo(G);
        		break;
     	   }
    }

    deleteGraph(&G);
    return 0;
}
