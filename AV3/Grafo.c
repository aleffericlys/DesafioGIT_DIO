#include <stdio.h>
#include <stdlib.h>

struct grafo
{
	int ehPonderado;
	int nVertices;
	int grauMax;
	int **arestas;
	float **pesos;
	int *grau;
};

typedef struct grafo Grafo;

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

void mostraGrafo(Grafo *gr){
    printf("origem \t\t destino \n");
    for(int i = 0; i < gr->nVertices;i++)
        for(int d = 0; d < gr->grau[i];d++)
            if(gr->arestas[i][d] != 0)
                printf("%d \t\t %d \n",i,gr->arestas[i][d]);
}

int procuraMenorDistancia(float *dist, int *visitado, int nVertices){
	int menor = -1, primeiro = 1;

	for(int i = 0; i < nVertices; i++)
	{
		if(dist[i] >= 0 && visitado[i] == 0)
		{
			if(primeiro)
			{
				menor = i;
				primeiro = 0;
			}
			else
			{
				if(dist[menor] > dist[i])
					menor = i;
			}
		}
	}
	return menor;
}

void Djikstra(Grafo *gr, int ini, int *ant, float *dist){
	int i = 0;
	int cont = gr->nVertices;
	int ind;
	int visitado[gr->nVertices];
	int aux;

	for(i = 0; i < cont; i++)
	{
		visitado[i] = 0;
		ant[i] = -1;
		dist[i] = -1;
	}

	dist[ini] = 0;

	while (cont > 0){
		int aux = procuraMenorDistancia(dist, visitado, gr->nVertices);

		if(aux != -1)
		{
			visitado[aux] = 1;
			cont--;

			for(i = 0; i < gr->grau[aux]; i++)
			{
				ind = gr->arestas[aux][i];
				if(dist[ind] < 0)
				{
					dist[ind] = dist[aux] + gr->pesos[aux][i];
					ant[ind] = aux;
				}
				else
				{
					if(dist[ind] > dist[aux] + gr->pesos[aux][i]) 
					{
						dist[ind] = dist[aux] + gr->pesos[aux][i];
						ant[ind] = aux;
					}
				}
			}
		}
	}
}

int main() {
    int ehDigrafo = 1;
    Grafo *gr;

    criarGrafo(&gr, 10, 6, 1);
	//A = 0
    inserirAresta(&gr, 0, 1, ehDigrafo, 60);
	inserirAresta(&gr, 0, 2, ehDigrafo, 54);
	inserirAresta(&gr, 0, 3, ehDigrafo, 42);
	//B = 1
	inserirAresta(&gr, 1, 3, ehDigrafo, 71);
	inserirAresta(&gr, 1, 5, ehDigrafo, 29);
	//C = 2
	inserirAresta(&gr, 2, 3, ehDigrafo, 56);
	inserirAresta(&gr, 2, 4, ehDigrafo, 67);
	//D = 3
	inserirAresta(&gr, 3, 4, ehDigrafo, 26);
	inserirAresta(&gr, 3, 5, ehDigrafo, 52);
	inserirAresta(&gr, 3, 6, ehDigrafo, 87);
	//E = 4
	inserirAresta(&gr, 4, 6, ehDigrafo, 70);
	inserirAresta(&gr, 4, 8, ehDigrafo, 73);
	//F = 5
	inserirAresta(&gr, 5, 6, ehDigrafo, 20);
	inserirAresta(&gr, 5, 7, ehDigrafo, 25);
	//G = 6
	inserirAresta(&gr, 6, 7, ehDigrafo, 36);
	inserirAresta(&gr, 6, 8, ehDigrafo, 59);
	inserirAresta(&gr, 6, 9, ehDigrafo, 32);
	//H = 7
	inserirAresta(&gr, 7, 9, ehDigrafo, 25);
	//I = 8
	inserirAresta(&gr, 8, 9, ehDigrafo, 26);
    //J = 9

	int ant[10];
	float dist[10];

	mostraGrafo(gr);
	printf("\n");

	Djikstra(gr, 0, ant, dist);

	printf("Djikstra:\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%f %d\n", dist[i], ant[i]);
	}
	printf("\n");

	liberarGrafo(gr);

    return 0;
}