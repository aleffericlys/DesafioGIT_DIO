#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Calcado calcado;

struct NO{
	calcado *info;
	int cor; // preto: cor = 0 || vermelho: cor = 1
	struct NO *esq;
	struct NO *dir;
};

struct Calcado{
	char tipo[46], marca[46];
	int cod, tam, quant, pos;
	float preco;
};

int cor(struct NO *H);
struct NO* balancear (struct NO *H);
struct NO *rotacionaDireita (struct NO *A);
struct NO *rotacionaEsquerda(struct NO* A);
void trocaCor(struct NO* H);
struct NO *move2EsqRED(struct NO *H);
struct NO *move2DirRED(struct NO *H);
struct NO *insereNO(struct NO *H, calcado *valor, int *resp);
int insere_ArvLLRB(struct NO **raiz, calcado *valor);
struct NO* remove_NO(struct NO* H, int valor);
int remove_ArvLLRB(struct NO **raiz, int valor);
void atualizar(struct NO *raiz, FILE *arq);
struct NO *removerMenor(struct NO *H);
struct NO *procuraMenor(struct NO* atual);
calcado *Calc(int ch1, char ch2[46], char ch3[46], int ch4, int ch5, float ch6 ,int pos);
void carregar(struct NO **Raiz);


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
	if(cor(H->dir) == 1)
		H = rotacionaEsquerda (H) ;

	
	if(H->esq != NULL && cor(H->esq) == 1 && !cor(H->esq->esq) == 1)
		H = rotacionaDireita (H);

	//2 filhos vermelhos: troca cor!
	if(cor(H->esq) == 1 && cor(H->dir) == 1)
		trocaCor(H);

    return H;
}

struct NO *rotacionaDireita (struct NO *A){
	struct NO* B = A->esq;
	A->esq = B->dir;
	B->dir = A;
	B->cor = A->cor;
	A->cor = 1;

	return B;
}

struct NO *rotacionaEsquerda(struct NO* A){

	struct NO *B = A->dir;
	A->dir = B->esq;
	B->esq = A;
	B->cor = A->cor;
	A->cor = 1;

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

	if(cor(H->dir->esq) == 1){
		H->dir = rotacionaDireita(H->dir);
		H = rotacionaEsquerda(H);
		trocaCor(H);
	}
	return H;
}

struct NO *move2DirRED(struct NO *H){

	trocaCor(H);

	if(cor(H->esq->esq) == 1){
		H = rotacionaDireita(H);
		trocaCor(H);
	}
	return H;
}

struct NO *insereNO(struct NO *H, calcado *valor, int *resp){
	struct NO *ret;
	if(H == NULL) {
		struct NO *novo;
		novo = (struct NO*)malloc(sizeof (struct NO));
		
		if(novo == NULL) {
			*resp = 0;
			return NULL;
		}
		novo->info = valor;
		novo->cor = 1;
		novo->dir = NULL;
		novo->esq = NULL;
		*resp = 1;

		ret = novo;

	}else{ 

        if(valor->cod == H->info->cod)
            *resp = 0;// Valor duplicado
        else{
            if (valor->cod < H->info->cod)
                H->esq = insereNO(H->esq, valor, resp);
            else
                H->dir = insereNO(H->dir, valor, resp);
        } 
        
        if(cor(H->dir) == 1 && cor(H->esq) == 0)
            H = rotacionaEsquerda (H);

        if(cor(H->esq) == 1 && cor(H->esq->esq) == 1)
            H = rotacionaDireita (H);

        if(cor(H->esq) == 1 && cor(H->dir) == 1)
            trocaCor(H);       
	
		ret = H;
	}

	return ret;
}

int insere_ArvLLRB(struct NO **raiz, calcado *valor){
	int resp;
    *(raiz) = insereNO(*raiz, valor, &resp);
	if(raiz != NULL)
		(*raiz)->cor = 0;
    
	return resp;
}

struct NO *remove_NO(struct NO* H, int valor) {
	struct NO *ret;
	if (valor < H->info->cod) {
		if(cor(H->esq) == 0 && cor(H->esq->esq) == 0)
			H = move2EsqRED(H);

		H->esq = remove_NO(H->esq, valor);
	}else {
		if(cor(H->esq) == 1)
			H = rotacionaDireita(H);

		if(valor == H->info->cod && (H->dir == NULL)){
			free (H);
			return NULL;
		}

		if(cor(H->dir) == 0 && cor(H->dir->esq) == 0)
			H = move2DirRED(H);

		if(valor == H->info->cod){
			struct NO* x = procuraMenor(H->dir);
			H->info->cod = x->info->cod;
			H->dir = removerMenor(H->dir);
		}else
			H->dir = remove_NO(H->dir, valor);
	}
	ret = balancear(H);
	
	return ret;
}

int consulta_ArvLLRB(struct NO *H, int valor){
	int ret = 0;
	if (H != NULL)
	{
		if(H->info->cod == valor)
		{
			ret = 1;
		}else if(valor < H->info->cod){
			ret = consulta_ArvLLRB(H->esq, valor);
		}else{
			ret = consulta_ArvLLRB(H->dir, valor);
		}
		
	}
	return ret;
}

int remove_ArvLLRB(struct NO **raiz, int valor) {
	int ret;
	if(consulta_ArvLLRB(*raiz, valor)){
        printf("Aqui %d\n", consulta_ArvLLRB(*raiz, valor));
		struct NO *h = *raiz;
		*raiz = remove_NO(h, valor);
		if(*raiz != NULL)
			(*raiz)->cor = 0;
		ret = 1;

		FILE *arq;
		arq = fopen("calcados.txt", "w");
		atualizar(*raiz, arq);
		fclose(arq);
		carregar(raiz);
	}else
		ret = 0;

	return ret;
}

void atualizar(struct NO *raiz, FILE *arq){
	if (raiz != NULL){
		fprintf(arq,"%d %s %s %d %d %.2f\n", raiz->info->cod, raiz->info->tipo, raiz->info->marca, raiz->info->tam, raiz->info->quant, raiz->info->preco);
		atualizar(raiz->esq, arq);
		atualizar(raiz->dir, arq);
	}
	
}

struct NO *removerMenor(struct NO *H) {
	if(H->esq == NULL) {
		free (H);
		return NULL;
	}
	if(cor(H->esq) == 0 && cor(H->esq->esq) == 0)
		H = move2EsqRED(H);

	H->esq = removerMenor(H->esq);
	return balancear(H);
}

struct NO *procuraMenor(struct NO* atual){
	struct NO *no1;
	if (atual->esq == NULL)
	{
		no1 = atual;
	}else{
		no1 = procuraMenor(atual->esq);
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

calcado *Calc(int ch1, char ch2[46], char ch3[46], int ch4, int ch5, float ch6 ,int pos){
	calcado *cac = NULL;
	cac = (calcado *) malloc(sizeof(calcado));
	cac->cod = ch1;
	strcpy(cac->tipo, ch2);
	strcpy(cac->marca, ch3);
	cac->tam = ch4;
	cac->quant = ch5;
	cac->preco = ch6;
	cac->pos = pos;
	return cac;
}

int ehFolha(struct NO *no){//Função que verifica se um nó é folha. Ela recebe um nó como parâmetro.
	int ret = 0;
	if (no->dir == NULL && no->esq == NULL)
	{
		ret = 1;
	}
	return ret;
}

void mostra(calcado *item){
	printf("%d %s %s %d %d %.2f\n", item->cod, item->tipo, item->marca, item->tam, item->quant, item->preco);
}

void mostraArv(struct NO *raiz){
	if(raiz != NULL){
		mostra(raiz->info);
        printf("%d\n", ehFolha(raiz));
        // printf("%d\n", raiz->dir->cor);
		if (raiz->cor)
		{
			printf("Vermelha\n\n");
		}else
		{
			printf("Preta\n\n");
		}
        mostraArv(raiz->esq);
		mostraArv(raiz->dir);
	}

}

void carregar(struct NO **Raiz){
	calcado *calc;
	char url[]="calcados.txt",
	ch2[46], ch3[46];
	int ch1 = 0, ch4 = 0, ch5 = 0, i;
	float ch6;
	FILE *arq;

	arq = fopen(url, "r");
	if(arq == NULL)
		printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
		for (i = 1;(fscanf(arq,"%d %s %s %d %d %f\n", &ch1, ch2, ch3, &ch4, &ch5, &ch6))!=EOF ;i++)
		{
			calc = Calc(ch1, ch2, ch3, ch4, ch5, ch6, i);
			insere_ArvLLRB(Raiz, calc);
		}
		fclose(arq);
	}
}

int main(int argc, char const *argv[])
{
	calcado *sob;
	struct NO *Raiz;
	Raiz = NULL;
	sob = NULL;

	carregar(&Raiz);
	mostraArv(Raiz);
	printf("\n");

	remove_ArvLLRB(&Raiz, 11);
	mostraArv(Raiz);
	// cadastra(&Raiz, &i, arq);

	// int ret;
	// ret = consulta_ArvLLRB(Raiz, 11);
	// if (ret == 1){
	// 	printf("Tienes");
	// }else{
	// 	printf("No tienes\n");
	// }

	
	limpaArv(Raiz);
	
	return 0;
}
