#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "q2.h"

struct ArvNum{ 
	int val;
	int profu;
	int alt;
	arvNum *Dir;
	arvNum *Esq; 
};


//cria o novo nó
// i: valor a ser inserido na arvore
arvNum *novoNo(int i){
	arvNum *nova;
	nova = (arvNum*)malloc(sizeof(arvNum));

	nova->val = i;
	nova->profu = -1;
	nova->alt = -1;
	nova->Esq = NULL;
	nova->Dir = NULL;
	
	return nova;
}

// 	raiz: ponteiro para raiz da arvore q o valor será inserido
//	nova: ponteiro para o nó com o valor a ser inserido
int insereNum(arvNum **raiz, arvNum *nova){
	int ret = 0;
	if (*raiz == NULL)
	{
		*raiz = nova;
		ret = 1;
	}else if((*raiz)->val < nova->val)
	{
		ret = insereNum(&((*raiz)->Dir), nova);
	}else if ((*raiz)->val > nova->val)
	{
		ret = insereNum(&((*raiz)->Esq), nova);
	}

	altura(*raiz);

	balanceamento(&(*raiz));

	return ret;
}

int busca(arvNum *raiz, int val){
	int ret = 0;
	if (raiz != NULL)
	{
		if (raiz->val == val)
		{
			ret = 1;
		}else if (raiz->val > val)
		{
			ret = busca(raiz->Esq, val);
		}else
		{
			ret = busca(raiz->Dir, val);
		}
	}
	return ret;
}


void profundidade(arvNum *raiz, int profu){
	if (raiz != NULL)
	{
		raiz->profu = profu;
		profundidade(raiz->Esq, profu +1);
		profundidade(raiz->Dir, profu +1);
	}	
}


void limpaArv(arvNum *raiz){
	if (raiz != NULL)
	{
		limpaArv(raiz->Esq);
		limpaArv(raiz->Dir);
		free(raiz);
		raiz = NULL;
	}
}


int ehFolha(arvNum *no){
	int ret = 0;
	if (no->Dir == NULL && no->Esq == NULL)
	{
		ret = 1;
	}
	return ret;
}

void mame(arvNum *raiz, int *maior, int *menor){
	if (raiz != NULL)
	{
		if (ehFolha(raiz))
		{
			if (*maior == -1 && *menor == -1)
			{
				*maior = raiz->profu;
				*menor = raiz->profu;
			}else if (raiz->profu > *maior)
			{
				*maior =raiz->profu;
			}else if (raiz->profu < *menor)
			{
				*menor = raiz->profu;
			}
		}
		mame(raiz->Esq, maior, menor);
		mame(raiz->Dir, maior, menor);
	}
}

void altura(arvNum *No){
	if(ehFolha(No))	
	{
		No->alt = 0;
	}else if (No->Esq == NULL)
	{
		No->alt = No->Dir->alt + 1;
	}else if (No->Dir == NULL)
	{
		No->alt = No->Esq->alt + 1;
	}else if (No->Esq->alt > No->Dir->alt)
	{
		No->alt = No->Esq->alt + 1;
	}else
	{
		No->alt = No->Dir->alt + 1;
	}
}

int fatBal(arvNum *No){
	int ret;
	if (ehFolha(No))
	{
		ret = 0;
	}else if (No->Dir == NULL)
	{
		ret = (No->Esq->alt) - (-1);
	}else if (No->Esq == NULL)
	{
		ret = (-1) - (No->Dir->alt);
	}else
	{
		ret = (No->Esq->alt) - (No->Dir->alt);
	}
	return ret;
}

void balHorario(arvNum **raiz){
	arvNum *No;
	No = (*raiz)->Esq;
	(*raiz)->Esq = No->Dir;
	No->Dir = *raiz;
	altura((*raiz));
	altura(No); 
	(*raiz) = No;
}


void balAntHorario(arvNum **raiz){
	arvNum *No;
	No = (*raiz)->Dir;
	(*raiz)->Dir = No->Esq;
	No->Esq = *raiz;
	altura((*raiz));
	altura(No); 
	(*raiz) = No;
}

void balanceamento(arvNum **raiz){

	if (fatBal(*raiz) == 2)	
	{
		if (fatBal((*raiz)->Esq) == 1)
		{
			balHorario(raiz);
		}else
		{
			balAntHorario(&(*raiz)->Esq);
			balHorario(raiz);
		}		
	}else if (fatBal(*raiz) == -2)
	{
		if (fatBal((*raiz)->Dir) == -1)
		{
			balAntHorario(raiz);
		}else
		{
			balHorario(&(*raiz)->Dir);
			balAntHorario(raiz);
		}
	}
}

// int main(int argc, char const *argv[])
// {
// 	srand(time(NULL));
// 	arvNum *raiz;
// 	raiz = NULL;

// 	for (int i = 0; i < 1000; i++)
// 	{
// 		int a, b;
// 		a = 1 + rand() % 1000;
// 		b = rand() % 1000;

// 		insereNum(&raiz, novoNo(a * b));
// 	}
// 	profundidade(raiz, 0);
// 	// int val[] = {392882, 730914, 121600, 946187, 960666};

// 	mostrar(raiz);

// 	int maior = 0, menor = 0;
// 	mameProf(raiz, &maior, &menor);
// 	printf("%d %d\n", maior, menor);

// 	limpaArv(raiz);
// 	return 0;
// }