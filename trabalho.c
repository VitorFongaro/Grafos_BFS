#include <stdio.h>
#include <malloc.h>
#define numNos 17
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INFINITO 1000 // Apenas uma representação

// --------------------------- Estruturas e funções para Lista Q ---------------------------

typedef struct{
	int posVet;
	struct NoListaQ * proximo;	// Aponta para o próximo vértice
}NoListaQ; // PARA O BFS

typedef struct{
	NoListaQ * primeiro;
	NoListaQ * ultimo;
}ListaQ;

void init(ListaQ * lq){
    lq->primeiro = NULL;
    lq->ultimo = NULL;
}

void enqueue(ListaQ * lq, int wu){
	NoListaQ * aux = (NoListaQ *) malloc(sizeof(NoListaQ)); // Cria o auxiliar para guardar as informações
	aux->posVet = wu; // Atrubui valor
	aux->proximo = NULL; // Deixa o próximo como nulo;
	if(lq->primeiro == NULL){ // Lista vazia
		// Como ele vai ser o primeiro e único elemento, ele é o primeiro e último da lista
		lq->primeiro = aux;
		lq->ultimo = aux;
	}
	else{ // Insere depois do primeiro
		// lq->ultimo->proximo = aux; Jeito antigo que funciona
	    NoListaQ * temp = lq->ultimo;
	    temp->proximo = (struct NoListaQ *) aux;
	    lq->ultimo = aux; // Define o ponteiro da lista pro último
	}
}

int dequeue(ListaQ * lq){
	if(lq->primeiro == NULL){ // Lista vazia
		return -1;
	}
	else{
		NoListaQ * aux = lq->primeiro;
		int retorno = aux->posVet; // Salvando a informação que vai retornar
		lq->primeiro = (NoListaQ *) aux->proximo; // Recebe o próximo para ser o primeiro
		free(aux); // Libera o 'primeiro' primeiro
		return retorno;
	}
}


// -------------------------------- Estruturas para o Grafo --------------------------------
typedef struct{
	int posVet;
	struct NoLista * proximo;	// Aponta para o próximo vértice
}NoLista;

typedef struct{
	char nome[30]; // Informação do nó
	struct NoLista * primeiro; // O índice do vetor
}Vertice;

typedef Vertice Grafo[numNos]; // Cria o Grafo

void insereVizinho(Grafo wg, int u, int v){
	// u = índice | v = vizinho
    NoLista * aux = (NoLista *) malloc(sizeof(NoLista));
    aux->posVet = v; // Recebe o vizinho
    aux->proximo = NULL; // Deixa o próximo vizinho como NULL
    if(wg[u].primeiro == NULL){ // Primeiro vizinho
    	wg[u].primeiro = (struct NoLista *) aux;
	}
	else{ // Do segundo vizinho em diante
		NoLista * ultimo = (NoLista *) wg[u].primeiro; // Pega o primeiro da lista
		while(ultimo->proximo != NULL){
			ultimo = (NoLista *) ultimo->proximo; // Avança até o último
		}
		ultimo->proximo = (struct NoLista *) aux; // Recebe o vizinho
	}
}

// ----------------------------------------    BFS    ----------------------------------------
int cor[numNos]; // Cor
int dist[numNos]; // Dsitância
int pred[numNos]; // Predecessores

void BFS(Grafo g, int s){
	ListaQ Q;
	int u, v;
	for(u = 0; u <numNos; u++){
		if(u != s){ // Para todos menos o s (start)
			cor[u] = WHITE;
			dist[u] = INFINITO;
			pred[u] = -1; // Nesse algoritmo, -1 significa que não tem predecessor
		}
	}
	cor[s] = GRAY;
	dist[s] = 0;
	pred[s] = -1;
	
	init(&Q);
	enqueue(&Q, s);
	while(Q.primeiro != NULL){
		u = dequeue(&Q);
		NoLista * aux = (NoLista *) g[u].primeiro;
		for(aux; aux != NULL; aux = (NoLista *) aux->proximo){
			v = aux->posVet;
			if(cor[v] == WHITE ){
				cor[v] = GRAY;
				dist[v] = dist[u] + 1;
				pred[v] = u;
				enqueue(&Q, v);
			}
		}
		cor[u] = BLACK;
	}
}

void main(){

    Grafo g = {
        {"Argentina", NULL},
        {"Chile", NULL},
        {"Paraguai", NULL},
        {"Brasil", NULL},
        {"Uruguai", NULL},
        {"Bolivia", NULL},
        {"Peru", NULL},
        {"Equador", NULL},
        {"Colombia", NULL}, 
        {"Venezuela", NULL},
        {"Panama", NULL},
        {"Costa Rica", NULL},
        {"Nicaragua", NULL}, 
        {"El Salvador", NULL},
        {"Honduras", NULL},
        {"Guatemala", NULL},
        {"Mexico", NULL}
    }; // Inicia o Grafo

    insereVizinho((Vertice *) &g, 0, 1);
    insereVizinho((Vertice *) &g, 0, 2);
    insereVizinho((Vertice *) &g, 0, 3);
    insereVizinho((Vertice *) &g, 0, 4);
    insereVizinho((Vertice *) &g, 1, 0);
    insereVizinho((Vertice *) &g, 1, 5);
    insereVizinho((Vertice *) &g, 1, 6);
    insereVizinho((Vertice *) &g, 2, 0);
    insereVizinho((Vertice *) &g, 2, 3);
    insereVizinho((Vertice *) &g, 2, 5);
    insereVizinho((Vertice *) &g, 3, 0);
    insereVizinho((Vertice *) &g, 3, 2);
    insereVizinho((Vertice *) &g, 3, 4);
    insereVizinho((Vertice *) &g, 3, 6);
    insereVizinho((Vertice *) &g, 4, 0);
    insereVizinho((Vertice *) &g, 4, 3);
    insereVizinho((Vertice *) &g, 5, 1);
    insereVizinho((Vertice *) &g, 5, 2);
    insereVizinho((Vertice *) &g, 5, 6);
    insereVizinho((Vertice *) &g, 6, 1);
    insereVizinho((Vertice *) &g, 6, 3);
    insereVizinho((Vertice *) &g, 6, 7);
    insereVizinho((Vertice *) &g, 6, 8);
    insereVizinho((Vertice *) &g, 7, 6);
    insereVizinho((Vertice *) &g, 7, 8);
    insereVizinho((Vertice *) &g, 8, 6);
    insereVizinho((Vertice *) &g, 8, 7);
    insereVizinho((Vertice *) &g, 8, 9);
    insereVizinho((Vertice *) &g, 8, 10);
    insereVizinho((Vertice *) &g, 9, 8);
    insereVizinho((Vertice *) &g, 10, 8);
    insereVizinho((Vertice *) &g, 10, 11);
    insereVizinho((Vertice *) &g, 11, 10);
    insereVizinho((Vertice *) &g, 11, 12);
    insereVizinho((Vertice *) &g, 12, 13);
    insereVizinho((Vertice *) &g, 12, 14);
    insereVizinho((Vertice *) &g, 13, 12);
    insereVizinho((Vertice *) &g, 13, 15);
    insereVizinho((Vertice *) &g, 14, 12);
    insereVizinho((Vertice *) &g, 14, 15);
    insereVizinho((Vertice *) &g, 15, 13);
    insereVizinho((Vertice *) &g, 15, 14);
    insereVizinho((Vertice *) &g, 15, 16);
    insereVizinho((Vertice *) &g, 16, 15);

    BFS(g, 0);

    int i;
    printf("\nNO\t\tPAIS \tCOR \tDIST \t PRED\n");
	for(i = 0; i < numNos; i++){
		printf("%d \t %11s \t %d \t %d \t %s \n", i, g[i].nome, cor[i], dist[i], g[pred[i]].nome);
	}
}