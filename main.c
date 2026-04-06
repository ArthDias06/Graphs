//Arthur de Castro Dias - 16855302
//Pedro Tiago Biffi - 1627777
//Gabriel Carraro Salzedas - 1627905
//Guilherme Cavalcanti de Santana - 15456556

#include<stdio.h>
#include<stdlib.h>

typedef struct graph_{
    int** matrix; //Matriz de adjacência
    int numVert; //Quantidade de vértices do grafo
}GRAPH;

int* neighbors(GRAPH*, int); //Declaração do protótipo de neighbors


//Função para criação do grafo
GRAPH* myGraph(int N){
    GRAPH* graph = malloc(sizeof(GRAPH));
    //Verificação se houve sucesso na alocação
    if(graph == NULL){
        printf("Erro ao alocar memória para o grafo!\n");
        return NULL;
    }
    //Verificação se o número de vértices enviado é válido
    if(N < 1){
        printf("Grafo com número inválido de vértices!\n");
        free(graph);
        graph = NULL;
        return NULL;
    }
    graph->numVert = N;
    graph->matrix = malloc(sizeof(int*) * N);
    //Se a matrix não for alocada, libera a memória de graph
    if(graph->matrix == NULL){
        free(graph);
        graph = NULL;
        printf("Erro ao alocar matriz!\n");
        return NULL;
    }
    //Alocação das linhas da matriz
    for(int i = 0; i < N; i++){
        graph->matrix[i] = malloc(sizeof(int) * N);
        if(graph->matrix[i] == NULL){
            //Se a linha der problema na alocação libera todas as anteriores
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
    //Retorna o ponteiro para o grafo
    return graph;
}

//Função para retorno da matriz de adjacência para o  usuário
int** adjacencyMatrix(GRAPH* graph){
    if(graph == NULL || graph->matrix == NULL){
        return NULL;
    }
    return graph->matrix;
}

//Função para verificar existência de uma certa aresta
int existEdge(GRAPH* graph, int vert1, int vert2){
    if(graph == NULL){
        return 0;
    }
    //Verifica se a posiçção na matriz de acordo com os vértices enviados é diferented e -1
    if(graph->matrix[vert1-1][vert2-1] != -1){ //Retira 1 do valor enviado, pois os vértices são de 1 - N, mas a matriz é de 0 - N-1
        return 1;
    }
    return 0;
}


//Função para printar o vetor de vizinhos, a matriz de adjacência ou as informações do gráfico
void printInfo(GRAPH* graph, int* vetNeighbors, int** adjacencyMatrix){
    if(graph == NULL){
        return;
    }
    //Se o ponteiro do vetor de vizinhos não for nulo ele printa o vetor
    if(vetNeighbors != NULL){
        //A posição 0 do vetor guarda o tamanho do vetor
        for(int i = 1; i <= vetNeighbors[0]; i++){
            printf("%d ", vetNeighbors[i]);
        }
        printf("\n");
        free(vetNeighbors);
        return;
    }
    //Se o ponteiro da matriz de adjacência não for nulo ele printa a matriz
    if(adjacencyMatrix != NULL){
        printf("Adjacency Matrix:");

        for(int i = 0; i < graph->numVert; i++){
            printf("\n");
            for(int j = 0; j < graph->numVert; j++){
                //Todas as posições preenchidas com -1 são apresentadas como 0 para o usuário
                if(adjacencyMatrix[i][j] == -1){
                    printf("  0 ");
                }else{
                    //Mostra para o usuário com uma identação de 3 espaços
                    printf("%3d ", adjacencyMatrix[i][j]);
                }
            }
        }
        
        return;
    }
    //Caso ambos ponteiros sejam nulos, ele printa as informações dos vértices e arestas
    printf("V = [");
    //Print dos vértices do grafo
    for(int i =0; i< graph->numVert; i++){
        if(i+1 != graph->numVert){
            printf("%d, ", i+1);
        //Se ele chegar no final ele não printa com a vírgula
        }else{
            printf("%d]\n", i+1);
        }
    }
    //Print das arestas
    int printaVirgula=0; // a vírgula é imprimida antes da aresta. Por isso, quando imprimir a primeira aresta antes não pode imprimir vírgula
    printf("E = [");
    for(int i = 1; i <= graph->numVert; i++){
        for(int j = 1; j <= i; j++){
            //Verifica se a aresta existe na posição procurada
            if(existEdge(graph, i, j)){

            	if(printaVirgula) printf(", ");
            	printaVirgula = 1;
            	
                printf("(%d, %d)", j, i);
            }
        }
    }
    printf("]\n");
}

//Função para retornar o vértice com maior número de vizinhos
int maxNeighbors(GRAPH* graph){
    if(graph == NULL){
        return 0;
    }
    
    int max_vert;
    int max_neigh = 0;
    int* neighbors_temp;
    for(int i = 1; i <= graph->numVert; i++){
        //pega o vetor de vizinhos de acordo com o  vértice
        neighbors_temp = neighbors(graph, i);

        if(neighbors_temp[0] > max_neigh){ // compara a quantidade de vizinhos desse nó com o maior encontrado até então
            //Se for maior, atualiza os valores
        	max_neigh = neighbors_temp[0];
        	max_vert = i;
        }
        free(neighbors_temp);
    }
    return max_vert;
}

//Função para adicionar aresta
void addEdge(GRAPH* graph, int vert1, int vert2, int edge){
    if(graph == NULL){
        return;
    }
    //Se a aresta tiver um peso inválido dá erro
    if(edge <= 0){
        printf("Aresta com valor inválido!\n");
        return;
    }
    //Se os vértices passados estiverem fora do intervalo estipulado, ele dá erro
    if(vert1 < 1 || vert2 < 1 || vert1 > graph->numVert || vert2 > graph->numVert){
    	printf("Vértices inválidos!\n");
        return;
    }
    //Coloca o valor da aresta na matriz
    graph->matrix[vert1-1][vert2-1] = edge;
    graph->matrix[vert2-1][vert1-1] = edge;
}


//Função para remover aresta
 int removeEdge(GRAPH* graph, int vert1, int vert2){
    if(graph == NULL || vert1<1 || vert1>graph->numVert || vert2<1 || vert2>graph->numVert){
        return -1;
    }
    //Verifica se não tem a aresta
    if(existEdge(graph, vert1, vert2) == 0){
        return -1;
    }
    //Troca o valor da posição por -1
    graph->matrix[vert1-1][vert2-1] = -1;
    graph->matrix[vert2-1][vert1-1] = -1;
    return 0;
}

//Função para cálculo dos vizinhos de um nó
int* neighbors(GRAPH* graph, int vert){
    if(graph == NULL || graph->matrix == NULL) return NULL;
	if(vert < 1 || vert > graph->numVert) return NULL;
	
	int conta_vizinhos = 0;
    //Só percorre a linha da matriz de acordo com o vértice
	for(int i=1; i <= graph->numVert; i++){
        //Se a posição analisada for diferente de -1, ele tem um vizinho
		if( (graph->matrix)[vert-1][i-1] != -1) conta_vizinhos++;
	}
	//Alocação do vetor de vizinhos
	int* vizinhos = (int*)malloc( (conta_vizinhos+1) * sizeof(int) );
    //A primeira posição do vetor é reservada para o tamanho dele
	vizinhos[0] = conta_vizinhos;
	//Percorre novamente a linha para ver os vizinhos e armazenar no vetor
	int index_array = 1;
	for(int i=1; i <= graph->numVert; i++){
		if( (graph->matrix)[vert-1][i-1] != -1){
			vizinhos[index_array] = i;
			index_array++;
		}
	}
	
	return vizinhos;
}

//Função para apagar o grafo
//Envia um ponteiro para ponteiro para poder apagar a posição de mamória correta
void deleteGraph(GRAPH** graph){
    if(graph==NULL){
        return;
    }
    //Desaloca cada linha da matriz
    for(int i = 0; i < (*graph)->numVert; i++){
        free((*graph)->matrix[i]);
        (*graph)->matrix[i] = NULL;
    }
    //Desaloca a matriz
    free((*graph)->matrix);
    (*graph)->matrix = NULL;
    //Desaloca o grafo
    free(*graph);
    *graph = NULL;
}











int main(void)
{
    int option;
    int N, vertex1, vertex2, weight;
    int res;
    int print_status = 1;
    int** matrix = NULL;
    int* neigh = NULL;

    GRAPH *G;

    scanf(" %d", &option);

    while (option != -1)
    {
        switch (option){
        case 0:
            //Criação do grafo
            scanf(" %d", &N);
            G = myGraph(N);
            break;
        case 1:
            // adicionamos
            scanf(" %d %d %d", &vertex1, &vertex2, &weight);
            addEdge(G, vertex1, vertex2, weight);
            break;
        case 2:
            // Verificação da existência
            scanf(" %d %d", &vertex1, &vertex2);
            res = existEdge(G, vertex1, vertex2);
            print_status = 0;
            break;
        case 3:
        	// neighbors
        	scanf(" %d", &vertex1);
        	neigh = neighbors(G, vertex1);
        	break;
        case 4:
        	 // remove
            scanf(" %d %d", &vertex1, &vertex2);
            res = removeEdge(G, vertex1, vertex2);
            if(res == -1){
            	print_status = 0;
            }
            break;
        case 5:
        	// matriz
        	matrix = adjacencyMatrix(G);
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

    //Print final das informações pedidas
    if (option == -1){
        switch(print_status){
        	case 0:
            	printf("%d\n", res);
            	break;
            case 1:
        		printInfo(G, neigh, matrix);
        		break;
     	   }
    }

    //Deleção do grafo 
    deleteGraph(&G);
    return 0;
}
