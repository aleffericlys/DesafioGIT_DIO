#ifndef lista3_h
#define lista3_h

#include <stdio.h>
#include <stdlib.h>

typedef struct arvSeries series;
typedef struct Temporadas temp;
typedef struct arvPart ator;


//Cria um novo nó de tipo series e retorna um ponteiro para o mesmo com os dados inseridos internamente na função
series *novaSerie();
//Insere um nó na arvore de series
//	raiz: ponteiro pra ponteiro da raiz da arvore;
//	novo: ponteiro para o nó a ser inserido na arvore
//	retorna 1 para uma inserção realizada com sucesso e 0 caso contrário
int cadastroSerie(series **raiz, series *novo);
//Busca uma série na árvore pelo código da série
//	raiz: ponteiro para raiz da arvore
// 	cod: codigo da série q deseja buscar
//	retorna um ponterio para o nó caso a série seja encontrada e NULL caso contrário
temp *buscaSerie(series *raiz, int cod);
//Faz a limpeza da arvore
//	raiz: ponteiro para raiz da arvore
void limpaSeries(series *raiz);
//Imprime os dados das séries na arvore de séries como solicitado na letra A
//	raiz: ponteiro para raiz da arvore
void imprA(series *raiz);

//	Essa função chama as funções novaTemp e cadTemp;
//	val: numero da temporada;
temp *dadosTemps(int val);
//Insere um nó na lista de temporadas
//	inicio: ponteiro pra ponteiro do inicio da lista;
//	nova: ponteiro para o nó a ser inserido na lista;
//	retorna 1 para uma inserção realizada com sucesso e 0 caso contrário
int cadTemp(temp **inicio, temp *nova);
//Cria um novo nó de tipo temp e retorna um ponteiro para o mesmo com os dados inseridos internamente na função
//	val: numero da temporada;
temp *novaTemp(int val);
//Busca uma temporada na lista pelo valor da temporada
//	inicio: ponteiro para o inicio da lista
// 	val: codigo da série q deseja buscar
//	retorna um ponterio para o nó caso a temporada seja encontrada e NULL caso contrário
ator *buscaTemp(temp *inicio, int val);
//Faz a limpeza da arvore
//	inicio: ponteiro para o inicio da lista
void limpaTemps(temp *inicio);
//Imprime os dados de cada temporada de uma determinada série
//	inicio: ponteiro para o inicio da lista
void imprB(temp *inicio);

//	Essa função chama as funções novoPersona e cadPersona;
ator *dadosPersona();
//Cria um novo nó de tipo ator e retorna um ponteiro para o mesmo com os dados inseridos internamente na função
ator *novoPersona();
//Insere um nó na arvore de personagens
//	raiz: ponteiro pra ponteiro da raiz da arvore;
//	novo: ponteiro para o nó a ser inserido na arvore
//	retorna 1 para uma inserção realizada com sucesso e 0 caso contrário
int cadPersona(ator **raiz, ator *novo);
//Busca um personagem na árvore pelo mome dele
//	raiz: ponteiro para raiz da arvore
// 	nome: nome de um personagem q se deseja buscar
//	retorna um ponterio para o nó caso a série seja encontrada e NULL caso contrário
ator *personagem(ator *raiz, char nome[]);
//Faz a limpeza da arvore
//	raiz: ponteiro para raiz da arvore
void limpaPersona(ator *raiz);
//Imprime os dados de cada personagem de uma determinada temporada de determinada série
//	inicio: ponteiro para o inicio da lista
void imprC(ator *raiz);
//Imprime os dados das séries na arvore de séries como solicitado na letra A
//	raiz: ponteiro para raiz da arvore
int menuPersona();

//imprime o nome dos artistas que interpretam um determinado persinagem
//	raiz: ponteiro para raiz da arvore
// 	nome: nome de um personagem q se deseja buscar
//	i: 1
void imprD(temp *inicio, char nome[], int i);
#endif