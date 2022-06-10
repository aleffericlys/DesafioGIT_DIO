#ifndef q1_h
#define q1_h

#include <stdio.h>
#include <stdlib.h>

typedef struct ArvNum arvNum;

arvNum *novoNo(int i);
int insereNum(arvNum **raiz, arvNum *nova, int profu);
int busca(arvNum *raiz, int val);
void limpaArv(arvNum *inicio);
int ehFolha(arvNum *no);
void mame(arvNum *raiz, int *maior, int *menor);

#endif