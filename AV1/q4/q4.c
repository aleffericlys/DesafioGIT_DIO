#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "q4.h"


struct ArvTermos{
	char termo[46]; //Pneumoultramicroscopicossilicovulcanoconiótico 
	arvint *pag;
	subt *Subterm;
	int alt;
	termos *Esq;
	termos *Dir;
};


struct ArvSubT{
	char subt[46]; //Pneumoultramicroscopicossilicovulcanoconiótico 
	arvint *pag;
	int alt;
	subt *Esq;
	subt *Dir;
};


struct ArvInt{ 
	int val;
	int alt;
	arvint *Dir;
	arvint *Esq; 
};

//termos

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

	alturaT(*raiz);

	balanceamentoT(&(*raiz));

	
	return ret;
}

void mostra(termos *raiz){
	if (raiz != NULL)
	{
		mostra(raiz->Esq);
		printf("\nTermo: %s -> ", raiz->termo);
		printf("Paginas: ");
		mostraP(raiz->pag);
		printf("\n");
		mostraSubt(raiz->Subterm);
		printf("\n");
		mostra(raiz->Dir);
	}
}

void alturaT(termos *No){
	if(ehFolhaT(No))	
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

int ehFolhaT(termos *no){
	int ret = 0;
	if (no->Dir == NULL && no->Esq == NULL)
	{
		ret = 1;
	}
	return ret;
}

int fatBalT(termos *No){
	int ret;
	if (ehFolhaT(No))
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

void balHorarioT(termos **raiz){
	termos *No;
	No = (*raiz)->Esq;
	(*raiz)->Esq = No->Dir;
	No->Dir = *raiz;
	alturaT((*raiz));
	alturaT(No); 
	(*raiz) = No;
}

void balAntHorarioT(termos **raiz){
	termos *No;
	No = (*raiz)->Dir;
	(*raiz)->Dir = No->Esq;
	No->Esq = *raiz;
	alturaT((*raiz));
	alturaT(No); 
	(*raiz) = No;
}

void balanceamentoT(termos **raiz){

	if (fatBalT(*raiz) == 2)	
	{
		if (fatBalT((*raiz)->Esq) == 1)
		{
			balHorarioT(raiz);
		}else
		{
			balAntHorarioT(&(*raiz)->Esq);
			balHorarioT(raiz);
		}		
	}else if (fatBalT(*raiz) == -2)
	{
		if (fatBalT((*raiz)->Dir) == -1)
		{
			balAntHorarioT(raiz);
		}else
		{
			balHorarioT(&(*raiz)->Dir);
			balAntHorarioT(raiz);
		}
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


//subt

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
	
	alturaSubt(*raiz);

	balanceamentoSubt(&(*raiz));

	return ret;
}

void mostraSubt(subt *raiz){
	if (raiz != NULL)
	{
		mostraSubt(raiz->Esq);
		printf("\n\tSubtermo: %s -> ", raiz->subt);
		printf("Paginas: ");
		mostraP(raiz->pag);
		mostraSubt(raiz->Dir);
	}
}

int ehFolhaSubt(subt *no){
	int ret = 0;
	if (no->Dir == NULL && no->Esq == NULL)
	{
		ret = 1;
	}
	return ret;
}

void alturaSubt(subt *No){
	if(ehFolhaSubt(No))	
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

int fatBalSubt(subt *No){
	int ret;
	if (ehFolhaSubt(No))
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

void balHorarioSubt(subt **raiz){
	subt *No;
	No = (*raiz)->Esq;
	(*raiz)->Esq = No->Dir;
	No->Dir = *raiz;
	alturaSubt((*raiz));
	alturaSubt(No); 
	(*raiz) = No;
}

void balAntHorarioSubt(subt **raiz){
	subt *No;
	No = (*raiz)->Dir;
	(*raiz)->Dir = No->Esq;
	No->Esq = *raiz;
	alturaSubt((*raiz));
	alturaSubt(No); 
	(*raiz) = No;
}

void balanceamentoSubt(subt **raiz){

	if (fatBalSubt(*raiz) == 2)	
	{
		if (fatBalSubt((*raiz)->Esq) == 1)
		{
			balHorarioSubt(raiz);
		}else
		{
			balAntHorarioSubt(&(*raiz)->Esq);
			balHorarioSubt(raiz);
		}		
	}else if (fatBalSubt(*raiz) == -2)
	{
		if (fatBalSubt((*raiz)->Dir) == -1)
		{
			balAntHorarioSubt(raiz);
		}else
		{
			balHorarioSubt(&(*raiz)->Dir);
			balAntHorarioSubt(raiz);
		}
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


//Paginas

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

	alturaP(*raiz);

	balanceamentoP(&(*raiz));

	return ret;
}

void mostraP(arvint *raiz){
	if (raiz != NULL)
	{
		mostraP(raiz->Esq);
		printf("%d ", raiz->val);
		mostraP(raiz->Dir);
	}
}

int ehFolhaP(arvint *no){
	int ret = 0;
	if (no->Dir == NULL && no->Esq == NULL)
	{
		ret = 1;
	}
	return ret;
}

void alturaP(arvint *No){
	if(ehFolhaP(No))	
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

int fatBalP(arvint *No){
	int ret;
	if (ehFolhaP(No))
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

void balHorarioP(arvint **raiz){
	arvint *No;
	No = (*raiz)->Esq;
	(*raiz)->Esq = No->Dir;
	No->Dir = *raiz;
	alturaP((*raiz));
	alturaP(No); 
	(*raiz) = No;
}

void balAntHorarioP(arvint **raiz){
	arvint *No;
	No = (*raiz)->Dir;
	(*raiz)->Dir = No->Esq;
	No->Esq = *raiz;
	alturaP((*raiz));
	alturaP(No); 
	(*raiz) = No;
}

void balanceamentoP(arvint **raiz){

	if (fatBalP(*raiz) == 2)	
	{
		if (fatBalP((*raiz)->Esq) == 1)
		{
			balHorarioP(raiz);
		}else
		{
			balAntHorarioP(&(*raiz)->Esq);
			balHorarioP(raiz);
		}		
	}else if (fatBalP(*raiz) == -2)
	{
		if (fatBalP((*raiz)->Dir) == -1)
		{
			balAntHorarioP(raiz);
		}else
		{
			balHorarioP(&(*raiz)->Dir);
			balAntHorarioP(raiz);
		}
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



// int main(int argc, char const *argv[])
// {
// 	srand(time(NULL));

// 	termos *raiz, *novo;
// 	raiz = NULL;

// 	char termos[7][46] = {"Estudar", "Cavar", "Gastar","Alocar", "Blindar", "Forjar", "Desconsiderar"};
// 	char subt[7][5][46] = {
// 							//"Alocar", "Blindar", "Cavar", "Desconsiderar", "Estudar", "Forjar", "Gastar"
// 							"Estudaram", "Estudei", "Estudava", "Estudavam", "Estudarei",
// 							"Cava", "Cavaram", "Cavacao", "Cavo", "Cavei",
// 							"Gasta", "Gastarei", "Gastava", "Gastaria", "Gastaram",
// 							"Alocacao", "Aloca", "Aloquei", "Alocam", "Alocando", 
// 							"Blinda", "Blindagem", "Blindasse", "Blindava", "Blindam", 
// 							"Forja", "Forjei", "Forjavam", "Forjaria", "Forjava",
// 							"Desconsideram", "Desconsideracao", "Desconsiderei", "Desconsiderava", "Desconsideravam"};

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