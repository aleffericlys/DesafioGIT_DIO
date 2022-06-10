#ifndef q3_h
#define q3_h

#include <stdio.h>
#include <stdlib.h>

typedef struct ArvTermos termos;
typedef struct ArvSubT subt;
typedef struct ArvInt arvint;

termos *novoTermo(char termo[46], char listSubt[5][46]);
int cadTermo(termos **raiz, termos *novo);
void mostra(termos *raiz);
void limpa(termos *raiz);

subt *dadoSubt(char subtermo[5][46]);
subt *novoSubt(char subtermo[]);
int cadSubt(subt **raiz, subt *novo);
void mostraT(subt *raiz);
void limpaSubt(subt *raiz);

arvint *dadosInt();
arvint *novoNo(int i);
int insereNum(arvint **raiz, arvint *nova);
void mostraP(arvint *raiz);
void limpaPag(arvint *raiz);

#endif