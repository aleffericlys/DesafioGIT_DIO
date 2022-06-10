#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "q1.h"
// #include <.h>

typedef struct ArvNum arvNum; 

struct ArvNum{ 
	int val;
	int profu;
	arvNum *Dir;
	arvNum *Esq; 
};


//cria o novo nó
// i: valor a ser inserido na arvore
arvNum *novoNo(int i){
	arvNum *nova;
	nova = (arvNum*)malloc(sizeof(arvNum));

	nova->val = i;
	nova->profu = 0;
	nova->Esq = NULL;
	nova->Dir = NULL;
	
	return nova;
}

// 	raiz: ponteiro para raiz da arvore q o valor será inserido
//	nova: ponteiro para o nó com o valor a ser inserido
int insereNum(arvNum **raiz, arvNum *nova, int profu){
	int ret = 0;
	if (*raiz == NULL)
	{
		nova->profu = profu;
		*raiz = nova;
		ret = 1;
	}else if((*raiz)->val < nova->val)
	{
		ret = insereNum(&((*raiz)->Dir), nova, (*raiz)->profu+1);
	}else if ((*raiz)->val > nova->val)
	{
		ret = insereNum(&((*raiz)->Esq), nova, (*raiz)->profu+1);
	}

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

void limpaArv(arvNum *inicio){
	if (inicio != NULL)
	{
		limpaArv(inicio->Esq);
		limpaArv(inicio->Dir);
		free(inicio);
		inicio = NULL;
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
			if (*maior == 0 && *menor == 0)
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

// 		insereNum(&raiz, novoNo(a * b), 0);
// 	}
// 	int val[] = {392882, 730914, 121600, 946187, 960666};

// 	int maior = 0, menor = 0;
// 	mame(raiz, &maior, &menor);
// 	printf("%d %d\n", maior, menor);

// 	limpaArv(raiz);
// 	return 0;
// }