#ifndef q4_h
#define q4_h

#include <stdio.h>
#include <stdlib.h>

typedef struct ArvTermos termos;
typedef struct ArvSubT subt;
typedef struct ArvInt arvint;

termos *novoTermo(char termo[46], char listSubt[5][46]);
int cadTermo(termos **raiz, termos *novo);
void mostra(termos *raiz);
void alturaT(termos *No);
int ehFolhaT(termos *no);
int fatBalT(termos *No);
void balHorarioT(termos **raiz);
void balAntHorarioT(termos **raiz);
void balanceamentoT(termos **raiz);
void limpa(termos *raiz);

subt *dadoSubt(char subtermo[5][46]);
subt *novoSubt(char subtermo[]);
int cadSubt(subt **raiz, subt *novo);
void mostraSubt(subt *raiz);
int ehFolhaSubt(subt *no);
void alturaSubt(subt *No);
int fatBalSubt(subt *No);
void balHorarioSubt(subt **raiz);
void balAntHorarioSubt(subt **raiz);
void balanceamentoSubt(subt **raiz);
void limpaSubt(subt *raiz);

arvint *dadosInt();
arvint *novoNo(int i);
int insereNum(arvint **raiz, arvint *nova);
void mostraP(arvint *raiz);
int ehFolhaP(arvint *no);
void alturaP(arvint *No);
int fatBalP(arvint *No);
void balHorarioP(arvint **raiz);
void balAntHorarioP(arvint **raiz);
void balanceamentoP(arvint **raiz);
void limpaPag(arvint *raiz);

#endif