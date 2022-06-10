#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NO ArvLLRB;

struct NO{
	int info;
	int cor;
	struct NO *esq;
	struct NO *dir;
};

int cor(struct NO *H);
struct NO* balancear (struct NO *H);
struct NO *rotacionaDireita (struct NO *A);
struct NO *rotacionaEsquerda(struct NO* A);
void trocaCor(struct NO* H);
struct NO *move2EsqRED(struct NO *H);
struct NO *move2DirRED(struct NO *H);
struct NO *insereNO(struct NO *H, int valor, int *resp);
int insere_ArvLLRB(struct NO **raiz, int valor);
struct NO* remove_NO(struct NO* H, int valor);
int remove_ArvLLRB(struct NO *raiz, int valor);
struct NO *removerMenor(struct NO *H);
struct NO *procuraMenor(struct NO* atual);


int cor(struct NO *H){
	int ret;
	if(H == NULL)
	{
		ret = 0;
	}else{
		ret = H->cor;
	}
	
	return ret;
}

struct NO* balancear (struct NO *H){
	//nó vermelho é sempre filho à esquerda
	if(!cor(H->dir))
		H = rotacionaEsquerda (H) ;

	//Eilho da direita e neto da esquerda são vermelhos
	if(H->esq != NULL && !cor(H->dir) && !cor(H->esq->esq))
		H = rotacionaDireita (H);

	//2 filhos vermelhos: troca cor!
	if(!cor(H->esq) && !cor(H->dir))
		trocaCor(H);

return H;
}

struct NO *rotacionaDireita (struct NO *A){
	struct NO* B = A->esq;
	A->esq = B->dir;
	B->dir = A;
	B->cor = A->cor;
	A->cor = 0;

	return B;
}

struct NO *rotacionaEsquerda(struct NO* A){

	struct NO *B = A->dir;
	A->dir = B->esq;
	B->esq = A;
	B->cor = A->cor;
	A->cor = 0;

	return B;
}

void trocaCor(struct NO* H){
	H->cor = !H->cor;
	if(H->esq != NULL)
		H->esq->cor = !H->esq->cor;
	if(H->dir != NULL)
		H->dir->cor = !H->dir->cor;
}

struct NO *move2EsqRED(struct NO *H){

	trocaCor(H);

	if(!cor(H->dir->esq)){
		H->dir = rotacionaDireita(H->dir);
		H = rotacionaEsquerda(H);
		trocaCor (H);
	}
	return H;
}

struct NO *move2DirRED(struct NO *H){

	trocaCor(H);

	if(!cor(H->esq->dir)){
		H = rotacionaDireita(H);
		trocaCor(H);
	}
	return H;
}

struct NO *insereNO(struct NO *H, int valor, int *resp){
	if(H == NULL) {
		struct NO *novo;
		novo = (struct NO*)malloc (sizeof (struct NO));
		
		if(novo == NULL) {
			*resp = 0;
			return NULL;
		}
		novo->info = valor;
		novo->cor = 0;
		novo->dir = NULL;
		novo->esq = NULL;
		*resp = 1;
		return novo;
	}else if(valor == H->info)
		*resp = 0;// Valor duplicado
	else{
		if (valor < H->info)
			H->esq = insereNO (H->esq, valor, resp);
		else
			H->dir = insereNO(H->dir, valor, resp);
	}

	if(!cor(H->dir) && cor (H->esq))
		H = rotacionaEsquerda (H);

	if(!cor(H->esq) && !cor(H->esq->esq))
		H = rotacionaDireita (H);

	if(!cor(H->esq) && !cor(H->dir))
		trocaCor (H);

	return H;
}

int insere_ArvLLRB(struct NO **raiz, int valor){
	int resp;
	*raiz = insereNO(*raiz, valor, &resp);
	if(*raiz == NULL)
		(*raiz)->cor = 1;
	return resp;
}

struct NO *remove_NO(struct NO* H, int valor) {
	if (valor < H->info) {
		if(cor(H->esq) && cor(H->esq->esq))
			H = move2EsqRED (H) ;

		H->esq = remove_NO(H->esq, valor);
	}else {
		if(!cor(H->esq))
			H = rotacionaDireita(H);

		if(valor == H->info && (H->dir == NULL)){
			free (H);
			return NULL;
		}

		if(cor(H->dir) && cor(H->dir->esq))
			H = move2DirRED(H);

		if(valor == H->info){
			struct NO* x = procuraMenor(H->dir);
			H->info = x->info;
			H->dir = removerMenor(H->dir);
		}else
			H->dir = remove_NO(H->dir, valor);
	}
		return balancear(H);

}

int consulta_ArvLLRB(struct NO *H, int valor){
	int ret = 0;
	if (H != NULL)
	{
		if(H->info == valor)
		{
			ret = 1;
		}else if(valor < H->info){
			ret = consulta_ArvLLRB(H->esq, valor);
		}else
		{
			ret = consulta_ArvLLRB(H->dir, valor);
		}
		
	}
	return ret;
}

int remove_ArvLLRB(struct NO *raiz, int valor) {

	if(consulta_ArvLLRB(raiz, valor)){
		struct NO *h = raiz;
		raiz = remove_NO(h, valor);
		if(raiz != NULL)
			(raiz)->cor = 1;
		return 1;
	}else
		return 0;
}

struct NO *removerMenor(struct NO *H) {
	if(H->esq == NULL) {
		free (H);
		return NULL;
	}
	if(cor(H->esq) && cor(H->esq->esq))
		H = move2EsqRED(H);

	H->esq = removerMenor(H->esq) ;
	return balancear (H);
}

struct NO *procuraMenor(struct NO* atual){
	struct NO *no1 = atual;
	struct NO *no2 = atual->esq;
	while(no2 != NULL) {
		no1 = no2;
		no2 = no2->esq;
	}
	return no1;
}

void limpaArv(struct NO *raiz){
	if (raiz != NULL)
	{
		limpaArv(raiz->esq);
		limpaArv(raiz->dir);
		free(raiz);
		raiz = NULL;
	}
}

void mostraArv(struct NO*raiz){
	if(raiz != NULL){
		printf("%d\n", raiz->info);
		if (raiz->cor)
		{
			printf("preta");
		}else
		{
			printf("vermelha");
		}
		
		
		mostraArv(raiz->esq);
		mostraArv(raiz->dir);
	}

}

int main() {
	
	struct NO *Raiz;

	int vet[] = {5, 4, 3, 2, 1, 10, 9, 8, 7, 6, 11, 12};//, 6, 7, 8, 9, 10}; {13, 2, 5, 8, 15, 9, 18, 20, 1, 7};

	Raiz = NULL;

	for (int i = 0; i < 12; i++)
	{
		insere_ArvLLRB(&Raiz, vet[i]);
	}
	
	mostraArv(Raiz);

	limpaArv(Raiz);
	return 0;
}