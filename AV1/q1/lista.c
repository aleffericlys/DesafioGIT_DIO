#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include "lista.h"


struct Diferenca{
	int dif, cont;
	struct Diferenca *prox;
};

typedef struct Diferenca dife;

dife *diff(int n){
	dife *novo;
	novo = (dife*)malloc(sizeof(dife));
	novo->dif = n;
	novo->cont = 1;
	novo->prox = NULL;

	return novo;
}


void buscaLocal(dife *ant, dife **atual, dife *no){
	
	if ((*atual) != NULL)
	{
		if ((*atual)->dif < no->dif)
		{
			buscaLocal((*atual), &((*atual)->prox), no);
		}else if((*atual)->dif > no->dif){
			no->prox = (*atual);
			*atual = no;
		}else{
			(*atual)->cont += 1;
			free(no);
			no = NULL;
		}
	}else{
		(*atual) = no;
	}
}


void insereOrd(dife **inicio, int n){
	
	dife *novo;
	novo = diff(n);
	if ((*inicio) == NULL)
	{
		*inicio = novo;
	}else
	{
		buscaLocal(NULL, inicio, novo);
	}
}


void mostraLista(dife *inicio){
	if(inicio != NULL)
	{
		printf("diferença de %d, apareceu %d vezes\n", inicio->dif, inicio->cont);
		mostraLista(inicio->prox);
	}
}

void limpaLista(dife *inicio){
	if (inicio != NULL)
	{
		limpaLista(inicio->prox);
		free(inicio);
		inicio = NULL;
	}
}

// int main()
// {
// 	srand(time(NULL));
// 	printf("alou\n");
// 	dife *primeiro;
// 	primeiro = NULL;
// 	int a = -1;
// 	for (int i = 0; i < 20; i++)
// 	{
// 		a = rand() % 10;
// 		printf("%d\n", a);
// 		insereOrd(&primeiro, a);
// 	}
// 	mostraLista(primeiro);
// 	limpaLista(primeiro);
	
// 	return 0;
// }