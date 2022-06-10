#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "series.h"


struct arvSeries
{
	int cod, nTemp;
	char titulo[50];
	struct Temporadas *temps;
	struct arvSeries *dir, *esq;
};

struct Temporadas{
	int numero, quantEp, ano;
	char titulo[50];
	struct arvPart *atores;
	struct Temporadas *prox;
};

struct arvPart
{
	char nomeAtor[50], nomePersona[50], descPersona[200];
	struct arvPart *dir, *esq;
};

series *novaSerie(){
	series *nova;
	char lixo;
	nova = (series*)malloc(sizeof(series));
	printf("Cod da serie: ");
	scanf("%d", &nova->cod);
	printf("Quantidade de temporadas: ");
	scanf("%d", &nova->nTemp);
	fflush(stdin);
	scanf("%c", &lixo);
	printf("Titulo: ");
	setbuf(stdin, 0);
	scanf("%50[^\n]", nova->titulo);
	setbuf(stdin, 0);
	fflush(stdin);
	nova->temps = dadosTemps(nova->nTemp);
	nova->dir = NULL;
	nova->esq = NULL;

	return nova;
}

int cadastroSerie(series **raiz, series *novo){
	int inseriu = 0;
	if (*raiz == NULL)
	{
		*raiz = novo;
		inseriu = 1;
	}else if(novo->cod < (*raiz)->cod)
		{
			inseriu = cadastroSerie(&((*raiz)->esq), novo);
		}else if(novo->cod > (*raiz)->cod)
		{
			inseriu = cadastroSerie(&((*raiz)->dir), novo);
		}else
		{
			free(novo);
			novo = NULL;
			inseriu = 0;
		}

	return inseriu;
}

void limpaSeries(series *raiz){
	if(raiz != NULL){
		limpaSeries(raiz->esq);
		limpaSeries(raiz->dir);
		limpaTemps(raiz->temps);

		free(raiz);
		raiz = NULL;
	}
}

temp *dadosTemps(int val){
	temp *novaT, *inicio;
	inicio = NULL;
	for (int i = 0; i < val; i++)
	{
		novaT = novaTemp(i+1);
		cadTemp(&inicio, novaT);
	}
	
	return inicio;
}

temp *novaTemp(int val){
	temp *nova;
	nova = NULL;
	nova = (temp*)malloc(sizeof(temp));

	nova->numero = val;
	
	printf("Qantidade de eps da %d temp: ", val);
	scanf("%d", &nova->quantEp);
	printf("Ano de lancamento da %d temp: ", val);
	scanf("%d", &nova->ano);
	printf("Titulo da %d temp: ", val);
	setbuf(stdin, 0);
	scanf("%50[^\n]", nova->titulo);
	setbuf(stdin, 0);
	nova->atores = dadosPersona();
	
	nova->prox = NULL;
	
	return nova;
}


int cadTemp(temp **inicio, temp *nova){
	int ret = 0;
	if (*inicio == NULL)
	{
		*inicio = nova;
		ret = 1;
	}else if ((*inicio)->numero == nova->numero )
	{
		free(nova);
		nova = NULL;
		ret = 0;
	}else{
		ret = cadTemp(&((*inicio)->prox), nova);
	}
	return ret;
}

void limpaTemps(temp *inicio){
	if (inicio != NULL)
	{
		limpaTemps(inicio->prox);
		limpaPersona(inicio->atores);
		free(inicio);
		inicio = NULL;
	}
}

int menuPersona(){
	int a;
	printf("deseja adicionar um personagem?\n");
	printf("1- Sim\n");
	printf("0- Nao\n");
	scanf("%d",&a);
	setbuf(stdin, 0);
	if (a != 1 && a != 0)
	{
		printf("digite apenas uma das opções pedidas\n");
		a = menuPersona();
	}
	return a;	
}

ator *dadosPersona(){
	ator *raiz, *persona;
	raiz = NULL;
	persona = NULL;
	int a = 1;
	while (a)
	{
		a = menuPersona(); 
		if(a)
		{
			persona = novoPersona();
			cadPersona(&raiz, persona);
		}
	}
	return raiz;
}


ator *novoPersona(){
	ator *novo;
	novo = (ator*)malloc(sizeof(ator));
	
	printf("Nome do personagem: ");
	setbuf(stdin, 0);
	scanf("%50[^\n]", novo->nomePersona);
	setbuf(stdin, 0);
	printf("Ator que interpreta o personagem: ");
	scanf("%50[^\n]", novo->nomeAtor);
	setbuf(stdin, 0);
	printf("Descricao do personagem: ");
	scanf("%200[^\n]", novo->descPersona);
	setbuf(stdin, 0);
	
	novo->dir = NULL;
	novo->esq = NULL;
	
	return novo;
}

int cadPersona(ator **raiz, ator *novo){
	int ret = 0;
	if (*raiz == NULL)
	{
		*raiz = novo;
		ret = 1;
	}else if(strcmp((*raiz)->nomePersona, novo->nomePersona) > 0){
		ret = cadPersona(&((*raiz)->esq), novo);
	}else if (strcmp((*raiz)->nomePersona, novo->nomePersona) < 0)
	{
		ret = cadPersona(&((*raiz)->dir), novo);
	}
	
	return ret;
}

void limpaPersona(ator *raiz){
	if (raiz != NULL)
	{
		limpaPersona(raiz->esq);
		limpaPersona(raiz->dir);
		free(raiz);
		raiz = NULL;
	}
}

void imprA(series *raiz){
	if (raiz != NULL)
	{
		imprA(raiz->esq);
		printf("titulo: %s\n\tnumero de temporadas: %d\n\n", raiz->titulo, raiz->nTemp);
		imprA(raiz->dir);
	}
}

temp *buscaSerie(series *raiz, int cod){
	temp *aux = NULL;

	if(raiz != NULL){
		if (cod > raiz->cod)
		{
			aux = buscaSerie(raiz->dir, cod);
		}else if (cod < raiz->cod)
		{
			aux = buscaSerie(raiz->esq, cod);
		}else{
			aux = raiz->temps; 
		}	
	}
	return aux;
}

void imprB(temp *inicio){
	if (inicio != NULL)
	{
		printf("Titulo: %s\n \t%da Temp\n\tQantidade de Eps: %d\n\tAno: %d\n\n", inicio->titulo, inicio->numero, inicio->quantEp, inicio->ano);
		imprC(inicio->atores);
		imprB(inicio->prox);
	}
}

ator *buscaTemp(temp *inicio, int val){
	ator *aux;
	aux = NULL;
	if (inicio != NULL)
	{
		if (inicio->numero == val)
		{
			aux = inicio->atores;
		}else{
			aux = buscaTemp(inicio->prox, val);
		}
	}
	return aux;
}

void imprC(ator *raiz){
	if (raiz != NULL)
	{
		imprC(raiz->esq);
		printf("Personagem: %s\tNome do ator: %s\n\tDescricao: %s\n\n", raiz->nomePersona, raiz->nomeAtor, raiz->descPersona);
		imprC(raiz->dir);
	}
}

ator *personagem(ator *raiz, char nome[]){
	ator *aux;
	aux = NULL;
	if (raiz != NULL)
	{
		if (strcmp(raiz->nomePersona, nome) > 0)
		{
			aux = personagem(raiz->esq, nome);
		}else if (strcmp(raiz->nomePersona, nome) < 0)
		{
			aux = personagem(raiz->dir, nome);
		}else{
			aux = raiz;
		}
	}
	return aux;
}

void imprD(temp *inicio, char nome[], int i){
	ator *aux;
	aux = NULL;
	if (inicio != NULL)
	{
		aux = personagem(inicio->atores, nome);
		if (aux == NULL)
		{
			printf("%da Temp: Nao ha esse personagem\n", i);
		}else{
			printf("%da Temp: %s\n", i, aux->nomeAtor);
		}

		imprD(inicio->prox, nome, i+1);	
	}
}


int main(int argc, char const *argv[])
{
	series *raiz, *novaS;
	
	
	raiz = NULL;
	int conf;
	
	for(int i = 0; i < 1; i++)
	{
		novaS = novaSerie();
		conf = cadastroSerie(&raiz, novaS);
		printf("%d\n", conf);
	}	

	imprA(raiz);
	imprB(buscaSerie(raiz, 111));
	imprC(buscaTemp(buscaSerie(raiz, 111), 2));
	char nome[20] = "Julius";
	imprD(buscaSerie(raiz, 111), nome, 1);

	limpaSeries(raiz);
	return 0;
}