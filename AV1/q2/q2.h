#ifndef q2_h
#define q2_h

#include <stdio.h>
#include <stdlib.h>

typedef struct ArvNum arvNum;

arvNum *novoNo(int i);
int insereNum(arvNum **raiz, arvNum *nova);
int busca(arvNum *raiz, int val);
void limpaArv(arvNum *inicio);
int ehFolha(arvNum *no);
void mame(arvNum *raiz, int *maior, int *menor);


void altura(arvNum *raiz);
void profundidade(arvNum *raiz, int profu);
int fatBal(arvNum *No);
void balHorario(arvNum **raiz);
void balAntHorario(arvNum **raiz);
void balanceamento(arvNum **raiz);

#endif