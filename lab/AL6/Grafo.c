#include <stdio.h>
#include <stdlib.h>

struct grafo//Definição da struct do grafo.
{
	int ehPonderado;
	int nVertices;
	int grauMax;
	int **arestas;
	float **pesos;
	int *grau;
};

typedef struct grafo Grafo;

//Função que cria um novo grafo, recebendo um ponteiro para ponteiro de um grafo, o numero de vertices desse grafo 
//numero maximo de ligações (arestas) de cada vertice e uma opção que indica se temos pesos nas ligações.
void criarGrafo(Grafo **gr, int nVertices, int grauMax, int ehPonderado)
{
	*gr = (Grafo *) malloc(sizeof(Grafo));
	(*gr)->nVertices = nVertices;
	(*gr)->grauMax = grauMax;
	(*gr)->ehPonderado = ehPonderado;
	(*gr)->grau = (int *) calloc(nVertices, sizeof(int));

	(*gr)->arestas = (int **) malloc(nVertices * sizeof(int *));
	for(int i = 0; i < nVertices; i++)
		(*gr)->arestas[i] = (int *) malloc(grauMax * sizeof(int));
	
	if((*gr)->ehPonderado)
	{
		(*gr)->pesos = (float **) malloc(nVertices * sizeof(float *));
		for(int i = 0; i < nVertices; i++)
			(*gr)->pesos[i] = (float *) malloc(grauMax * sizeof(float));
	}
}

//Função que limpa o grafo
void liberarGrafo(Grafo *gr)
{
	if(gr != NULL)
	{
		for(int i = 0; i < gr->nVertices; i++)
			free(gr->arestas[i]);
		free(gr->arestas);

		if(gr->ehPonderado)
		{
			for(int i = 0; i < gr->nVertices; i++)
				free(gr->pesos[i]);
			free(gr->pesos);
		}
		free(gr->grau);
		free(gr);
	}
}

//Função que insere as ligações no grafo.
//Recebe o grafo, os vertices de origem e destino, opção de digrafo e o peso da ligação.
int inserirAresta(Grafo **gr, int origem, int destino, int ehDigrafo, float peso)
{
	int inseriu = 1;
	if(*gr == NULL)
		inseriu = 0;

	else if(origem < 0 || origem >= (*gr)->nVertices)
		inseriu = 0;
	
	else if(destino < 0 || destino >= (*gr)->nVertices)
		inseriu = 0;
	else
	{
		(*gr)->arestas[origem][(*gr)->grau[origem]] = destino;
		if((*gr)->ehPonderado)
			(*gr)->pesos[origem][(*gr)->grau[origem]] = peso;
		(*gr)->grau[origem]++;

		if(!ehDigrafo)
			inseriu = inserirAresta(gr, destino, origem, 1, peso);
	}
	return inseriu;
}

//Função que mostra um grafo.
void mostraGrafo(Grafo *gr){
    printf("origem \t\t destino \n");
    for(int i = 0; i < gr->nVertices;i++)
        for(int d = 0; d < gr->grau[i];d++)
            if(gr->arestas[i][d] != 0)
                printf("%d \t\t %d \n",i,gr->arestas[i][d]);
}

//Função que faz a busca por profundidade em um grafo.
void Buscaprofundidade(Grafo *gr, int ini, int *visitado, int cont){

	int i;
	visitado[ini] = cont;

	for(int i = 0; i < gr->grau[ini]; i++)
	{
		if(!visitado[gr->arestas[ini][i]]){
					Buscaprofundidade(gr, gr->arestas[ini][i], visitado, cont + 1);
		}
	}
}

//Função auxiliar que trabalha com a função Buscaprofundidade, ela zera o vetor visitado para posterior preenchimento.
//Recebe o grafo, o vertice de inicio da busca e um vetor de retorno da busca.
void Buscaprofundidade_grafo(Grafo *gr, int ini, int *visitado){
	int i, cont = 1;
	for(int i = 0; i < gr->nVertices; i++)
	{
		visitado[i] = 0;
	}
	Buscaprofundidade(gr, ini, visitado, cont);
}

//Função que faz a busca por largura em um grafo.
//Recebe o grafo, o vertice de inicio da busca e um vetor de retorno da busca.
void Buscalargura_grafo(Grafo *gr, int ini, int *visitado){
	int i = 0, vert, numv = gr->nVertices, cont = 1, fila[numv], inicio = 0, fim = 0;

	for(int i = 0; i < gr->nVertices; i++)
	{
		visitado[i] = 0;
	}

	fim++;
	fila[fim] = ini;
	visitado[ini] = cont;	

	while (inicio != fim){
		inicio = (inicio + 1) % numv;
		vert = fila[inicio];
		cont++;

		for (i = 0; i < gr->grau[vert]; i++)
		{
			if(!visitado[gr->arestas[vert][i]]){
				fim = (fim + 1) % numv;
				fila[fim] = gr->arestas[vert][i];
				visitado[gr->arestas[vert][i]] = cont;
			}
		}	
	}
}

int main(){
    int ehDigrafo = 1;
    Grafo *gr;

    criarGrafo(&gr, 5, 5, 1);

    inserirAresta(&gr, 0, 1, ehDigrafo, 0);
    inserirAresta(&gr, 1, 3, ehDigrafo, 0);
    inserirAresta(&gr, 1, 2, ehDigrafo, 0);
    inserirAresta(&gr, 2, 4, ehDigrafo, 0);
    inserirAresta(&gr, 3, 0, ehDigrafo, 0);
    inserirAresta(&gr, 3, 4, ehDigrafo, 0);
    inserirAresta(&gr, 4, 1, ehDigrafo, 0);
	int vet[5];
	int vet2[5];

	mostraGrafo(gr);
	printf("\n");

	Buscaprofundidade_grafo(gr, 0, vet);
	printf("Busca em profundidade: ");
	for (int i = 0; i < 5; i++)
	{
		printf("%d ",vet[i]);
	}
	printf("\n");

	Buscalargura_grafo(gr, 0, vet2);
	printf("Busca em largura: ");
	for (int i = 0; i < 5; i++)
	{
		printf("%d ",vet2[i]);
	}
	printf("\n");
    
    liberarGrafo(gr);

    return 0;
}