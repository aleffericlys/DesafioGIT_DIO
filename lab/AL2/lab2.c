#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ano 2022
#define TAM 7

typedef struct ArvNum arvNum; 

struct ArvNum{ 
	int val;
	arvNum *Dir;
	arvNum *Esq; 
};


//cria o novo nó
// i: valor a ser inserido na arvore
arvNum *novoNo(int i){
	arvNum *nova;
	nova = (arvNum*)malloc(sizeof(arvNum));

	nova->val = i;
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

return ret;
}


//	a)
//	raiz: raiz da arvore
//  retorna a multiplocação de todos os multiplos de 5 maiores que 20
int mult5(arvNum *raiz){
	int papa = 1;
	if(raiz != NULL){
		if (raiz->val > 20)
		{
			if ((raiz->val % 5) == 0){
				papa *= raiz->val;
			}
			papa *= mult5(raiz->Esq);
			papa *= mult5(raiz->Dir);
		}else{
			papa *= mult5(raiz->Dir);
		}
	}
	return papa;
}


//	b)
//	no: ponteiro para o nó q se deseja testar se é  folha ou não
//	retorna 1 se for folha
int ehFolha(arvNum *no){
	int ret = 0;
	if (no->Dir == NULL && no->Esq == NULL)
	{
		ret = 1;
	}
	return ret;
}

//	raiz: raiz da arvore
// 	usa a função ehfolha para contar a quantidade de nós folha
//	retorna a quantidade de nós folha
int contaFolhas(arvNum *raiz){
	int quant = 0;
	if(raiz != NULL){
		quant += ehFolha(raiz);
		quant += contaFolhas(raiz->Esq);
		quant += contaFolhas(raiz->Dir);
	}
	return quant;
}

//	c)
//	raiz: raiz da arvore
//	val: valor q se deseja buscar na arvore
//	aux: NULL
//	Retorna -1 caso esse número não esteja na arvore
//	Retorna -2 caso o valor seja a raiz da arvore
//	Retorna o valor do vai dele, caso haja.
int pai(arvNum *raiz, int val, arvNum *aux){
	int papa = -1;
	if(raiz != NULL){

		if (val < raiz->val)
		{
			papa = pai(raiz->Esq, raiz, val);
		}else if (val > raiz->val)
		{
			papa = pai(raiz->Dir, raiz, val);
		}else{
			if (aux == NULL){
				papa = -2;
			}else{
				papa = aux->val;
			}
		}
	}
	return papa;
}

//d)

//função auxiliar de remover 
arvNum *maisAD(arvNum **raiz){
	arvNum *aux;
	if ((*raiz)->Dir == NULL){
		aux = (*raiz);
		if ((*raiz)->Esq != NULL)
		{
			*raiz = (*raiz)->Esq;
		}else
		{
			*raiz = NULL;
		}
	} 
	else
	{
		aux = maisAD(&(*raiz)->Dir);
	}
	return aux;
}

//	raiz: ponteiro para raiz da arvore
//	val: valor q se deseja remover da arvore
//	retorna 0 caso esse numero n seja removido
//	retorna 1 caso o numero seja removido
int remover(arvNum **raiz, int val){
	int ret = 0;
	if((*raiz) != NULL){

		if (val < (*raiz)->val)
		{
			ret = remover(&(*raiz)->Esq, val);
		}else if (val > (*raiz)->val)
		{
			ret = remover(&(*raiz)->Dir, val);
		}else{
			arvNum *aux = (*raiz);
			if(ehFolha((*raiz)))
			{
				free(aux);
				(*raiz) = NULL;
				ret = 1;
			}else if((*raiz)->Dir == NULL){
				(*raiz) = (*raiz)->Esq;
				aux->Esq = NULL;
				free(aux); aux = NULL; 
				ret = 1;
			}else if((*raiz)->Esq == NULL){
				(*raiz) = (*raiz)->Dir;
				aux->Dir = NULL;
				free(aux); aux = NULL; 
				ret = 1;
			}else{
				aux = maisAD(&((*raiz)->Esq));
				aux->Dir = (*raiz)->Dir;
				aux->Esq = (*raiz)->Esq;
				(*raiz)->Esq = NULL;
				(*raiz)->Dir = NULL;
				free((*raiz));
				(*raiz) = aux;
				aux = NULL;
				ret = 1;
			}
		}
	}
	return ret;
}

void mostraArv(arvNum *raiz){
	if(raiz != NULL){
		printf("%d\n", raiz->val);
		mostraArv(raiz->Esq);
		mostraArv(raiz->Dir);
	}

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

int main(int argc, char const *argv[])
{
	arvNum *raiz = NULL;
	int n;

	int anos[TAM]  = {50, 20, 90, 80, 70, 40, 10};


	for (int i = 0; i < TAM; i++)
	{
		insereNum(&raiz, novoNo(anos[i]));
	}

	mostraArv(raiz);
	// n = contaFolhas(raiz);
	// n = pai(raiz, NULL, 150);
	// n = mult5(raiz);
	n = remover(&raiz, 50);
	printf("%d\n", n);
	mostraArv(raiz);

	limpaArv(raiz);
	return 0;
}  