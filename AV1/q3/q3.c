#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "q3.h"


struct ArvTermos{
	char termo[46]; //Pneumoultramicroscopicossilicovulcanoconiótico 
	arvint *pag;
	subt *Subterm;
	termos *Esq;
	termos *Dir;
};


struct ArvSubT{
	char subt[46]; //Pneumoultramicroscopicossilicovulcanoconiótico 
	arvint *pag;
	subt *Esq;
	subt *Dir;
};


struct ArvInt{ 
	int val;
	arvint *Dir;
	arvint *Esq; 
};


termos *novoTermo(char termo[46], char listSubt[5][46]){
	termos *novo;
	novo = (termos*)malloc(sizeof(termos));

	strcpy(novo->termo, termo);
	novo->pag = dadosInt(); 
	novo->Subterm = dadoSubt(listSubt);
	novo->Dir = NULL;
	novo->Esq = NULL;
	
	return novo;
}

int cadTermo(termos **raiz, termos *novo){
	int ret = 0;
	if (*raiz == NULL)
	{
		*raiz = novo;
		ret = 1;
	}else if(strcmp((*raiz)->termo, novo->termo) > 0){
		ret = cadTermo(&((*raiz)->Esq), novo);
	}else if (strcmp((*raiz)->termo, novo->termo) < 0)
	{
		ret = cadTermo(&((*raiz)->Dir), novo);
	}
	
	return ret;
}

subt *dadoSubt(char subtermo[5][46]){
	subt *novaT, *raiz;
	raiz = NULL;
	for (int i = 0; i < 5; i++)
	{
		novaT = novoSubt(subtermo[i]);
		cadSubt(&raiz, novaT);
	}
	
	return raiz;
}

subt *novoSubt(char subtermo[]){
	subt *novo;
	arvint *no;
	novo = (subt*)malloc(sizeof(subt));
	

	strcpy(novo->subt, subtermo);
	novo->pag = dadosInt();	
	novo->Dir = NULL;
	novo->Esq = NULL;
	
	return novo;
}

int cadSubt(subt **raiz, subt *novo){
	int ret = 0;
	if (*raiz == NULL)
	{
		*raiz = novo;
		ret = 1;
	}else if(strcmp((*raiz)->subt, novo->subt) > 0){
		ret = cadSubt(&((*raiz)->Esq), novo);
	}else if (strcmp((*raiz)->subt, novo->subt) < 0)
	{
		ret = cadSubt(&((*raiz)->Dir), novo);
	}
	
	return ret;
}


arvint *dadosInt(){
	arvint *ret;
	ret = NULL;
	for (int i = 0; i < 10; i++)
	{
		int num = 1 + rand() % 500;
		insereNum(&ret, novoNo(num));
	}
	return ret;
}

arvint *novoNo(int i){
	arvint *nova;
	nova = (arvint*)malloc(sizeof(arvint));

	nova->val = i;
	nova->Esq = NULL;
	nova->Dir = NULL;
	
	return nova;
}

int insereNum(arvint **raiz, arvint *nova){
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

void mostraT(subt *raiz){
	if (raiz != NULL)
	{
		mostraT(raiz->Esq);
		printf("\n\tSubtermo: %s -> ", raiz->subt);
		printf("Paginas: ");
		mostraP(raiz->pag);
		mostraT(raiz->Dir);
	}
}

void mostraP(arvint *raiz){
	if (raiz != NULL)
	{
		mostraP(raiz->Esq);
		printf("%d ", raiz->val);
		mostraP(raiz->Dir);
	}
}

void mostra(termos *raiz){
	if (raiz != NULL)
	{
		mostra(raiz->Esq);
		printf("\nTermo: %s -> ", raiz->termo);
		printf("Paginas: ");
		mostraP(raiz->pag);
		printf("\n");
		mostraT(raiz->Subterm);
		printf("\n");
		mostra(raiz->Dir);
	}
}

void limpaPag(arvint *raiz){
	if (raiz != NULL)
	{
		limpaPag(raiz->Esq);
		limpaPag(raiz->Dir);
		free(raiz);
		raiz = NULL;
	}
	
}

void limpaSubt(subt *raiz){
	if(raiz != NULL){
		limpaSubt(raiz->Esq);
		limpaSubt(raiz->Dir);
		limpaPag(raiz->pag);
		free(raiz);
		raiz = NULL;
	}
}

void limpa(termos *raiz){
	if(raiz != NULL){
		limpa(raiz->Esq);
		limpa(raiz->Dir);
		limpaPag(raiz->pag);
		limpaSubt(raiz->Subterm);
		free(raiz);
		raiz = NULL;
	}
}

// int main(int argc, char const *argv[])
// {
// 	srand(time(NULL));

// 	termos *raiz, *novo;
// 	raiz = NULL;

// 	char termos[7][46] = {"Estudar", "Cavar", "Gastar","Alocar", "Blindar", "Forjar", "Desconsiderar"};
// 	char subt[7][5][46] = {
// 							//"Alocar", "Blindar", "Cavar", "Desconsiderar", "Estudar", "Forjar", "Gastar"
// 							"Estudar", "Estudei", "Estudava", "Estudavam", "Estudarei",
// 							"Cava", "Cavaram", "Cavacao", "Cavo", "Cavei",
// 							"Gasta", "Gastarei", "Gastava", "Gastaria", "Gastaram",
// 							"Alocacao", "Aloca", "Aloquei", "Alocam", "Alocando", 
// 							"Blinda", "Blindagem", "Blindasse", "Blindava", "Blindam", 
// 							"Forja", "Forjei", "Forjavam", "Forjaria", "Forjava",
// 							"Desconsiderar", "Desconsideracao", "Desconsiderei", "Desconsiderava", "Desconsideravam"};

// 	for (int i = 0; i < 7; i++)
// 	{
// 		novo = novoTermo(termos[i], subt[i]);
// 		cadTermo(&raiz, novo);
// 	}
	
// 	mostra(raiz);
// 	printf("\n");
// 	limpa(raiz);
// 	return 0;
// }